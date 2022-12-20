#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "DIST_2.h"
#include "DIST_NAIF.h"
#include "PROG_DYN.h"

int main(void) {
  int n = 0;
  int m = 0;
  char *x = NULL;
  char *y = NULL;

  // Validité
  printf("========== VALIDITE ==========\n\n");

  // Inst_0000010_44.adn
  FILE *f = fopen("./Instances_genome/Inst_0000010_44.adn", "r");
  if (f == NULL) {
    printf("Erreur à l'ouverture du fichier Inst_0000010_44.adn");
    exit(EXIT_FAILURE);
  } else {

    //Lecture des mots et de leur taille
    fscanf(f, "%d \n", &n);
    fscanf(f, "%d \n", &m);
    x = (char *)malloc(sizeof(char) * (n + 1));
    y = (char *)malloc(sizeof(char) * (m + 1));
    for (int i = 0; i < n; i++) {
      fscanf(f, "%s \n", &x[i]);
    }
    for (int i = 0; i < m; i++) {
      fscanf(f, "%s \n", &y[i]);
    }

    //Calcul de DIST_2 et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    int d = DIST_2(x, y, n, m);
    printf("Distance d’édition avec DIST_2 : %d\n", d);

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Inst_0000010_7.adn
  f = fopen("./Instances_genome/Inst_0000010_7.adn", "r");
  if (f == NULL) {
    printf("Erreur à l'ouverture du fichier Inst_0000010_7.adn");
    exit(EXIT_FAILURE);
  } else {

    //Lecture des mots et de leur taille
    fscanf(f, "%d \n", &n);
    fscanf(f, "%d \n", &m);
    x = (char *)malloc(sizeof(char) * (n + 1));
    y = (char *)malloc(sizeof(char) * (m + 1));
    for (int i = 0; i < n; i++) {
      fscanf(f, "%s \n", &x[i]);
    }
    for (int i = 0; i < m; i++) {
      fscanf(f, "%s \n", &y[i]);
    }

    //Calcul de DIST_2 et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    int d = DIST_2(x, y, n, m);
    printf("Distance d’édition avec DIST_2 : %d\n", d);

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Inst_0000010_8.adn
  f = fopen("./Instances_genome/Inst_0000010_8.adn", "r");
  if (f == NULL) {
    printf("Erreur à l'ouverture du fichier Inst_0000010_8.adn");
    exit(EXIT_FAILURE);
  } else {

    //Lecture des mots et de leur taille
    fscanf(f, "%d \n", &n);
    fscanf(f, "%d \n", &m);
    x = (char *)malloc(sizeof(char) * (n + 1));
    y = (char *)malloc(sizeof(char) * (m + 1));
    for (int i = 0; i < n; i++) {
      fscanf(f, "%s \n", &x[i]);
    }
    for (int i = 0; i < m; i++) {
      fscanf(f, "%s \n", &y[i]);
    }

    //Calcul de DIST_2 et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    int d = DIST_2(x, y, n, m);
    printf("Distance d’édition avec DIST_2 : %d\n", d);

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Ecriture dans le fichier
  printf("========== ECRITURE DANS LE FICHIER ==========\n\n");
  char nom_fic[256];

  //Ouverture/création du fichier
  FILE *cpu = fopen("DIST_2.txt", "w");
  if (!cpu) {
    printf("Erreur à l'ouverture du fichier DIST_2.txt\n");
    exit(EXIT_FAILURE);
  }

  //Ouverture répertoire
  DIR *rep = opendir("./Instances_genome/");
  if (rep != NULL) {
    struct dirent *dir;
    while ((dir = readdir(rep))) {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
        strcpy(nom_fic, "./Instances_genome/");
        strcat(nom_fic, dir->d_name);

        //Ouverture/création du fichier
        FILE *f = fopen(nom_fic, "r");
        if (f == NULL) {
          printf("Erreur à l'ouverture du fichier");
          exit(EXIT_FAILURE);
        } else {
          //Lecture des mots et de leur taille
          fscanf(f, "%d \n", &n);
          fscanf(f, "%d \n", &m);

          //On ne prend pas les instances supérieures à 50000
          if (n > 50000) {
            fclose(f);
            continue;
          }

          //Lecture des mots et de leur taille
          x = (char *)malloc(sizeof(char) * (n + 1));
          y = (char *)malloc(sizeof(char) * (m + 1));
          for (int i = 0; i < n; i++) {
            fscanf(f, "%s \n", &x[i]);
          }
          for (int i = 0; i < m; i++) {
            fscanf(f, "%s \n", &y[i]);
          }

          //Calcul de DIST_2 et écriture dans les fichiers
          clock_t before = clock();
          int d = DIST_2(x, y, n, m);
          clock_t difference = clock() - before;
          int msec = difference * 1000 / CLOCKS_PER_SEC;
          fprintf(cpu, "%d %d\n", n, msec);

          //Libération mémoire
          free(x);
          free(y);
        }
        fclose(f);
      }
    }
    closedir(rep);
  } else {
    printf("Erreur répertoire");
    exit(EXIT_FAILURE);
  }
  printf("Fin : Regarder DIST_2.txt\n");
  fclose(cpu);

  return 0;
}
