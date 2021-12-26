//
// Created by Stephan on 01.12.2021.
//

#include "Sorts.h"
#include "InputFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include "CarStruct.c"
#include "Comporators.h"

void timing() {
    printf("What sort's timing do you wanna check?\n");
    printf("1) Gnome Sort  |  2) Insert Sort with binary search  |  3) Radix Sort\n->");
    int n = 0;
    while (scanf("%d", &n) < 0) {
        scanf("%*s");
        printf("Error\n");
    }
    if (n > 3 || n < 1) return;

    printf("What thing we will sort?\n");
    printf("1) Marks  |  2) Names of owners  |  3) Mileages\n->");
    int par = 0;
    while (scanf("%d", &par) < 0) {
        scanf("%*s");
        printf("Error\n");
    }
    if (par > 3 || par < 1) return;
    par--;

    int (*comp[3])(const void*, const void*) = {comp_mark, comp_name, comp_mileage};
    long double times_mileage[10];
    for (int i = 0; i < 10; ++i) {
        long double middle = 0;
        int number = (i+1)*10000;
        for (int j = 0; j < 8; ++j) {
            struct Car * cars = generate(number);
            clock_t start, finish;
            switch ((int) n) {
                case 1:
                    start = clock();
                    gnome_sort(cars, number, sizeof(struct Car), comp[par]);
                    finish = clock();
                    break;
                case 2:
                    start = clock();
                    insertionSort(cars, number, sizeof(struct Car), comp[par]);
                    finish = clock();
                    break;
                case 3:
                    start = clock();
                    radix_sort_uni(cars, number, sizeof(struct Car), (char) par);
                    finish = clock();
                    break;
            }
            for (int k = 0; k < number; ++k) free(cars[k].name);
            free(cars);
            middle = (middle+(finish-start))/2;
            printf("%Lf, %d\n", middle, j);
        }
        times_mileage[i] = middle;
        printf("\n%Lf\n", times_mileage[i]);
    }
    for (int i = 0; i < 10; ++i) printf("%Lf\n", times_mileage[i]);
}
