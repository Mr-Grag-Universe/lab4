#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CarStruct.c"

void erase(struct Car ** all_cars, int * number_of_cars) {
	getchar();
	printf("Enter the index from where you wanna erase elements.\n");
	int ind = *number_of_cars;
	while (ind > (*number_of_cars)-1) {
		while (scanf("%d", &ind) <= 0) {
			getchar();
			printf("Error!\n");
		}
	}
	printf("Enter the number of cars you wanna erase elements.\n");
	int number = -1;
	while ((scanf("%d", &number) <= 0) && (number < 0 || number + ind < *number_of_cars)) {
		getchar();
		printf("Error!\n");
	}

	memmove((*all_cars) + ind, (*all_cars) + ind + number, sizeof(struct Car) * ((*number_of_cars)-ind-number));

	for (int i = 0; i < number; ++i)
		free(((*all_cars)[(*number_of_cars)-number+i]).name);

	(*all_cars) = (struct Car*) realloc((*all_cars), sizeof(struct Car)*((*number_of_cars)-number));
	(*number_of_cars) -= number;
}