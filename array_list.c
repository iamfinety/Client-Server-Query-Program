#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array_list.h"

/*
 * initialize an array list
 */
ArrayList* alist_initialize(int maxarraysize, int dtsize){
	ArrayList* array = malloc(sizeof(ArrayList));
    array->arr = malloc(sizeof(void*) * maxarraysize); //mark
    array->size=0;
    array->maxSize = maxarraysize;
    array->itemSize = dtsize; //mark
    return array;
}

/*
 * add new item into arraylist
 */
bool alist_add(ArrayList* array,void* input){

    //int array[10];
	array->arr[array->size] = input;
	array->size++;
	return true;
}



/*
 * clear everything in the arraylist
 */
void alist_clear(ArrayList* array){
	if(array == NULL){
	}
	else{
		for(int i =0; i < array->size;i++){
			free(array->arr[i]);
			array->arr[i]=NULL;
		}
		array->size = 0;
	}
}

/*
 * get pokenmons at specific index
 */

void* alist_get(ArrayList* array,int index){
	if(array == NULL|| index < 0|| index >= array->maxSize){
        return NULL;
    }
    else{
        return array->arr[index];
    }
}
