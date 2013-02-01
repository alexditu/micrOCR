#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <search.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DICTIONARY "bigFR.txt"
#define DICT_SZ    3500000


// A appeler en premier lieu pour initialiser le spellchecker.
// Renvoie 1 si tout s'est bien passé, 0 sinon.
int initSpellCheck();

// Fonction "principale"
// Renvoie un char*, étant soit le mot originel si aucune correction n'est disponible, soit une proposition de correction
char* correct(char *word);
