#include <stdio.h>
#include <stdlib.h>
#include "CarStruct.c"
#include "KGetLine.h"

void save_data_to_file(struct Car * all_cars, int * number_of_cars) {
	printf("Enter your file path or name to save all data to it.\n");
    getchar();
    char * path = get_line();

    FILE * file = fopen(path, "w");
    for (int i = 0; i < *number_of_cars; ++i) {
        fprintf(file, "%s;%s;%Lf.\n", all_cars[i].mark, all_cars[i].name, all_cars[i].mileage);
    }
    free(path);
    fclose(file);
}

void output_to_terminal(struct Car * all_cars, int * number_of_cars) {
    //printf("skdkjsd");
    int n = *number_of_cars;

    for (int i = 0; i < n; ++i) {
        struct Car car = all_cars[i];
        printf("The %d car:\n", i);
        printf("Mark: %s\n", car.mark);
        printf("Name: %s\n", car.name);
        printf("Mileage: %Lf\n\n", car.mileage);
    }

    printf("Enter any key to continue.\n");
    getchar();
    char a[19];
    scanf("%s", a);
}