//
// Created by Stephan on 25.11.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarStruct.c"
#include "KGetLine.h"

void insert_f() {
    
}

void insert(struct Car ** all_cars, int * number_of_cars) {
    printf("Enter new car's data here.\n");
    printf("Mark: ");
    getchar();
    char * mark = NULL;
    do {
        while (mark == NULL || mark[0] == '\0') { mark = get_line(); }
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

    printf("Enter the index where you wanna insert this car: \n");
    int n = 0;
    do {
        while (scanf("%d", &n) <= 0) {
            getchar();
            printf("Error!\n->");
        }
        printf("\n");
        if (n > *number_of_cars || n < 0) { printf("Your index is out of range.\n->"); }
    } while (n > *number_of_cars || n < 0);

    (*number_of_cars)++;
    int noc = *number_of_cars;

    if (noc <= 1) {
	    (*all_cars) = (struct Car *) malloc(sizeof(struct Car)*noc);
    		memcpy((*all_cars)[0].mark, mark, 17);
            //(*all_cars)[0].mark[16] = '\0';
    		//(*all_cars)[0].name = name;
    		(*all_cars)[0].mileage = mileage;
            free(mark);
		return;
    }
    
    (*all_cars) = (struct Car *) realloc((*all_cars), sizeof(struct Car)*noc);
    memmove((*all_cars) + n+1, (*all_cars)+n, sizeof(struct Car)*(noc-n-1));

    (*all_cars)[n].mileage = mileage;
    (*all_cars)[n].name = name;
    memcpy((*all_cars)[n].mark, mark, 17);
    //(*all_cars)[n].mark[16] = '\0';

    free(mark);
}
