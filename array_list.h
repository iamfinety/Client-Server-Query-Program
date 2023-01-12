#ifndef __ARRAY_LIST_H
#define __ARRAY_LIST_H



typedef struct _AList {
		void** arr;
		int size;
		int maxSize;
		int itemSize;
		}ArrayList;

ArrayList* alist_initialize(int,int);
bool alist_add(ArrayList*,void*);
void alist_clear(ArrayList*);
void* alist_get(ArrayList*,int);

#endif
