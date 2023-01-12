#include "PPS.h"
#include "array_list.h"
#include "array_list.c"

//create two global variable
ArrayList * array_to_be_saved;
FILE * file_to_be_saved;
char file_names[1024] = "0";
int main() {

    //line 14 to 41 is to initialize server end (number may change after some modifications)
    int query_count = 0;
    FILE *fptr;
    fptr = step1_read_file(fptr);
    ArrayList * array_list = alist_initialize(800, sizeof(Pokemon));
    array_list = read_pokemons(fptr, array_list);
    printf("%d\n", array_list->size);
    //initialize ip address and port number
    char *ip = "127.0.0.1";
    int port = 80;

    //initialize server and client address
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    //initialize buffer
    char buffer[1024];
    int n;

    //using tcp
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0) {
        perror("Scoket error");
        exit(1);
    }

    printf("TCP server initialized successful!\n");


    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;//AF_INET means internet version 4
    server_addr.sin_port = port; //which we have already defined as 80
    server_addr.sin_addr.s_addr = inet_addr(ip); //which we have already defined "127.0.0.1"

    //line 44 to 52 below are going to bind server
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(n < 0) {
        perror("Binded falied\n");
        exit(1);
    }

    printf("Binded to the port number: %d\n", port);

    //line below is linten

    listen(server_sock, 5);
    printf("[PPS]Listening.....\n"); //server is waiting for the client

    //here we accept connection from the client

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[PPS]Client connected.\n");

    while(1){
        //recieve message from client
        bzero(buffer, 1024); // clean the data
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("[PPS]Server recieved: %s\n", buffer);

        //after recieving message from PQC
        //based on respone do following options
        
        if(strcmp(buffer, "Type") == 0) {
            bzero(buffer, 1024); // clean the data
            recv(client_sock, buffer, sizeof(buffer), 0);
            search_pokemon(array_list, buffer);
        }
        else if(strcmp(buffer, "Save") == 0) {
            bzero(buffer, 1024); // clean the data
            recv(client_sock, buffer, sizeof(buffer), 0);
            save_pokemon(buffer);
            strcat(file_names, ", ");
            strcat(file_names, buffer);
        }


        //send message to client
        if(strcmp(buffer, "Exit") == 0) {
            printf("[PPS]Server: User choice is %s\n", buffer);
            send(client_sock, &buffer, strlen(buffer), 0);
            break;
        }
        printf("[PPS]Server: User choice is %s\n", buffer);
        send(client_sock, &buffer, strlen(buffer), 0);
        query_count++;
    }
    close(client_sock);
    close(server_sock);
    printf("There are %d queries completed successfully during the session.\n", query_count);  
    printf("The names of new files created during the session are %s\n", file_names);
    return 0;
}



FILE * step1_read_file(FILE * fptr){
    //assume that the longest path does not exceed 200 characters
    char file_path[200];
    printf("Please enter the name of the file containing the Pokemon descriptions: \n");

    //read the path/name
    scanf("%s", file_path);
    fptr = fopen(file_path,"r");

    //verify if the file exists or path is correct
    while(fptr == NULL){

        //empty the buffer
        fflush(stdin);
        printf("Pokemon file is not found. Please enter the name of the file again or enter 1 to exit: \n");
        scanf("%s", file_path);
        //first verify if the user want to exit or continue
        if(strcmp(file_path, "1") == 0){
            exit(1);
        }
        else{
            fptr = fopen(file_path,"r");
        }
    }
    return fptr;
}


/*
 * Function: read_pokemons
 * Description: Reads csv lines from a file, creates pokenmons structures,
 *              store them in an array
 * Parameters:
 *   pokemon_csv: the pointer to the file to be read
 *   arraylist: where we store wll the pokemons
 * Returns:
 *   the number of pokemons read in from the file
*/
ArrayList * read_pokemons(FILE* fptr, ArrayList * arrayList) {

    char line[1024];
    //skip the first line by reading it first
    fgets(line, 1024, fptr);
    while (fgets(line, 1024, fptr)) {

        Pokemon *pokemon = malloc(sizeof(Pokemon));
        //read data and store it in a pokemon
        pokemon->number = atoi(strtok(line, ","));
        strcpy(pokemon->name, strtok(NULL, ","));
        strcpy(pokemon->type1, strtok(NULL, ","));
        strcpy(pokemon->type2, strtok(NULL, ","));
        pokemon->total = atoi(strtok(NULL, ","));
        pokemon->hp = atoi(strtok(NULL, ","));
        pokemon->attack = atoi(strtok(NULL, ","));
        pokemon->defense = atoi(strtok(NULL, ","));
        pokemon->atk = atoi(strtok(NULL, ","));
        pokemon->def = atoi(strtok(NULL, ","));
        pokemon->speed = atoi(strtok(NULL, ","));
        pokemon->generation = atoi(strtok(NULL, ","));
        pokemon->legendary = strtok(NULL, ",");

        //add it to arraylist
        alist_add(arrayList, pokemon);
    }

    return arrayList;
}



/*
 * search pokemon by user choice
 */

ArrayList * search_pokemon(ArrayList * arrayList, char* type){
    array_to_be_saved = alist_initialize(800, 800);
    for(int i = 0; i < arrayList->size; i++){
        Pokemon * pokemon = alist_get(arrayList, i);
        if(strcmp(type, pokemon->type1) == 0){
            alist_add(array_to_be_saved, pokemon);
        }
    }
    return array_to_be_saved;
}

/*
 * search pokemon by user choice
 */

void save_pokemon(char * file_name){
    file_to_be_saved = fopen(file_name, "w+");
    for(int i = 0; i < array_to_be_saved->size; i++){
        Pokemon * temp_pokemon = alist_get(array_to_be_saved, i);
        char type_of_bool[200];
        if(temp_pokemon->legendary){
            strcpy(type_of_bool,"True");
        }
        else{
            strcpy(type_of_bool,"False");
        }

        fprintf(file_to_be_saved,"%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s\n",
                temp_pokemon->number,
                temp_pokemon->name,
                temp_pokemon->type1,
                temp_pokemon->type2,
                temp_pokemon->total,
                temp_pokemon->hp,
                temp_pokemon->attack,
                temp_pokemon->defense,
                temp_pokemon->atk,
                temp_pokemon->def,
                temp_pokemon->speed,
                temp_pokemon->generation,
                type_of_bool
                );
    }
}