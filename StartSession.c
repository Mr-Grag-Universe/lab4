#include <stdio.h>
#include <stdlib.h>
#include "KGetLine.h"
#include <string.h>
#include <ctype.h>
#include <locale.h>

char start_session() {
	setlocale(LC_ALL, "Rus");
	
	printf("\nHello, Dear User.\nDo you wanna activate this app? [Y/n]: ");
	
	char * answer = NULL;// = get_line();
	char * yes = "y";
	char * no = "n";
	char * ryes = "д";
	char * rno = "н";

	do {
		if (answer) {
			printf("Are you stupid?! It's definitely not [Y/n]. Please check your answer and retry.\n-->");
			free(answer);
		}
		answer = get_line();
		//while (strlen(answer) != 1) {
		//	printf("Are you stupid?! It's definly not [Y/n]. Please check your answer and retry or finish this process entering \"!\"\n-->");
		//	free(answer);
		//	answer = get_line();
		//}
		for (int i = 0, l = strlen(answer); i < l; ++i) answer[i] = tolower(answer[i]);
	} while (strcmp(answer, yes) && strcmp(answer, no) && strcmp(answer, ryes) && strcmp(answer, rno));

	//for (int i = 0, l = strlen(answer); i < l; ++i) answer[i] = tolower(answer[i]);
	
	if (!(strcmp(answer, yes) && strcmp(answer, ryes))) {
		printf("Wait for a second, please.\n");
		free(answer);
		return 1;
	}

	printf("Okey, goodbye!\n");
	free(answer);
	return 0;
}
