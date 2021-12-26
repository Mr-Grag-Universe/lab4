//
// Created by Stephan on 21.11.2021.
//
#include "CarStruct.c"
#include <stdlib.h>

#ifndef LAB4_INPUTFUNCTIONS_H
#define LAB4_INPUTFUNCTIONS_H
void read_from_terminal(struct Car ** all_cars, int * number_of_cars);
void read_from_file(struct Car ** all_cars, int * number_of_cars);
void generate_random_array(struct Car ** all_cars, int * number_of_cars);
struct Car * generate(size_t n);
#endif //LAB4_INPUTFUNCTIONS_H
