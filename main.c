////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande();
void convertirNenChaine4(int N, char *N4);
void lireLesCommandes();
int lireCommande(FILE *ficCommande, char *NNNN);
float obtenirPrix(int reference);

int main() {
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 

	//TODO: Commenter ça
	FILE *f;int N=1;
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
		printf("%s", nomCommande);

		ficCommande = fopen(nomCommande, "rt");
		if (ficCommande != NULL) { // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present", nomCommande);
			//lireCommande(ficCommande, NNNN); // à vous de coder cette fonction lors de ce TP10
			printf("\nOlalah ça marche");
			fclose(ficCommande);
		} else {
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f = fopen("nextFact", "w"); // on va ecrire la valeur de N dans enxtFact
			// pour
			fwrite(&N, 1, sizeof(int), f);
			fclose(f);
			FINI = 1;
		}

		N++;
	} while (FINI == 0);

}

int lireCommande(FILE *ficCommande, char *NNNN){
	int ref, nbProdu;
	char chaine[50];
	char nomClient[50];
	float pu, pl, pTot;

	FILE *ficFacture = NULL;
	ficFacture=fopen(NNNN,"w"); //TODO: Changer le nom du fichier
	if(ficFacture == NULL)
		return 2; //On ne peut pas créer le fichier/Ecrire dedans
	
	//TODO: Si ligne 1 non vide
	fscanf(ficCommande, "%s", nomClient);
	fprintf(ficFacture, "Client : %s\n", nomClient);

	do{ //FIXME: Mettre la bonne condition (tant que ligne pas vide)
		//Lire la 2e ligne
		fscanf(ficCommande, "%d %s %f", &ref, &nbProdu);
		//pu = obtenirPrix(ref);
		//TODO: Verifier que pu est différent de -1 (ref indefinie)

		/*
		pl = pu * nbProdu;
		pTot += pl;

		*/


		fprintf(ficFacture, "Client : %s\n", nomClient);
		//fwrite(,1,sizeof(int),f);
			

	}while(1);

	fclose(f);
	return 0;
}

float obtenirPrix(int reference){
	return -1;
}