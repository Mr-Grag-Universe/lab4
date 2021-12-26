#pragma once
#include "MenuClass.c"

#ifndef MENU_FUNCTIONS
#define MENU_FUNCTIONS
struct Menu init_menu();
int number_of_folders(struct Folder folder);
int number_of_functions(struct Folder folder);
void add_folder(char * name, char * host_name, struct Menu * menu);
struct Menu create_menu();
void add_function(char * name, struct Folder * f);
void delete_all_folders(struct Menu * menu);
void clear_root(struct Menu * menu);
void print_menu(struct Folder * f);
#endif
