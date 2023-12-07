#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

int bss; //variable statique non initialisée
int stat = 1; //Variable statique

void exo1(void* ptr) {
    int stack = 0; //Premiere variable dans la stack
    int *heap = (int *)malloc(10* sizeof(int)); //
    int pid = getpid();
    int *mmapptr = mmap ( NULL, 10*sizeof(int),
                      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
    char str[40];
    sprintf(str, "%d", pid); //On utilise sprintf pour crée la commande que l'on passe dans system
    printf("Localisation de data %p\n", &stat);
    printf("Localisation de BSS %p\n", &bss);
    printf("Localisation de STR %p\n", str);
    printf("Localisation de Heap %p\n", heap);
    printf("Localisation de Main (code memory) %p\n", ptr);
    printf("Localisation de stack %p\n", &stack);
    printf("Localisation de Libc %p\n", printf);
    printf("Localisation de MMAP %p\n", mmapptr);
    execlp("pmap", "pmap","-X", str);
    // Note : nous avons changer la manière d'executer le pmap : on passe par execlp, plus efficace (moins dappel a fork)
}

