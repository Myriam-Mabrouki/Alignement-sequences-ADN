CFLAGS = -g -w

PROGRAMS = TACHE_A TACHE_B TACHE_C TACHE_D

.PHONY:	all clean

all: $(PROGRAMS)

TACHE_A: DIST_NAIF.o TACHE_A.o
	gcc -o $@ $(CFLAGS) $^

TACHE_B: DIST_NAIF.o PROG_DYN.o TACHE_B.o
	gcc -o $@ $(CFLAGS) $^

TACHE_C: DIST_NAIF.o DIST_2.o PROG_DYN.o TACHE_C.o 
	gcc -o $@ $(CFLAGS) $^

TACHE_D: DIST_NAIF.o DIST_2.o PROG_DYN.o DIVISER_POUR_REGNER.o TACHE_D.o 
	gcc -o $@ $(CFLAGS) $^

DIST_NAIF.o: DIST_NAIF.c
	gcc -c $(CFLAGS) DIST_NAIF.c

TACHE_A.o: TACHE_A.c
	gcc -c $(CFLAGS) TACHE_A.c

PROG_DYN.o: PROG_DYN.c
	gcc -c $(CFLAGS) PROG_DYN.c

TACHE_B.o: TACHE_B.c
	gcc -c $(CFLAGS) TACHE_B.c
	
DIST_2.o: DIST_2.c
	gcc -c $(CFLAGS) DIST_2.c

TACHE_C.o: TACHE_C.c
	gcc -c $(CFLAGS) TACHE_C.c

DIVISER_POUR_REGNER.o: DIVISER_POUR_REGNER.c
	gcc -c $(CFLAGS) DIVISER_POUR_REGNER.c

TACHE_D.o: TACHE_D.c
	gcc -c $(CFLAGS) TACHE_D.c
	
clean:
	rm -f *.o $(PROGRAMS) *~
