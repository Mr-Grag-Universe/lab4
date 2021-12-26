#include "CarStruct.c"
#include <stdlib.h>

#ifndef SORTS
#define SORTS
void sort(struct Car ** all_cars, int number_of_cars, char index_of_sort);
void gnome_sort(void * first, size_t number, size_t size, int (*comparator) (const void*, const void*));
size_t binarySearch(void * cars, void * el, size_t number, size_t size, int (*comparator) (const void*, const void*));
void insertionSort(void * cars, size_t number, size_t size, int (*comparator) (const void*, const void*));
void radix_sort_uni(void * cars, size_t number, size_t size, char field);
void* el(void * first, size_t index, size_t * size_ell, char *** el_ptr, size_t max_len, char field);
#endif
