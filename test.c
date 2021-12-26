#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Rus");
	
	char * a = (char*) malloc(sizeof(char) * 1);
	a[0] = 'д';
	char * b = (char*) malloc(sizeof(char) * 1);
        b[0] = 'д';

	printf("++== %d\n", strcmp(a, b));

	printf("OK\n");
	return 0;
}
