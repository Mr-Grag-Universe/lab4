#include <stdio.h>
#include <stdlib.h>
#include "MenuCreation.h"
#include "MenuClass.c"
#include "FunctionsExecution.h"
#include <unistd.h>

void clrscr(){
    system("@cls||clear");
}

void end_session(){
	printf("Goodbye!\n");
	printf("Enter something to finish your work.\n");
	//getchar();//char * buf = get_line();
	sleep(1);
	clrscr();
	//free(buf);
}

void main_circle(){
	clrscr();
    char finish_session = 0;

	printf("Hello. It is the start menu of my app.\nWhat would you like to do the first?\n");
	//sleep(3);
	//getchar();

	struct Menu menu = create_menu();
	struct Folder * folder = menu.root;
	struct Car * all_cars = NULL;
	int number_of_cars = 0;
    	while (!finish_session) {
        	clrscr();
        	//printf("%s\n", folder->name);
        	print_menu(folder);
        
		int n = 0;
		int b = 0;
		if (scanf("%d", &n) <= 0) { 
			scanf("%*c");
			continue;
		}
		//while (scanf("%d", &n) <= 0) { getchar(); printf("Error!\n->"); }
	
		if (n == 0) {
			if (folder->previous)
				folder = folder->previous;
			else
				printf("This is the root!\n");
			continue;
		}

    		int nof = number_of_folders(*folder);
		if (n <= nof) {
			folder = folder->folders[n-1];
			continue;
		}

    		if (n > nof+ number_of_functions(*folder)) {
        		printf("Your command was out of range. Try again.\n");
        		sleep(1);
        		continue;
    		}

		finish_session = functions_execution(folder->functions[n-nof-1], &all_cars, &number_of_cars);
    	}

	clrscr();

    delete_all_folders(&menu);
    //printf("s;fkdjkjdf");
	clear_root(&menu);
	for (int i = 0; i < number_of_cars; ++i) free(all_cars[i].name);
	free(all_cars);

    end_session();
}
