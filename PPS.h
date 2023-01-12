#ifndef __PPS_H
#define __PPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "array_list.h"

#define MAXLENGTH 300
//type
typedef struct PokemonType {
    int number;
    char name[MAXLENGTH];
    char type1[MAXLENGTH];
    char type2[MAXLENGTH];
    int total;
    int hp;
    int attack;
    int defense;
    int atk;
    int def;
    int speed;
    int generation;
    bool legendary;
} Pokemon;



FILE *step1_read_file(FILE * );
ArrayList * read_pokemons(FILE *, ArrayList *);
ArrayList * search_pokemon(ArrayList *, char*);
void save_pokemon(char *);


#endif