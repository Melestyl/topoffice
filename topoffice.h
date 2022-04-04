#ifndef TOPOFFICE_H
#define TOPOFFICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

/**
 * @brief Renvoie l'int contenu dans nextFact
 * @return int stocké dans nextFact
 */
int lireProchaineCommande();

/**
 * @brief Permet de transformer un int en chaine de caractère XXXX
 * @param N Le chiffre
 * @param N4 La chaine de caractère destination
 */
void convertirNenChaine4(int N, char *N4);

/**
 * @brief Fait des factures de toutes les commandes présentes dans le répertoire commandes
 */
void lireLesCommandes();

/**
 * @brief Fonction qui lit une commande, et en fait une facture
 * @param ficCommande Pointeur de fichier vers la commande à traiter
 * @param NNNN Numéro de commande
 * @return 0 si ça s'est bien passé, 2 si l'ouverture du fichier a rencontré un problème
 */
int lireCommande(FILE *ficCommande, char *NNNN);

/**
 * @brief Permet de trouver le prix d'un produit par sa référence
 * @param reference La référence du produit concerné
 * @return Son prix
 */
float obtenirPrix(unsigned reference);

/**
 * @brief Permet de trouver le nom d'un produit par sa référence
 * @param ref La référence du produit concerné
 * @param nom La chaine de caractère destination dans laquelle sera écrit le nom
 * @return Le nom du produit
 */
char *obtenirNom(unsigned ref, char* nom);

/**
 * @brief Soustrait la quantité passée en argument au stock du produit
 * @param ref La référence du produit
 * @param qte La quantité à retirer
 */
void retirerStock(unsigned ref, int qte);

/**
 * @brief Ecrit dans alertes.txt la référence qu'on a besoin de réapprovisionner, si elle n'y est pas déjà
 * @param ref La référence du produit à écrire
 */
void besoinDeStock(unsigned ref);

#endif //TOPOFFICE_H
