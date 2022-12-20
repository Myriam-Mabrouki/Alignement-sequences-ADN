#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DIST_NAIF.h"
#include "PROG_DYN.h"

/**
  Entrée: a, b et c trois entiers
  Retourne le minimum entre ces 3 entiers
*/
int min(int a, int b, int c) {
  if ((a <= b) && (a <= c)) {
    return a;
  }
  if (b <= c) {
    return b;
  }
  return c;
}

/*
  Entrée: deux mots x et y
  Renvoie la distance d'édition entre ces deux mots
 */
int DIST_1(char *x, char *y, int n, int m, int **tab) {
  int a, b, c;

  if (n == 0 && m == 0)
    return 0;

  //On initialise avec les coûts de suppression
  for (int i = 1; i < n + 1; i++) {
    tab[i][0] = i * C_DEL;
  }
  //On initialise avec les coûts d'insertion
  for (int j = 1; j < m + 1; j++) {
    tab[0][j] = j * C_INS;
  }

  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < m + 1; j++) {
      //On récupère le coût minimum
      a = tab[i][j - 1] + C_INS;
      b = tab[i - 1][j] + C_DEL;
      c = tab[i - 1][j - 1] + csub(x[i - 1], y[j - 1]);
      tab[i][j] = min(a, b, c);
    }
  }
  return tab[n][m];
}

/**
  Entrée: a un caractère et mot un mot
  Ajoute le caractère a au début du mot
*/
void ajouter_en_tete(char a, Mot *mot) {
  Elem *e = malloc(sizeof(Elem));
  e->c = a;
  e->suiv = mot->first;
  mot->first = e;
  if (mot->last == NULL) mot->last = e;
}

/**
  Entrée: a un caractère et mot un mot
  Ajoute le caractère a à la fin du mot
*/
void ajouter_en_queue(char a, Mot *mot) {
  Elem *e = malloc(sizeof(Elem));
  e->c = a;
  e->suiv = NULL;
  if (mot->last != NULL) {
    mot->last->suiv = e;
  }
  mot->last = e;
  if (mot->first == NULL) mot->first = e;
}

/*
  Entrée: deux mots x et y
  Renvoie un alignement minimal de (x,y)
 */
Align *SOL_1(char *x, char *y, int n, int m, int **tab) {
  Mot *a = malloc(sizeof(Mot));
  a->first = NULL;
  a->last = NULL;
  Mot *b = malloc(sizeof(Mot));
  b->first = NULL;
  b->last = NULL;

  int i = n;
  int j = m;
  while (i > 0 || j > 0) {
    if ((i > 0) && (j > 0) && tab[i][j] == tab[i - 1][j - 1] + csub(x[i - 1], y[j - 1])) {
      ajouter_en_tete(x[i - 1], a);
      ajouter_en_tete(y[j - 1], b);
      i--;
      j--;
    } else if ((i > 0) && (tab[i][j] == tab[i - 1][j] + C_DEL)) {
      ajouter_en_tete(x[i - 1], a);
      ajouter_en_tete('-', b);
      i--;
    } else if ((j > 0) && (tab[i][j] == tab[i][j - 1] + C_INS)) {
      ajouter_en_tete('-', a);
      ajouter_en_tete(y[j - 1], b);
      j--;
    }
  }

  Align *xy = malloc(sizeof(Align));
  xy->x = a;
  xy->y = b;
  return xy;
}

/**
  Entrée: a un alignement
  Affiche l'alignement a
*/
void print_align(Align *a) {
  printf("Alignement obtenu :\n");
  Elem *current = a->x->first;
  while (current != NULL) {
    printf("%c", current->c);
    current = current->suiv;
  }
  printf("\n");
  current = a->y->first;
  while (current != NULL) {
    printf("%c", current->c);
    current = current->suiv;
  }
  printf("\n");
}

/**
  Entrée: a un alignement
  Libère la mémoire de l'alignement a
*/
void free_align (Align *a) {
  Elem *current;
  Elem *prec;

  current = a->x->first;
  while (current != NULL) {
    prec = current;
    current = current->suiv;
    free(prec);
  }

  current = a->y->first;
  while (current != NULL) {
    prec = current;
    current = current->suiv;
    free(prec);
  }
  free(a->x);
  free(a->y);
  free(a);
}
