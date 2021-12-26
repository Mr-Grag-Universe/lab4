//
// Created by Stephan on 20.11.2021.
//
#include <stdio.h>
#include <string.h>
#include "../lab4/InputFunctions.h"
#include "../lab4/OutputFunctions.h"
#include "../lab4/WorkWithData.h"
#include "../lab4/Sorts.h"
#include "../lab4/Timing.h"

char functions_execution(char * name, struct Car ** all_cars, int * number_of_cars) {
    printf("%s\n", name);
    if (!strcmp(name, "EXIT")) return 1;
    else if (!strcmp(name, "Read data from the terminal window.")) read_from_terminal(all_cars, number_of_cars);
    else if (!strcmp(name, "Read data from a file.")) read_from_file(all_cars, number_of_cars);
    else if (!strcmp(name, "Generate random data.")) generate_random_array(all_cars, number_of_cars);
    else if (!strcmp(name, "Print cars to terminal.")) output_to_terminal(*all_cars, number_of_cars);
    else if (!strcmp(name, "Save data to file.")) save_data_to_file(*all_cars, number_of_cars);
    else if (!strcmp(name, "Insert a new car.")) insert(all_cars, number_of_cars);
    else if (!strcmp(name, "Delete several elements.")) erase(all_cars, number_of_cars);
    else if (!strcmp(name, "Insert a new car in the sorted array.")) insert_in_sorted_array(all_cars, number_of_cars);
    else if (!strcmp(name, "Gnome Sort.")) sort(all_cars, *number_of_cars, 0);
    else if (!strcmp(name, "Insert Sort.")) sort(all_cars, *number_of_cars, 1);
    else if (!strcmp(name, "Radix Sort.")) sort(all_cars, *number_of_cars, 2);
    else if (!strcmp(name, "Timing.")) timing();
    return 0;
}
