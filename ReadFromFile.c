//
// Created by Stephan on 21.11.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarStruct.c"
#include "KGetLine.h"
#include "FGetLine.h"
#include <unistd.h>
/*
void read_from_file(struct Car ** all_cars, int * number_of_cars) {
    printf("Enter the WHOLE path to your file.\n-> ");
    getchar();
    char * path = get_line();

    char * lines = f_get_lines(path, 'd');
    if (lines == NULL || lines[0] == '\0') {
        printf("Empty file.\n");
        sleep(1);
        return;
    }
    char * line = NULL;
    char ** cars_in_lines = (char**) malloc(0);
    int nonc = 0;
    line = strtok(lines, "\n\0");
    do {
        nonc++;
        cars_in_lines = (char**) realloc(cars_in_lines, nonc* sizeof(char*));
        cars_in_lines[nonc-1] = line;
        line = strtok(NULL, "\n\0");
    } while (line);
    for (int i = 0; i < nonc; ++i) printf("%s\n", cars_in_lines[i]);
    for (int i = 0; i < nonc; ++i) {
        struct Car car;
        char * mark = strtok(cars_in_lines[i], ".;");
        for (int j = 0; j < 17; ++j) car.mark[j] = 0;
        int len = (int) strlen(mark);
        if (len > 16) len = 16;
        memcpy(car.mark, mark, len);

        car.name = strtok(NULL, ".;");
        car.mileage = atof(strtok(NULL, ".;"));

        if (*number_of_cars)
            *all_cars = (struct Car*) realloc(*all_cars, sizeof(struct Car) * (*number_of_cars+1));
        else
            *all_cars = (struct Car*) malloc(sizeof(struct Car) * (*number_of_cars+1));
        (*number_of_cars) += 1;
        (*all_cars)[*number_of_cars-1] = car;
    }
}
*/