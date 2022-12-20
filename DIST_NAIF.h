#ifndef _DIST_NAIF_H_
#define _DIST_NAIF_H_

#define C_DEL 2
#define C_INS 2

int csub(char a, char b);
int DIST_NAIF_REC(char *x, char *y, int i, int j, int c, int dist);
int DIST_NAIF(char *x, char *y);

#endif
