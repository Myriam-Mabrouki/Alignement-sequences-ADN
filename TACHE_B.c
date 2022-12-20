#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "DIST_NAIF.h"
#include "PROG_DYN.h"

int main(void) {

  int n = 0;
  int m = 0;
  char *x = NULL;
  char *y = NULL;
  int **tab = NULL;

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

    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    tab = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < n + 1; i++) {
      tab[i] = (int *)malloc((m + 1) * sizeof(int));
      for (int j = 0; j < (m + 1); j++) {
        tab[i][j] = 0;
      }
    }

    //Calcul de DIST_1 et SOL_1 et affichage
    int d = DIST_1(x, y, n, m, tab);
    printf("Distance d’édition : %d\n", d);
    Align *align = SOL_1(x, y, n, m, tab);
    print_align(align);

    //Libération mémoire
    free(x);
    free(y);
    for (int i = 0; i < n + 1; i++) {
      free(tab[i]);
    }
    free(tab);
    free_align(align);
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

    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    tab = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < n + 1; i++) {
      tab[i] = (int *)malloc((m + 1) * sizeof(int));
      for (int j = 0; j < (m + 1); j++) {
        tab[i][j] = 0;
      }
    }

    //Calcul de DIST_1 et SOL_1 et affichage
    int d = DIST_1(x, y, n, m, tab);
    printf("Distance d’édition : %d\n", d);
    Align *align = SOL_1(x, y, n, m, tab);
    print_align(align);

    //Libération mémoire
    free(x);
    free(y);
    for (int i = 0; i < n + 1; i++) {
      free(tab[i]);
    }
    free(tab);
    free_align(align);
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

    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);

    tab = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < n + 1; i++) {
      tab[i] = (int *)malloc((m + 1) * sizeof(int));
      for (int j = 0; j < (m + 1); j++) {
        tab[i][j] = 0;
      }
    }

    //Calcul de DIST_1 et SOL_1 et affichage
    int d = DIST_1(x, y, n, m, tab);
    printf("Distance d’édition : %d\n", d);
    Align *align = SOL_1(x, y, n, m, tab);
    print_align(align);

    //Libération mémoire
    free(x);
    free(y);
    for (int i = 0; i < n + 1; i++) {
      free(tab[i]);
    }
    free(tab);
    free_align(align);
    fclose(f);
  }


  // Ecriture dans le fichier
  printf("========== ECRITURE DANS LE FICHIER ==========\n\n");
  char nom_fic[256];

  //Ouverture/création des fichiers
  FILE *cpu = fopen("DIST_1.txt", "w");
  FILE *cpu2 = fopen("PROG_DYN.txt", "w");
  if (!cpu || !cpu2) {
    printf("Erreur à l'ouverture du fichier DIST_1.txt PROG_DYN.txt\n");
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
        FILE *f = fopen(nom_fic, "r");
        if (f == NULL) {

          //Ouverture/création du fichier
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

          x = (char *)malloc(sizeof(char) * (n + 1));
          y = (char *)malloc(sizeof(char) * (m + 1));
          for (int i = 0; i < n; i++) {
            fscanf(f, "%s \n", &x[i]);
          }
          for (int i = 0; i < m; i++) {
            fscanf(f, "%s \n", &y[i]);
          }

          //Lecture des mots et de leur taille
          tab = (int **)malloc((n + 1) * sizeof(int *));
          for (int i = 0; i < n + 1; i++) {
            tab[i] = (int *)malloc((m + 1) * sizeof(int));
            for (int j = 0; j < (m + 1); j++) {
              tab[i][j] = 0;
            }
          }

          //Calcul de DIST_1 et SOL_1 et écriture dans les fichiers
          clock_t before = clock();
          DIST_1(x, y, n, m, tab);
          clock_t end_dist_1 = clock() - before;
          Align * align = SOL_1(x, y, n, m, tab);
          clock_t end_sol1_1 = clock() - before;
          int msec1 = end_dist_1 * 1000 / CLOCKS_PER_SEC;
          int msec2 = end_sol1_1 * 1000 / CLOCKS_PER_SEC;
          fprintf(cpu, "%d %d\n", n, msec1);
          fprintf(cpu2, "%d %d\n", n, msec2);

          //Libération mémoire
          free(x);
          free(y);
          for (int i = 0; i < n + 1; i++) {
            free(tab[i]);
          }
          free(tab);
          free_align(align);
        }
        fclose(f);
      }
    }
    closedir(rep);
  } else {
    printf("Erreur répertoire");
    exit(EXIT_FAILURE);
  }
  printf("Fin : Regarder DIST_1.txt et PROG_DYN.txt\n");
  fclose(cpu);
  fclose(cpu2);

  return 0;
}
