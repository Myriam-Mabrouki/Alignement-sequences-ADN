#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DIST_NAIF.h"

/*
  Entrée: deux caractères a et b
  Renvoie le coût de substitution entre ces deux caractères
 */
int csub(char a, char b) {
  if (a == b) {
    return 0;
  } else if ((a == 'A' && b == 'T') || (a == 'G' && b == 'C') ||
             (a == 'T' && b == 'A') || (a == 'C' && b == 'G')) {
    return 3;
  }
  return 4;
}

/*
  Entrée: deux mots a et b, deux indices i et j, c le coût d'un alignement et dist le coût du meilleur alignement
  Renvoie le coût de meilleur alignement entre ces deux mots
 */
int DIST_NAIF_REC(char *x, char *y, int i, int j, int c, int dist) {
  if ((i == strlen(x)) && (j == strlen(y))) {
    if (c < dist)
      dist = c;
  } else {
    if ((i < strlen(x)) && (j < strlen(y))) {
      dist = DIST_NAIF_REC(x, y, i + 1, j + 1, c + csub(x[i], y[j]), dist);
    }
    if (i < strlen(x)) {
      dist = DIST_NAIF_REC(x, y, i + 1, j, c + C_DEL, dist);
    }
    if (j < strlen(y)) {
      dist = DIST_NAIF_REC(x, y, i, j + 1, c + C_INS, dist);
    }
  }
  return dist;
}

/*
  Entrée: deux mots a et b
  Renvoie le coût de meilleur alignement entre ces deux mots
 */
int DIST_NAIF(char *x, char *y) {
  return DIST_NAIF_REC(x, y, 0, 0, 0, INT_MAX);
}
