//
// Created by Stephan on 21.11.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "KGetLine.h"
#include <string.h>
#include "CarStruct.c"
/*
inline void clrscr(){
    system("@cls||clear");
}

void read_from_terminal(struct Car ** all_cars, int * number_of_cars) {
    clrscr();
    scanf("%*c");

    printf("How many cars do you wanna enter?\n");
    int n = 0;
    //if (scanf("Number of new cars: %d", &n) <= 0) printf("Error1!\n");
    printf("Number of new cars: ");
    scanf("%d", &n);

    int noc = *number_of_cars;
    if (*all_cars == NULL) *all_cars = (struct Car*) malloc(sizeof(struct Car) * (noc + n));
    else *all_cars = (struct Car*) realloc(*all_cars, sizeof(struct Car) * (noc + n));

    for (int i = 0; i < n; ++i) {
        clrscr();
        printf("Number of new cars: %d\n", n);

        char * mark_t;
        scanf("%*c");
        printf("Mark of %d car: ", i+1);
        //getchar();
        mark_t = get_line();
        while (strlen(mark_t) > 16) {
            printf("Too many letters in the mark. It must be less than 17. Retry, please.\n-> ");
            mark_t = get_line();
        }
        //char mark[17] = {0};
        //memcpy(mark, mark_t, strlen(mark_t));
        //for (int j = (int) strlen(mark_t); j < 18; ++j) mark[j] = '\0';

        char * name;
        printf("Name of %d car: ", i+1);
        name = get_line();

        long double mileage = 0;
        printf("Car's mileage: "); scanf("%Lf", &mileage);
        printf("\n");

        struct Car car;
        car.mileage = mileage;
        car.name = name;
        memcpy(car.mark, mark_t, strlen(mark_t));
        for (int j = (int) strlen(mark_t); j < 18; ++j) car.mark[j] = '\0';

        (*all_cars)[noc] = car;
        noc++;
        free(mark_t);
    }
    *number_of_cars = noc;
}
*/