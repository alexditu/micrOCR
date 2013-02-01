/*
 *
 *	Projet : Sous traitance geekou
 *	Fichier : Main.c
 *	Version 2
 *	Auteur : Vian Jeremy
 *	Date : 11/01/2013
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include "spell.h"

#define TAILLE_BUFFER 256
#define TAILLE_MOT_MAX 50
#define TAILLE_CHOIX_MAX 50
#define STRTOK_SYNTAX ". \r\t\n"

typedef unsigned int uint;
typedef FILE* pFILE;
typedef struct
{
	uint NombreMots;
	char**	LeMot;
}Dictionnaire,*pDictionnaire;


///
///	Geekou Projet fonctions
///
///================================================================================
char* spellCheck(const char* texteOriginal);
int GetMode(const char* maChaine);
char* DemandeCorrectionManuelle(const char* MessageDemande,char* pMot);
int DemandeOuiouNON(const char *chaine, ...);

///
///	Operations sur les chaines de charactères
///
///=========================================================================
char* chercheEtRemplace(char *maChaine, const char *ARemplacer, const char *RemplacePar);
char* copieChaineCaractere(const char* texteOriginal);
char* TransformeEnMode(char* maChaine,int Mode);
char* transformeEnMinuscule(char* maChaine);
char* transformeEnMinusculeSansToucher(const char* maChaine);
char* transformeEnMajuscule(char* maChaine);
char* transformeEnPremiereLettreMajuscule(char* maChaine);
int estUnNombre(const char * s);
int estPremiereLettreMaj(const char* maChaine);
int estEnMaj(const char* maChaine);
int estEnMin(const char* maChaine);

///
///	Dictionnaire PART
///
///=========================================================================
pDictionnaire OuvreDictionnaire(const char* nomFichier);
void FermeDictionnaire(pDictionnaire monDictionnaire);
bool DicoContient(const char* Mot, pDictionnaire monDictionnaire);
uint LisNombreDeMots(pFILE monFichier);
char* LisMot(pFILE monFichier);


