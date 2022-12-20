#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "DIST_NAIF.h"

int main(void) {

  int n = 0;
  int m = 0;
  char *x = NULL;
  char *y = NULL;

  // Validité
  printf("========== VALIDITE ==========\n\n");

  // Inst_0000010_44.adn
  //Ouverture/création du fichier
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

    //Calcul de DIST_NAIF et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);
    printf("Distance d’édition : %d\n\n", DIST_NAIF(x, y));

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Inst_0000010_7.adn
  //Ouverture/création du fichier
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

    //Calcul de DIST_NAIF et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);
    printf("Distance d’édition : %d\n\n", DIST_NAIF(x, y));

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Inst_0000010_8.adn
  //Ouverture/création du fichier
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

    //Calcul de DIST_NAIF et affichage
    printf("Mot x de longueur %d : %s\n", n, x);
    printf("Mot y de longueur %d : %s\n", m, y);
    printf("Distance d’édition : %d\n\n", DIST_NAIF(x, y));

    //Libération mémoire
    free(x);
    free(y);
    fclose(f);
  }

  // Instance prenant moins d'une minute
  printf("========== INSTANCE PRENANT MOINS D'UNE MINUTE ==========\n\n");
  char nom_fic[256];
  int msec = 0;
  int d;

  //On récupère les valeurs de l'instance précédente
  int d_avant;
  int n_avant = 0;
  int m_avant = 0;
  char *x_avant = NULL;
  char *y_avant = NULL;

  int first = 1;

  //Ouverture répertoire
  DIR *rep = opendir("./Instances_genome/");
  if (rep != NULL) {
    struct dirent *dir;
    while ( (dir = readdir(rep)) && (msec < 1000 * 60) ) {
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

          clock_t before = clock();
          d = DIST_NAIF(x, y);
          clock_t difference = clock() - before;
          printf("Distance d’édition : %d\n", d);
          msec = difference * 1000 / CLOCKS_PER_SEC;
          printf("Temps : %d s\n\n", msec / 1000);

          if (msec < 1000 * 60) {
            if (!first) {
              free(x_avant);
              free(y_avant);
            }
            n_avant = n;
            m_avant = m;
            x_avant = strdup(x);
            y_avant = strdup(y);
            d_avant = d;
            first = 0;
          }
          // Libération mémoire
          free(x);
          free(y);
        }
        fclose(f);
      }
    }
    printf("L'instance la plus grande calculable en moins d'une minute :\n");
    printf("Mot x de longueur %d : %s\n", n_avant, x_avant);
    printf("Mot y de longueur %d : %s\n", m_avant, y_avant);
    printf("Distance d’édition : %d\n", d_avant);

    // Libération mémoire
    free(x_avant);
    free(y_avant);
    closedir(rep);
  } else {
    printf("Erreur répertoire");
    exit(EXIT_FAILURE);
  }
  return 0;
}
