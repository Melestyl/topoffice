////////////////////////// TP10
// LAFFRA Timothée et TELLIER--CALOONE Tom, LE1 TPB1.

#include "topoffice.h"

int main() {
	FILE *f;
	int N = 1;

	// Permet de créer nextFact si il n'existe pas, sinon n'y touche pas
	f = fopen("ressources/nextFact", "r");
	if (f == NULL) {
		f=fopen("ressources/nextFact","w");
		fwrite(&N,1,sizeof(int),f);
	}
	fclose(f);

	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)

	return 0;
}

int lireProchaineCommande() {
	FILE *f;
	int N;

	f = fopen("ressources/nextFact", "r");
	fread(&N, sizeof(int), 1, f);
	fclose(f);

	return N;
}

void convertirNenChaine4(int N, char *N4) {
	sprintf(N4, "%04d", N); // Si N=69, alors N4="0069"
}

void lireLesCommandes() {
	FILE *ficCommande = NULL;
	int FINI = 0;
	int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	//ce do while prend fin dès que fichier commandeXXXX.txt est absent
	do {
		strcpy(nomCommande, "./commandes/commande");
		convertirNenChaine4(N, NNNN);
		ficCommande = NULL;
		strcat(nomCommande, NNNN);
		strcat(nomCommande, ".txt");

		ficCommande = fopen(nomCommande, "rt");
		if (ficCommande != NULL) { // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present", nomCommande);
			lireCommande(ficCommande, NNNN);
			fclose(ficCommande);
		}
		else {
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f = fopen("ressources/nextFact", "w"); // on va ecrire la valeur de N dans nextFact
			fwrite(&N, 1, sizeof(int), f);
			fclose(f);
			FINI = 1;
		}
		N++;
	} while (FINI == 0);
}

int lireCommande(FILE *ficCommande, char *NNNN) {
	unsigned ref;
	int nbProdu;
	char nomFact[50];
	char nomProduit[TAILLE];
	char nomClient[50];
	float prixUni, prixLot, prixTot = 0;

	sprintf(nomFact, "factures/facture%s.txt", NNNN);
	FILE *ficFacture = NULL;
	ficFacture=fopen(nomFact, "w");
	if(ficFacture == NULL)
		return 2; //On ne peut pas créer le fichier/Ecrire dedans
	
	// EOF est le retour de la fonction fscanf lorsque la lecture n'a pas prixUni avoir lieu (fichier vide ou malformé)
	if (fscanf(ficCommande, "%s", nomClient) != EOF) {
		fprintf(ficFacture, "Client : %s\n", nomClient);
		fprintf(ficFacture, "%10s %50s %20s %10s %10s\n", "Quantité", "Nom", "Réf", "Prix u.", "Total");

		// Tant qu'on peut lire une nouvelle ligne (un produit avec une quantité)
		while (fscanf(ficCommande, "%u %d", &ref, &nbProdu) != EOF) {
			prixUni = obtenirPrix(ref);
			prixLot = prixUni * nbProdu;
			fprintf(ficFacture, "%10d %50s %20u %10f %10f\n", nbProdu, obtenirNom(ref, nomProduit), ref, prixUni, prixLot);
			prixTot += prixLot;
			retirerStock(ref, nbProdu);
		}
		fprintf(ficFacture, "\n\t\tTVA (20%%) : %f\n", prixTot*0.2);
		fprintf(ficFacture, "\t\tPRIX TOTAL = %f", prixTot*1.2);
	}

	fclose(ficFacture);
	return 0;
}

float obtenirPrix(unsigned reference) {
	FILE* f = NULL;
	T_Produit produit;

	f = fopen("ressources/produits.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de produits.txt");
		exit(2);
	}

	// Parcourt tout le fichier produits.txt jusqu'à trouver la référence recherchée, et renvoie son prix
	while (fscanf(f, "%u %s %f", &produit.reference, produit.libelle, &produit.prixU) != EOF) {
		if (produit.reference == reference)
			return produit.prixU;
	}

	fclose(f);
	return -1;
}

char *obtenirNom(unsigned ref, char* nom) {
	FILE* f = NULL;
	T_Produit produit;

	f = fopen("ressources/produits.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de produits.txt");
		exit(2);
	}

	// Parcourt tout le fichier produits.txt jusqu'à trouver la référence recherchée, et renvoie son noms
	while (fscanf(f, "%u %s %f", &produit.reference, produit.libelle, &produit.prixU) != EOF) {
		if (produit.reference == ref) {
			strcpy(nom, produit.libelle);
			return nom;
		}
	}

	fclose(f);
	return "ERREUR";
}

void retirerStock(unsigned ref, int qte) {
	FILE *f = NULL;
	FILE *ftemp = NULL;
	int stock;
	unsigned ref2;

	f = fopen("ressources/stock.txt", "r");
	ftemp = fopen("temp.txt", "w");
	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de stock.txt");
		exit(2);
	}
	if (ftemp == NULL) {
		fprintf(stderr, "Erreur d'ouverture de temp");
		exit(2);
	}

	/* Change une ligne du fichier stock.txt (la ligne avec la réf concernée)
	 * Pour ce faire, on va créer un fichier temporaire et réécrire tout le fichier stock.txt dans ce fichier temporaire
	 * Au moment où on arrive à la ligne qui nous intéresse (la ligne avec la référence recherchée), on écrit la nouvelle valeur dans le fichier temporaire
	 * Ainsi, notre fichier temporaire correspond au fichier "modifié" que nous voulions
	 * On renomme le fichier temporaire avec le nom de stock.txt, pour le remplacer
	 * Et ainsi, nous avons modifié une seule ligne de notre fichier
	 */
	while (fscanf(f, "%u %d", &ref2, &stock) != EOF) {
		if (ref2 == ref) { // La ligne qui nous intéresse (on change la valeur)
			stock -= qte;
			fprintf(ftemp, "%u %d\n", ref2, stock);
			if (stock <= 0)
				besoinDeStock(ref); // Si le stock est négatif ou nul, alors on appelle la fonction qui va écrire dans alertes.txt la référence manquante
		}
		else // Les autres lignes (on recopie à l'identique)
			fprintf(ftemp, "%d %d\n", ref2, stock);
	}
	fclose(f);
	fclose(ftemp);
	rename("temp.txt", "ressources/stock.txt");
}

void besoinDeStock(unsigned ref) {
	FILE* f = NULL;
	unsigned ref2;
	unsigned short isPresent = 0; // = bool

	f = fopen("ressources/alertes.txt", "a+");

	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de alertes.txt");
		exit(2);
	}

	// On vérifie la présence de la référence dans le fichier
	while (fscanf(f, "%u", &ref2) != EOF) {
		if (ref2 == ref) {
			isPresent = 1;
			break;
		}
	}
	// Si la référence n'était pas présente dans le fichier, alors on l'écrit à la fin
	if (!isPresent)
		fprintf(f, "%u\n", ref);
	fclose(f);
}