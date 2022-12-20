#ifndef _DIVISER_POUR_REGNER_

#include "PROG_DYN.h"

Mot *MOT_GAPS(int k);
Mot *string_to_mot(char *s, int len);
void *concatenation_mots(Mot *a, Mot *b);
Align *ALIGN_LETTRE_MOT(char *x, char *y, int m);
int COUPURE(char *x, char *y, int n, int m);
Align *SOL_2(char *x, char *y, int n, int m);

#endif
