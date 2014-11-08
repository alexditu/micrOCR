// Veuillez reporter tout commentaire a ghislain.oudinet@isen.fr

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WavLib.h"
#include "OutilsLib.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

#define PCM_ENCODING 1

//#define DEBUGMODE

// Fonction s'occupant de la liberation complete d'une structure DonneesSonWAV
void libereDonneesSonWAV(DonneesSonWAV **structure)
{
	if
		(structure != NULL)
	{
		if
			(*structure != NULL)
		{
			free((*structure)->donneesSonores);
			free(*structure);
		}
		*structure = NULL;
	}
}

// Fonction essayant de lire le fichier passe en parametre, et renvoyant une structure
//	contenant les informations du fichier sonore en cas de succes, NULL sinon
DonneesSonWAV *lisWAV(char *nom)
{
	DonneesSonWAV *donneesSonWAV = (DonneesSonWAV*)calloc(1, sizeof(DonneesSonWAV));
	bool toutOK = false;
	
	if (donneesSonWAV != NULL)
	{
		// donneesSonWAV != NULL

		FILE *fichierWAV;
		
		if ((fichierWAV = fopen(nom, "rb")) != NULL)
		{
			// fichierWAV != NULL
			int buffer4o = 0;
			char ID[4] = {0, 0, 0, 0};
			
			fread(&ID, 1, sizeof(ID), fichierWAV);

			// Si le header commence bien par 'RIFF'...
			if (ID[0] == 'R' && ID[1] == 'I' && ID[2] == 'F' && ID[3] == 'F')
			{
				fread(&buffer4o, 1, sizeof(buffer4o), fichierWAV); // On saute les 4 octets qui suivent
				fread(&ID, 1, sizeof(ID), fichierWAV);
				// Si ce qui suit contient bien 'WAVE'
				if (ID[0] == 'W' && ID[1] == 'A' && ID[2] == 'V' && ID[3] == 'E')
				{
					fread(&ID, 1, sizeof(ID), fichierWAV);
					// Si ce qui suit contient bien 'fmt '
					if (ID[0] == 'f' && ID[1] == 'm' && ID[2] == 't' && ID[3] == ' ')
					{
						short buffer2o;
						
						fread(&buffer4o, 1, sizeof(buffer4o), fichierWAV); // On saute les 4 octets qui suivent
						fread(&buffer2o, 1, sizeof(buffer2o), fichierWAV); // Lecture du codage des donnees
						// S'il n'y a pas de compression (encodage PCM)
						if (little16VersNatif(buffer2o) == PCM_ENCODING)
						{
							fread(&buffer2o, 1, sizeof(buffer2o), fichierWAV); // Lecture du nombre de canaux
							donneesSonWAV->nombreDeCanaux = little16VersNatif(buffer2o);
							fread(&buffer4o, 1, sizeof(buffer4o), fichierWAV); // Lecture de la frequence d'echantillonnage
							donneesSonWAV->frequenceEchantillonnage = little32VersNatif(buffer4o);
							fread(&buffer4o, 1, sizeof(buffer4o), fichierWAV); // On saute les 4 octets qui suivent
							fread(&buffer2o, 1, sizeof(buffer2o), fichierWAV); // On saute les 2 octets qui suivent
							fread(&buffer2o, 1, sizeof(buffer2o), fichierWAV); // Lecture du nombre de bits par canal
							donneesSonWAV->tailleEchantillon = little16VersNatif(buffer2o)>>3; // On passe d'un nombre de bits a un nombre d'octets
							fread(&ID, 1, sizeof(ID), fichierWAV);
							// Si ce qui suit contient bien 'data'
							if (ID[0] == 'd' && ID[1] == 'a' && ID[2] == 't' && ID[3] == 'a')
							{
								int tailleDesDonnees;
								int index; // Pour parcourir les donnees et s'assurer de leur endianness
								fread(&buffer4o, 1, sizeof(buffer4o), fichierWAV); // Lecture de la taille des donnees sonores
								tailleDesDonnees = little32VersNatif(buffer4o);
								
								donneesSonWAV->donneesSonores = malloc(tailleDesDonnees);
								fread(donneesSonWAV->donneesSonores, 1, tailleDesDonnees, fichierWAV);
								tailleDesDonnees /= donneesSonWAV->tailleEchantillon;
								donneesSonWAV->nombreEchantillonnages = tailleDesDonnees/donneesSonWAV->nombreDeCanaux;
								// Conversion eventuelle des donnees pour l'endianness
								if (donneesSonWAV->tailleEchantillon == 2)
								{
									for (index = 0; index < tailleDesDonnees; ++index)
									{
										((short*)(donneesSonWAV->donneesSonores))[index] = little16VersNatif(((short*)(donneesSonWAV->donneesSonores))[index]);
									}
								}
								else if (donneesSonWAV->tailleEchantillon == 4)
								{
									for (index = 0; index < tailleDesDonnees; ++index)
									{
										((int*)(donneesSonWAV->donneesSonores))[index] = little32VersNatif(((int*)(donneesSonWAV->donneesSonores))[index]);
									}
								}
								toutOK = true;
							}
						}
					}
				}
			}
			
			
			// Quoi qu'il arrive il faut fermer le fichier
			fclose(fichierWAV);
		}
		
		// Si tout ne s'est pas bien passe on libere les donnees son et on les met a NULL
		if (!toutOK)
		{
			free(donneesSonWAV);
			donneesSonWAV = NULL;
		}
	}
	
	return donneesSonWAV;
}
