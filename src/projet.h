/**
 * \file projet.h
 * \brief Fichier d'en-tête du projet d'algo 2012-2013
 * \author Adrien Bertrand (Groupe B2 avec Romain Bosselet et Yanis Chamieh)
 * \version 2.7
 * \date 26/01/2013
 *
 * Fichier .h d'en-tête du programme de reconnaissance matricielle de caractères
 *
 */


//********************
//     Includes :    *
//********************

#include <dirent.h>
#include <stdlib.h> // Pour pouvoir utiliser exit
#include <stdio.h> // Pour pouvoir utiliser printf
#include <math.h> // Pour pouvoir utiliser sin et cos
#include <string.h>
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire
#include <locale.h> //support de l'unicode
#include <ctype.h> // autres trucs de string/char


//********************
//  Defines/Macros : *
//********************

#define LargeurFenetre 800
#define HauteurFenetre 600

#define nbrBoutons 5

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#define PRINT(token) printf(#token " = %d      ******\n", token)
#define SWAP(a, b)  do { a ^= b; b ^= a; a ^= b; } while (0)
#define INTSWAP(a, b) { register int t=(a);(a)=(b);(b)=t; }



//********************
//    Structures :   *
//********************

/**
 * \brief     Structure basique définissant un rectangle.
 * \details   Structure basique définissant un rectangle par les coordonnées de 2 sommets opposés. La hauteur et la largeur sont aussi directement disponibles.
 */
typedef struct Rectangle {
    int x1; //             +--------+ (x2, y2)
    int y1; //             |        |
    int x2; //             |        |
    int y2; //     (x1,y1) +--------+
    int w; ///< width du rectangle pour un accès plus rapide
    int h; ///< height du rectangle pour un accès plus rapide
} Rectangle;

/**
 * \brief     Structure basique définissant une couleur RGB.
 * \details   Structure basique définissant une couleur par ses 3 composantes RGB.
 */
typedef struct Couleur {
    int r; ///< Red (0-255)
    int g; ///< Green (0-255)
    int b; ///< Blue (0-255)
} Couleur;

/**
 * \brief     Associe une fréquence à une couleur.
 * \details   Associe une fréquence (\a freq) à une couleur (\a c).
 */
typedef struct colorCount {
    Couleur c;
    int freq;
} colorCount;

/**
 * \brief     Représente une image matricielle binaire.
 * \details   \a data est un tableau rempli de 0 et de 1 représentant respectivement un pixel de fond et un pixel de lettre.\n
 * 			  \a w (width) et \a h (height) sont la taille.
 */
typedef struct imageMatricielle {
    int w;
    int h;
    unsigned char* data;
} imageMatricielle;

/**
 * \brief     Définit une "lettre" par son éventuelle position en x, son caractère et ses images associées.
 * \details   Définit une "lettre" par son éventuelle position en x dans un mot (structure #Mot), son caractère et ses images associées (BmpRGB et matricielles).
 */
typedef struct Lettre {
    DonneesImageRGB* img;
    imageMatricielle* imgMat;
    int x;
    char carac;
} Lettre;

/**
 * \brief     Définit un "mot" par son éventuelle position en x, ses lettres et leurs nombre.
 * \details   Définit un "mot" par son éventuelle position en x dans l'image globale, les lettres (structure #Lettre), le nombre de lettre le constituant.
 */
typedef struct Mot {
    Lettre* lettres;
	int x;
    int nbrLettres;
} Mot;

/**
 * \brief     Définit une "lettre" typique d'une police, avec notemment son ratio largeur/hauteur et ses images associées.
 * \details   Définit une "lettre" (caractère) typique d'une police dont le nom est précisé, avec notemment son emplacement (nom du fichier), ainsi que son ratio largeur/hauteur et ses images associées.
 */
typedef struct LettrePolice {
    DonneesImageRGB* img;
    imageMatricielle* imgMat;
    float ratioWH;
    char carac;
    char nomFichier[50];
    char nomPolice[40];
} LettrePolice;

/**
 * \brief     Définit une correspondance entre une lettre détectée et une lettre tirée d'une police de caractères, avec un indice de fiabilité.
 * \details   Définit une correspondance entre une lettre détectée d'un mot et une lettre tirée d'une police de caractères, avec un indice de fiabilité.
 */
typedef struct Correspondance {
    Lettre* lettre;
    LettrePolice* lettrePolice;
    double fiabilite;
} Correspondance;

/**
 * \brief     Définit une zone de text input d'après ses caractéristiques principales (coordonées, taille, nom, statut..)
 * \details   
 */
typedef struct textInput {
	int x,y; ///< coords
	int w,h; ///< taille
	char txt[55]; ///< texte
	char titre[55]; ///< titre affiché au dessus
	double val; ///< valeur numerique, si besoin
	short int mode; ///< pour indiquer le mode courant (nom ville, lat., long.)
	bool isActive; /// <focus ou pas
	bool isHidden; ///< affiché ou pas
} textInput;

/**
 * \brief     Définit un bouton d'après ses caractéristiques principales (coordonées, taille, nom, statuts..)
 * \details   
 */
typedef struct Bouton {
	float x,y; ///< coords en % de la fenetre
	int w,h; ///< taille en px
	char txt[55]; ///< texte
	short int id; ///< numero du bouton pour faire correspondre a une fonction
	bool isActive; ///< focus ou pas
	bool isHidden; ///< affiché ou pas
} Bouton;

//********************
//    Prototypes :   *
//********************

// Fonctions "utilitaires" :

/**
 * \brief      Teste si les couleurs RGB en paramètres sont égales.
 * \details    Vérifie si chaque composante RGB de l'une est égale à celle de l'autre.
 * \param    c1         1ère couleur
 * \param    c2         2ème couleur
 * \return    Un \e int jouant le rôle de booléen (1 si vrai -couleurs égales- ou 0 si faux).
 */
int CouleursEgales(Couleur c1, Couleur c2);

/**
 * \brief      Permet d'obtenir la couleur d'un pixel d'une image selon ses coordonées
 * \details    Permet d'obtenir la couleur RGB d'un pixel d'une image d'après ses coordonées (x,y).
 * \param      image	l'image source que l'on va utiliser
 * \param      x		La coordonée en x du pixel voulu
 * \param      y		La coordonée en y du pixel voulu
 * \return     la couleur du pixel.
 */
Couleur getColorAt(DonneesImageRGB* image, int x, int y);

/**
 * \brief      Permet d'obtenir la couleur d'un pixel d'une image selon son index
 * \details    Permet d'obtenir la couleur RGB d'un pixel d'une image d'après son index.
 * \param      image	l'image source que l'on va utiliser
 * \param      i		L'index du tableau de données de l'image RGB
 * \return     la couleur du pixel.
 */
Couleur getColorAtI(DonneesImageRGB* image, int i);

/**
 * \brief      Convertit des coordonées (x,y) en indice (index du tableau de données de l'image RGB)
 * \details    Convertit des coordonées (x,y) en indice (index du tableau de données de l'image RGB) en vérifiant que ce point (x,y) apaprtient bien à l'image.
 * \param      image	l'image source que l'on va utiliser
 * \param      x		La coordonée en x du pixel voulu
 * \param      y		La coordonée en y du pixel voulu
 * \return     L'indice (index du tableau de données de l'image RGB) correspondant au pixel, où 0 si les coordonées sont invalides.
 */
long long int getIfromXYinImage(DonneesImageRGB* image, int x, int y);

/**
 * \brief      Dessine un rectangle vide défini par ses sommets haut-gauche et bas-droit.
 * \details    Dessine un rectangle vide défini par ses sommets haut-gauche et bas-droit en utilisant la fonction ligne(), dépendante d'OpenGL via GfxLib
 * \param      x1	Coordonée x du sommet haut-gauche du rectangle
 * \param      y1	Coordonée y du sommet haut-gauche du rectangle
 * \param      x2	Coordonée x du sommet bas-droit du rectangle
 * \param      y2	Coordonée y du sommet bas-droit du rectangle
 * \return    
 */
void drawRect(int x1, int y1, int x2, int y2);

/**
 * \brief      Dessine un bouton.
 * \param      b	le bouton à dessiner.
 * \return     
 */
void paintBouton(Bouton b);

/**
 * \brief      Calcule la surface du rectangle donné.
 * \details    
 * \param      rect	   Le rectangle dont on veut la surface
 * \return     La surface du rectangle, en pixels²
 */
int getRectangleSurface(Rectangle rect);

/**
 * \brief      Renvoie la fréquence maximale d'un tableau de fréquence de couleur.
 * \details    Renvoie la valeur de la fréquence maximale d'un tableau de fréquence de couleur de taille donnée
 * \param      tab		Le tableau de couleur
 * \param      taille	le nombre d'éléments du tableau \a tab
 * \return     la valeur de la fréquence maximale
 */
int indiceFreqMax(colorCount* tab, int taille);

/**
 * \brief      Renvoie la 2ème fréquence maximale d'un tableau de fréquence de couleur.
 * \details    Renvoie la 2ème valeur de la fréquence maximale d'un tableau de fréquence de couleur de taille donnée
 * \param      tab		Le tableau de couleur
 * \param      taille	le nombre d'éléments du tableau \a tab
 * \param      except	la valeur à ne pas considérer (c'est le maximum)
 * \return     la valeur de la 2ème fréquence maximale
 */
int indiceFreqSousMax(colorCount* tab, int taille, int except);

/**
 * \brief      Renvoie la médiane du tableau de valeur donnée.
 * \note       from the public domain source code on http://ndevilla.free.fr/median/median/
 * \param      arr		Le tableau de valeurs
 * \param      n		le nombre d'éléments du tableau \a arr
 * \return     la médiane du tableau
 */
 int quick_select(int* arr, int n);

/**
 * \brief      Affiche le contenu d'un tableau d'entier
 * \param      tab		Le tableau d'entiers
 * \param      nbrElem	le nombre d'éléments du tableau \a tab
 * \return     
 */
void dispTab(int *tab, int nbrElem);

/**
 * \brief      Indique si une chaîne se termine par une certaine autre chaîne (suffixe).
 * \details    
 * \param      str		(pointeur vers) la chaîne complète
 * \param      suffix	(pointeur vers) la chaîne du suffixe
 * \return     Un \e int jouant le rôle de booléen (1 si vrai ou 0 si faux).
 */
int strEndsWith(const char *str, const char *suffix);

/**
 * \brief      Initialise et alloue un tableau de structure #LettrePolice avec les caractères de la police Arial.
 * \details    Initialise et alloue un tableau de 70 structures (c'est le nombre de caractères de la police Arial) pour chaque caractères de la police. Un fichier texte est utilisé pour faire la correspondance entre chaque fichier .bmp (imagette de chaque caractère) et le caractère en lui-même.
 * \param	   Aucun
 * \return     (Le pointeur vers) le tableau de structure contenant les caractèers de la police Arial chargée.
 */
LettrePolice* initPoliceArial();

/**
 * \brief      Vérifie si le rectangle de rogange est valide par rapport à l'image à analyser.
 * \details    Vérifie si le rectangle de rogange est valide par rapport à l'image à analyser en vérifiant si les sommets du rectangle sont bien compris dans l'image.
 * \param      manualRect	le rectangle que l'utilisateur a défini.
 * \param      imageBest	l'image qui va être analysée.
 * \return     Le rectangle non modifié si OK, et un rectangle "dummy" (invalide pour la suite) si problème.
 */
Rectangle checkManualRect(Rectangle manualRect, DonneesImageRGB* imageBest);

/**
 * \brief      Vérifie si le clic de coordonées (x,y) est dans le rectangle rect.
 * \param      x	le rectangle que l'utilisateur a défini.
 * \param      y	l'image qui va être analysée.
 * \param      rect	le rectangle.
 * \return     un entier jouand le rôle de booléen : 1 si vrai, 0 si faux.
 */
int clicInRect(int x, int y, Rectangle rect);


// Fonctions de traitement d'une image en elle-même :

/**
 * \brief      Crée une copie rognée d'une image (DonneesImageRGB) à une zone donnée.
 * \details    Crée une copie rognée d'une image source (DonneesImageRGB) à une zone donnée par un rectangle précisant les coordonées.
 * \param      image	l'image source
 * \param      rect		Le rectangle utilisé pour déterminer les coordonées de la zone où l'image se fera rogner.
 * \return     pointeur vers une (nouvelle) image ne contenant que la zone de pixels voulue (rognée) 
 */
DonneesImageRGB* cropImageToRectangle(DonneesImageRGB* image, Rectangle rect);

/**
 * \brief      Effectue le prétraitement de l'image à analyser en améliorant certains de ses aspects
 * \details    Supression de pixels isolés (filtre médian), augmentation du contraste, "lissage" des couleurs (réduction de la palette)...
 * \param      image			L'image source.
 * \return	   le pointeur vers l'image (même qu'au départ)
 */
DonneesImageRGB* improveImage(DonneesImageRGB* image);

/**
 * \brief      Crée une copie redimensionnée d'une image (DonneesImageRGB) à des dimensions données.
 * \details    Crée une copie redimensionnée d'une image source (DonneesImageRGB) à des dimensions (largeur et hauteur) données.
 * \param      image			L'image source
 * \param      newWidth			La largeur de la nouvelle image.
 * \param      newHeight		Le hauteur de la nouvelle image.
 * \return     pointeur vers la nouvelle image 
 */
DonneesImageRGB* resizedCopy(DonneesImageRGB* image, int newWidth, int newHeight);

/**
 * \brief      Crée une copie de l'image source (DonneesImageRGB) affectée d'une rotation d'un angle donné.
 * \details    Crée une copie de l'image source (DonneesImageRGB) affectée d'une rotation d'un angle précisé (en degré). Les zones "vides" sont colorées de la couleur précisée.
 * \note	   Attention, les dimensions de la nouvelle image ne sont pas égales à celles de l'image source (sauf pour une rotation de 180°).
 * \param      image			L'image source
 * \param      angle_degre		L'angle de rotation en degré. (La rotation s'effectue dans le sens anti-trigonométrique).
 * \param      couleurFond		La couleur qui va remplacer les zones vides si besoin.
 * \return     pointeur vers la nouvelle image
 */
DonneesImageRGB* rotateImage(DonneesImageRGB* image, int angle_degre, Couleur couleurFond);

/**
 * \brief      
 * \details    
 * \param      image			L'image source
 * \param      tabY				Tableau d'entiers à remplir contenant les coordonées y des "espaces" verticaux dans l'image.
 * \param      couleurTexte		La couleur du fond dans l'image
 * \return     Le nombre de lignes de texte que l'image contient.
 */
int detectNbrLines(DonneesImageRGB* image, int* tabY, Couleur couleurTexte);

/**
 * \brief      
 * \details    
 * \param      image			L'image source
 * \param      couleurTexte		La couleur du texte dans l'image
 * \param      couleurFond		La couleur du fond dans l'image
 * \param      results			Tableau de mots utilisé pour obtenir les lettres etc.
 * \param      nbrDeLettres		Le nombre, au total, de lettres déterminé
 * \return     Le tableau des lettres, séparées.
 */
Lettre* separateLetters(DonneesImageRGB* image, Couleur couleurTexte, Couleur couleurFond, Mot** results, int* nbrDeLettres);

/**
 * \brief      Initialise et alloue un tableau de mots
 * \details    
 * \param      Aucun
 * \return     Pointeur vers le tableau de structures
 */
Mot** newTabMots();

/**
 * \brief      Détermine le plus petit rectangle contenant l'intégralité des pixels formant le texte
 * \details    
 * \param      image			L'image source.
 * \param      couleurTexte		La couleur du texte dans l'image
 * \return     Le rectangle déterminé.
 */
Rectangle getMinRect(DonneesImageRGB* image, Couleur couleurTexte);

/**
 * \brief      Crée une image matricielle à partir d'une image RGB source, connaissant la couleur du fond de l'image.
 * \details     
 * \param      image			L'image source.
 * \param	   couleurTexte		La couleur du texte dans l'image
 * \return	   Pointeur vers l'image matricielle
 */
imageMatricielle* getImageMatricielle(DonneesImageRGB* image, Couleur couleurTexte);

/**
 * \brief      Détermine le meilleur angle de rotation d'une image pour "horizontaliser" au mieux le texte à reconnaître
 * \details    
 * \param      image			L'image source.
 * \param      couleurFond		La couleur du fond de l'image
 * \param      couleurTexte		La couleur du texte dans l'image
 * \return     L'angle en degré
 */
int findBestAngle(DonneesImageRGB* image, Couleur couleurFond, Couleur couleurTexte);

/**
 * \brief      Compare une lettre reconnu dans l'image source à une lettre de la police, avec un indice de ressemblance
 * \details    L'algorithme compare binairement les images matricielles des deux caractères images et affecte un indice de ressemblance
 * \param      imgSrc					L'image matricielle source
 * \param      imgPolice				L'image matricielle d'un caractère de la police
 * \return     L'indice de ressemblance
 */
double compareLettres(imageMatricielle* imgSrc, imageMatricielle* imgPolice);

/**
 * \brief      Détecte les mots et lettres constituant une partie de l'image
 * \details    
 * \param      image			L'image source
 * \param      couleurTexte		La couleur RGB du texte
 * \param      results			Tableau de mots trouvés (à remplir)
 * \param      nbrDeMots		Le nombre de mots trouvés (à écrire)
 * \param      espaces			Tableau donnant la position des espaces
 * \return     0 si tout s'est bien passé, -1 sinon.
 */
int detectLettersAndWords(DonneesImageRGB* image, Couleur couleurTexte, Mot** results, int* nbrDeMots, int* espaces);

/**
 * \brief      Détecte la couleur de fond et la couleur du texte d'une image donnée.
 * \details    Détecte la couleur de fond et la couleur du texte d'une image donnée et les enregistre dans les valeurs pointées passées en paramètres.
 * \param      image			L'image source.
 * \param      fond				Pointeur vers la valeur de la couleur de fond.
 * \param      texte			Pointeur vers la valeur de la couleur du texte.
 * \return     
 */
void getBackgroundAndTextColor(DonneesImageRGB* image, Couleur* fond, Couleur* texte);

/**
 * \brief      Fonction de gestion des evenements du système graphique
 * \details    La fonction de gestion des événements, appelée automatiquement par le systeme graphique dès qu'une événement survient.
 * \param      evenement		L'événement en question.
 * \return     
 */
void gestionEvenement(EvenementGfx evenement);


// Fonctions de libération de la mémoire :

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      img			pointeur vers la structure à free.
 * \return     
 */
void freeImageRGB(DonneesImageRGB* img);

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      imgMat		pointeur vers la structure à free.
 * \return     
 */
void freeImageMat(imageMatricielle* imgMat);

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      ltr		pointeur vers la structure à free.
 * \return     
 */
void freeLettre(Lettre* ltr);

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      mot		pointeur vers la structure à free.
 * \return     
 */
void freeMot(Mot* mot);

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      lp		pointeur vers la structure à free.
 * \return     
 */
void freeLP(LettrePolice* lp);

/**
 * \brief      Libère proprement la mémoire allouée pour cette structure
 * \details    
 * \param      corr		pointeur vers la structure à free.
 * \return     
 */
void freeCorr(Correspondance* corr);
