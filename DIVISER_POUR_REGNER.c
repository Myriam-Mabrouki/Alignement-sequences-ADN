#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DIST_2.h"
#include "DIST_NAIF.h"
#include "DIVISER_POUR_REGNER.h"
#include "PROG_DYN.h"

/*
  Entrée: un entier k
  Renvoie un mot k composé de k gaps
 */
Mot *MOT_GAPS(int k) {
  Mot *mot = malloc(sizeof(Mot));
  mot->first = NULL;
  mot->last = NULL;
  for (int i = 0; i < k; i++) {
    ajouter_en_queue('-', mot);
  }
  return mot;
}

/*
  Entrée: une chaîne de caractère s
  Convertis une chaîne de caractères s en une structure de mot
 */
Mot *string_to_mot(char *s, int len) {
  Mot *mot = malloc(sizeof(Mot));
  mot->first = NULL;
  mot->last = NULL;
  for (int i=0; i<len; i++) {
    ajouter_en_queue(s[i], mot);
  }
  return mot;
}

/*
  Entrée: deux mots a et b
  Concatène le mot b à a, puis supprime le mot b
 */
void *concatenation_mots(Mot *a, Mot *b) {
  if (a->last != NULL) {
    a->last->suiv = b->first;
  } else {
    a->first = b->first;
  }
  if (b->last != NULL) a->last = b->last;
  free(b);
}
/*
  Entrée: deux mots x et y
  Précondition: strlen(x) = 1
  Renvoie l'alignement de x et y
 */
Align *ALIGN_LETTRE_MOT(char *x, char *y, int m) {
  int cout_sub_min = csub(x[0], y[0]);
  int indice_sub_min = 0;
  Mot *a = NULL;
  Mot *b = NULL;

  for (int i = 1; i < m; i++) {
    if (cout_sub_min > csub(x[0], y[i])) {
      cout_sub_min = csub(x[0], y[i]);
      indice_sub_min = i;
    }
  }
  if (cout_sub_min > C_DEL + C_INS) {
    a = MOT_GAPS(m);
    ajouter_en_queue(x[0], a);
    b = string_to_mot(y, m);
    ajouter_en_queue('-', b);
  } else {
    a = MOT_GAPS(indice_sub_min);
    ajouter_en_queue(x[0], a);
    concatenation_mots(a, MOT_GAPS(m - indice_sub_min - 1));
    b = string_to_mot(y, m);
  }

  Align *xy = malloc(sizeof(Align));
  xy->x = a;
  xy->y = b;
  return xy;
}
/*
  Entrée: deux mots x et y
  Renvoie la coupure associée à y
 */
int COUPURE(char *x, char *y, int n, int m) {
  int a, b, c;
  int *lig1 = malloc((m + 1) * sizeof(int)); // i - 1 de D
  int *lig2 = malloc((m + 1) * sizeof(int)); // i de D
  int *lig3 = malloc((m + 1) * sizeof(int)); // i - 1 de I
  int *lig4 = malloc((m + 1) * sizeof(int)); // i de I

  int moitie = n / 2;

  for (int j = 0; j < m + 1; j++) {
    lig1[j] = j * C_INS;
    lig3[j] = j;
  }
  lig2[0] = 0;
  lig4[0] = 0;
  for (int i = 1; i < n + 1; i++) {
    //On initialise avec les coûts de suppression
    lig2[0] = i * C_DEL;
    for (int j = 1; j < m + 1; j++) {
      //On récupère le coût minimum
      a = lig1[j] + C_INS;
      b = lig2[j - 1] + C_DEL;
      c = lig1[j - 1] + csub(x[i - 1], y[j - 1]);
      lig2[j] = min(a, b, c);

      if (i > moitie) {
        if (lig2[j] == a) {
          lig4[j] = lig3[j];
        } else if (lig2[j] == b) {
          lig4[j] = lig4[j - 1];
        } else {
          lig4[j] = lig3[j - 1];
        }
      }
    }

    //On récupère les lignes courantes pour réitérer les calculs
    if (i > moitie) {
      for (int k = 0; k < m + 1; k++) {
        lig3[k] = lig4[k];
      }
    }
    for (int k = 0; k < m + 1; k++) {
      lig1[k] = lig2[k];
    }
  }
  int indice = lig4[m];
  //Libération mémoire
  free(lig1);
  free(lig2);
  free(lig3);
  free(lig4);
  return indice;
}

/*
  Entrée: deux mots x et y
  Renvoie un alignement minimal de (x,y)
 */
Align *SOL_2(char *x, char *y, int n, int m) {

  //Si x et y représentent le mot vide, on renvoie un alignement de mots vides
  if (n == 0 && m == 0) {
    Align *xy = malloc(sizeof(Align));
    xy->x = malloc(sizeof(Mot));
    xy->x->first = NULL;
    xy->x->last = NULL;
    xy->y = malloc(sizeof(Mot));
    xy->y->first = NULL;
    xy->y->last = NULL;
    return xy;
  }

  //Si x est un mot vide, on renvoie un alignement composé de y et de m gaps
  else if (n == 0) {
    Align *xy = malloc(sizeof(Align));
    xy->x = MOT_GAPS(m);
    xy->y = string_to_mot(y, m);
    return xy;
  }

  //Si y est un mot vide, on renvoie un alignement composé de x et de n gaps
  else if (m == 0) {
    Align *xy = malloc(sizeof(Align));
    xy->x = string_to_mot(x, n);
    xy->y = MOT_GAPS(n);
    return xy;
  } else if (n == 1) {
    return ALIGN_LETTRE_MOT(x, y, m);
  }

  //Si m = 1, on revoie la permutation des couples (x,y) donnés par la fonction ALIGN_LETTRE_MOT
  else if (m == 1) {
    Align *xy = ALIGN_LETTRE_MOT(y, x, n);
    Mot *tmp = xy->x;
    xy->x = xy->y;
    xy->y = tmp;
    return xy;
  }

  //On divise x et y en deux mots et on regarde l'alignement optimal qu'on peut obtenir sur ces sous-mots
  else {
    int i = n / 2;
    int j = COUPURE(x, y, n, m);
    char *a1 = malloc((i + 1) * sizeof(char));
    char *a2 = malloc((n - i + 1) * sizeof(char));
    for (int k = 0; k < i; k++) {
      a1[k] = x[k];
    }
    a1[i] = '\0';
    for (int k = i; k < n; k++) {
      a2[k - i] = x[k];
    }
    a2[n - i] = '\0';
    char *b1 = malloc((j + 1) * sizeof(char));
    char *b2 = malloc((m - j + 1) * sizeof(char));
    for (int k = 0; k < j; k++) {
      b1[k] = y[k];
    }
    b1[j] = '\0';
    for (int k = j; k < m; k++) {
      b2[k - j] = y[k];
    }
    b2[m - j] = '\0';
    Align *xy1 = SOL_2(a1, b1, i, j);
    Align *xy2 = SOL_2(a2, b2, n - i, m - j);
    concatenation_mots(xy1->x, xy2->x);
    concatenation_mots(xy1->y, xy2->y);
    Align *xy = malloc(sizeof(Align));
    xy->x = xy1->x;
    xy->y = xy1->y;

    //Libération mémoire
    free(a1); free(a2);
    free(b1); free(b2);
    free(xy1); free(xy2);
    return xy;
  }
}
