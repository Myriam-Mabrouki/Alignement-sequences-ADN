#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DIST_2.h"
#include "DIST_NAIF.h"
#include "PROG_DYN.h"

/*
  Entrée: deux mots x et y
  Renvoie la distance d'édition entre ces deux mots
 */
int DIST_2(char *x, char *y, int n, int m) {
  int a, b, c;
  int *lig1 = malloc((m + 1) * sizeof(int)); //ligne i - 1
  int *lig2 = malloc((m + 1) * sizeof(int)); //ligne i

  for (int j = 0; j < m + 1; j++) {
    lig1[j] = j * C_INS;
  }
  lig2[0] = 0;
  for (int i = 1; i < n + 1; i++) {
    //On initialise avec les coûts de suppression
    lig2[0] = i * C_DEL;
    for (int j = 1; j < m + 1; j++) {
      //On récupère le coût minimum
      a = lig1[j] + C_INS;
      b = lig2[j - 1] + C_DEL;
      c = lig1[j - 1] + csub(x[i - 1], y[j - 1]);
      lig2[j] = min(a, b, c);
    }
    //On récupère la ligne courante pour réitérer les calculs
    for (int k = 0; k < m + 1; k++) {
      lig1[k] = lig2[k];
    }
  }
  int distance = lig2[m];

  //Libération mémoire
  free(lig1);
  free(lig2);
  return distance;
}
