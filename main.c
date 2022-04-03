////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande();
void convertirNenChaine4(int N, char *N4);
void lireLesCommandes();
int lireCommande(FILE *ficCommande, char *NNNN);
float obtenirPrix(unsigned reference);
char *obtenirNom(unsigned ref, char* nom);

int main() {
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 

	FILE *f;
	int N = 1;

	//TODO: Commenter ça
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	


	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
	FILE *f;
	int N;
	f = fopen("nextFact", "r");
	fread(&N, sizeof(int), 1, f);
	fclose(f);
//printf("\n--->lu N=%d",N);
	return N;
}

void convertirNenChaine4(int N, char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
	sprintf(N4, "%04d", N);
}


void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
	FILE *ficCommande = NULL;
	int FINI = 0;
	int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	do //ce do while prend fin dès que fichier commandeXXXX.txt est absent
	{
		strcpy(nomCommande, "./commandes/commande");
		convertirNenChaine4(N, NNNN);
		//printf("\n==>%s<==",NNNN);
		ficCommande = NULL;
		strcat(nomCommande, NNNN);
		strcat(nomCommande, ".txt");

		//printf("\n traitement de  %s",nomCommande);

		ficCommande = fopen(nomCommande, "rt");
		if (ficCommande != NULL) { // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present", nomCommande);
			lireCommande(ficCommande, NNNN); // à vous de coder cette fonction lors de ce TP10
			// printf("\nOlalah ça marche");
			fclose(ficCommande);
		} else {
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f = fopen("nextFact", "w"); // on va ecrire la valeur de N dans nextFact
			fwrite(&N, 1, sizeof(int), f);
			fclose(f);
			FINI = 1;
		}

		N++;
	} while (FINI == 0);
}

int lireCommande(FILE *ficCommande, char *NNNN){
	unsigned ref;
	int nbProdu;
	char chaine[50]; // FIXME: Nom pas explicit, qu'est-ce que c'est ? Est-ce que c'est pour le nom de la facture ?
	char nomProduit[TAILLE];
	char nomClient[50];
	float pu, pl, pTot = 0; // FIXME: "pl" ?

	sprintf(chaine, "factures/facture%s.txt", NNNN);
	FILE *ficFacture = NULL;
	ficFacture=fopen(chaine,"w");
	if(ficFacture == NULL)
		return 2; //On ne peut pas créer le fichier/Ecrire dedans
	
	// EOF est le retour de la fonction fscanf lorsque la lecture n'a pas pu avoir lieu (fichier vide ou malformé)
	if (fscanf(ficCommande, "%s", nomClient) != EOF) {
		fprintf(ficFacture, "Client : %s\n", nomClient);
		fprintf(ficFacture, "%10s %50s %20s %10s %10s\n", "Quantité", "Nom", "Réf", "Prix u.", "Total");

		while (fscanf(ficCommande, "%u %d", &ref, &nbProdu) != EOF) {
			// TODO: Trop de commentaires oskour

			//Lire la 2e ligne
			//pu = obtenirPrix(ref);
			//TODO: Verifier que pu est différent de -1 (ref indefinie)
			/*
			pl = pu * nbProdu;
			pTot += pl;
			*/
			//fwrite(,1,sizeof(int),f);

			pu = obtenirPrix(ref);
			pl = pu * nbProdu;
			fprintf(ficFacture, "%10d %50s %20u %10f %10f\n", nbProdu, obtenirNom(ref, nomProduit), ref, pu, pl);
			pTot += pl;
		}
		fprintf(ficFacture, "Insérer TVA ici\n");
		fprintf(ficFacture, "\t\tPRIX TOTAL = %f", pTot);
	}
	return 0;
}

float obtenirPrix(unsigned reference){
	FILE* f = NULL;
	T_Produit produit;

	f = fopen("produits.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de produits.txt");
		exit(2);
	}

	while (fscanf(f, "%d %s %f", &produit.reference, produit.libelle, &produit.prixU) != EOF) {
		if (produit.reference == reference)
			return produit.prixU;
	}

	return -1;
}

char *obtenirNom(unsigned ref, char* nom) {
	FILE* f = NULL;
	T_Produit produit;

	f = fopen("produits.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "Erreur d'ouverture de produits.txt");
		exit(2);
	}

	while (fscanf(f, "%d %s %f", &produit.reference, produit.libelle, &produit.prixU) != EOF) {
		if (produit.reference == ref) {
			strcpy(nom, produit.libelle);
			return nom;
		}
	}

	return "ERREUR";
}