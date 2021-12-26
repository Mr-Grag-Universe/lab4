#include <string.h>
#include "CarStruct.c"

int comp_mark(const void * car1, const void * car2) {
    struct Car* c1 = (struct Car*) car1;
    struct Car* c2 = (struct Car*) car2;

    if (strcmp(c1->mark, c2->mark) > 0) return 1;
    if (strcmp(c1->mark, c2->mark) < 0) return -1;
    return 0;
}
int comp_name(const void * car1, const void * car2) {
    struct Car* c1 = (struct Car*) car1;
    struct Car* c2 = (struct Car*) car2;

    if (strcmp(c1->name, c2->name) > 0) return 1;
    if (strcmp(c1->name, c2->name) < 0) return -1;
    return 0;
}
int comp_mileage(const void * car1, const void * car2) {
    struct Car* c1 = (struct Car*) car1;
    struct Car* c2 = (struct Car*) car2;

    if (c1->mileage > c2->mileage) return -1;
    if (c1->mileage < c2->mileage) return 1;
    return 0;
}