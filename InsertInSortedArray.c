#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "KGetLine.h"
#include "CarStruct.c"
#include "Comporators.h"

//[-1/0/1, -1/0/1, -1/0/1]
//-1 по убыванию
//0 не отсортирован
//1 по возрастанию
void is_arr_sorted(char * sorted, struct Car * cars, int number_of_cars) {
    int s1 = 0, s2 = 0;
    size_t size = sizeof(struct Car);
    for (int i = 0; i < number_of_cars-1; ++i) {
        void * p1 = (void*) ((size_t) cars + size*(i+1));
        void * p2 = (void*) ((size_t) cars + size*i);

        if (comp_mark(p1, p2)) s1++;
        else s2++;
        if (s2*s1) break;
    }
    if (s2*s1) sorted[0] = 0;
    else if (s1) sorted[0] = 1;
    else sorted[0] = -1;

    s1 = 0; s2 = 0;
    for (int i = 0; i < number_of_cars-1; ++i) {
        void * p1 = (void*) ((size_t) cars + size*(i+1));
        void * p2 = (void*) ((size_t) cars + size*i);

        if (comp_name(p1, p2)) s1++;
        else s2++;
        if (s2*s1) break;
    }
    if (s2*s1) sorted[1] = 0;
    else if (s1) sorted[1] = 1;
    else sorted[1] = -1;

    s1 = 0; s2 = 0;
    for (int i = 0; i < number_of_cars-1; ++i) {
        void * p1 = (void*) ((size_t) cars + size*(i+1));
        void * p2 = (void*) ((size_t) cars + size*i);

        if (comp_mileage(p1, p2)) s1++;
        else s2++;
        if (s2*s1) break;
    }
    if (s2*s1) sorted[2] = 0;
    else if (s1) sorted[2] = 1;
    else sorted[2] = -1;
}

inline size_t binarySearch(void * cars, void * el, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    size_t left = 0, right = number;
    while (left != right) {
        size_t m = (left+right)/2;
        void * p = (void*) ((size_t) cars + size*m);
        if (comparator(el, p) > 0) left = m + 1;
        else if (comparator(el, p) < 0) right = m;
        else return m;
    }
    return left;
}

void insert_in_sorted_array(struct Car ** all_cars, int * number_of_cars) {
	printf("Enter new car's data here.\n");
    printf("Mark: ");
    getchar();
    char * mark;
    do {
        mark = get_line();
        if (strlen(mark) > 16) printf("Your mark is too long (<17 symbols).\n->");
        //scanf("%*c");
    } while (strlen(mark) > 16);

    printf("Name: ");
    char * name = get_line();
    printf("Mileage: ");
    long double mileage = 0;
    char fl = 0;
    do {
        fl = scanf("%Lf", &mileage);
        if (fl <= 0) {
            scanf("%*s");
            printf("Worse enter. Try again.\n->");
        }
    } while (fl <= 0);

    int noc = *number_of_cars;

    //analysis of array
    char is_sorted[3];
    is_arr_sorted(is_sorted, *all_cars, *number_of_cars);
    char all_ways = abs(is_sorted[0]) + abs(is_sorted[1]) + abs(is_sorted[2]);
    
    if (all_ways == 0) {
        printf("This array isn't sorted. Please, sort it and try again.\n");
        sleep(3);
        free(name);
        free(mark);
        return;
    }

    printf("This array is sorted with:\n");
    if (is_sorted[0]) printf("->marks\n");
    if (is_sorted[1]) printf("->names\n");
    if (is_sorted[2]) printf("->mileage\n");

    //выбор по какому параметру вставить
    int chose = 0;
    if (all_ways > 1) {
        printf("Enter the number of the way you wanna insert this car: ");
        while (scanf("%d", &chose) <= 0) { getchar(); printf("Error!\n"); }
        if (chose > all_ways) {
            printf("Your command impossible.\n");
            sleep(1);
            return;
        }

        for (int i = 0; i < 3; ++i) if (is_sorted[i] == 0) chose++;
        chose--;

    }
    else {
        for (int i = 0; i < 3; ++i)
            if (is_sorted[i])
                chose = i;
    }

    struct Car car;
    car.mileage = mileage;
    car.name = name;
    memcpy(car.mark, mark, 17);
    free(mark);

    int (*comp[3])(const void*, const void*) = {comp_mark, comp_name, comp_mileage};
    int n = (int) binarySearch(*all_cars, &car, noc, sizeof(car), comp[chose]);
    printf("%d\n", n);

    noc++;
    *number_of_cars = noc;
    (*all_cars) = (struct Car *) realloc((*all_cars), sizeof(struct Car)*noc);
    
    memmove((*all_cars)+n+1, (*all_cars)+n, sizeof(struct Car)*(noc-n-1));
    getchar();

    (*all_cars)[n] = car;
}