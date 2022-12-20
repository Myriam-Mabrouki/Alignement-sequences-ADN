#ifndef _PROG_DYN_H_
#define _PROG_DYN_H_

typedef struct elem {
  char c;
  struct elem *suiv;
} Elem;

typedef struct mot {
  Elem *first;
  Elem *last;
} Mot;

typedef struct align {
  Mot *x;
  Mot *y;
} Align;

int min(int a, int b, int c);
int DIST_1(char *x, char *y, int n, int m, int **tab);
void ajouter_en_tete(char a, Mot *mot);
void ajouter_en_queue(char a, Mot *mot);
Align *SOL_1(char *x, char *y, int n, int m, int **tab);
void print_align(Align *a);
void free_align (Align *a);

#endif
