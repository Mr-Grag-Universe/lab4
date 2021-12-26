//#pragma pack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CarStruct.c"
#include "KGetLine.h"
#include "FGetLine.h"
#include <unistd.h>

struct Car * generate(int n) {
    struct Car * cars = NULL;
    srand(time(NULL));
    cars = (struct Car *) malloc(sizeof(struct Car)*n);

    for (int i = 0; i < n; ++i) {
        char mark[17] = {0};
        char * name = NULL;
        long double mileage = 0;

        int size = rand()%16+1;
        for (int j = 0; j < size; ++j) {
            char x = rand()%2;
            mark[j] = (char)((int)(x ? 'A' : 'a') + rand() % 26);
        }
        mark[size] = '\0';

        size = rand()%50+10;
        name = (char*) malloc(sizeof(char)*(size+1));
        for (int j = 0; j < size; ++j) {
            char x = rand()%2;
            name[j] = (char)((int)(x ? 'A' : 'a') + rand() % 26);
        }

        mileage = rand()%10000000;

        memcpy(cars[i].mark, mark, 17);
        cars[i].name = name;
        cars[i].mileage = mileage;
    }
    return cars;
}

void generate_random_array(struct Car ** all_cars, int * number_of_cars) {

    printf("Input the number of new random cars.\nWarning!!! All your previous cars will be deleted.\n-> ");
	long long int n = 0;
	scanf("%lld", &n);

    struct Car * cars = *all_cars;

	for (int i = 0; i < *number_of_cars && cars; ++i) {
		free(cars[i].name);
	}

	*number_of_cars = n;
    *all_cars = generate(n);
}

void read_from_file(struct Car ** all_cars, int * number_of_cars) {
    printf("Enter the WHOLE path to your file.\n-> ");
    getchar();
    char *path = get_line();

    char *lines = f_get_lines(path);
    if (path) free(path);
    
    if (lines == NULL || lines[0] == '\0') {
        if (lines) free(lines);
        printf("Empty file.\n");
        sleep(1);
        return;
    }
    char *line = NULL;
    char **cars_in_lines = (char **) malloc(0);
    int nonc = 0;
    line = strtok(lines, "\n\0");
    do {
        nonc++;
        cars_in_lines = (char **) realloc(cars_in_lines, nonc * sizeof(char *));
        cars_in_lines[nonc - 1] = line;
        line = strtok(NULL, "\n\0");
    } while (line);

    //for (int i = 0; i < nonc; ++i) printf("%s\n", cars_in_lines[i]);
    for (int i = 0; i < nonc; ++i) {
        struct Car car;
        char *mark = strtok(cars_in_lines[i], ".;");
        for (int j = 0; j < 17; ++j) car.mark[j] = 0;
        int len = (int) strlen(mark);
        if (len > 16) len = 16;
        memcpy(car.mark, mark, len);
        //if (mark) free(mark);

        car.name = strtok(NULL, ".;");
        car.mileage = atof(strtok(NULL, ".;"));

        if (*number_of_cars)
            *all_cars = (struct Car *) realloc(*all_cars, sizeof(struct Car) * (*number_of_cars + 1));
        else
            *all_cars = (struct Car *) malloc(sizeof(struct Car) * (*number_of_cars + 1));
        (*number_of_cars) += 1;
        (*all_cars)[*number_of_cars - 1] = car;
    }
    
    //for (int i = 0; i < nonc; ++i)
        //if (cars_in_lines[i])
            //free(cars_in_lines[i]);
    //free(cars_in_lines);
    free(lines);
}

inline void clrscr(){
    system("@cls||clear");
}

void read_from_terminal(struct Car ** all_cars, int * number_of_cars) {
    clrscr();
    scanf("%*c");

    printf("How many cars do you wanna enter?\n");
    int n = 0;
    printf("Number of new cars: ");
    while(scanf("%d", &n) <= 0) {
        //scanf("*")
        scanf("%*s");
        printf("Error!!!\n->");
    }

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
            free(mark_t);
            mark_t = get_line();
        }
        //char mark[17] = {0};
        //memcpy(mark, mark_t, strlen(mark_t));
        //for (int j = (int) strlen(mark_t); j < 18; ++j) mark[j] = '\0';

        char * name;
        printf("Name of %d car: ", i+1);
        name = get_line();

        long double mileage = 0;
        printf("Car's mileage: ");
        while (scanf("%Lf", &mileage) <= 0) {
            scanf("%*s");
            printf("Error!!!\n->");
        }
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