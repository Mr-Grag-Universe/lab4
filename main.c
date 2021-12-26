#include <stdio.h>
#include "StartSession.h"
#include "MainCircle.h"
#include <stdlib.h>

int main() {
	printf("Hello, World!");
	
	char we_are_begining = start_session();
	if (!we_are_begining) return 0;
	
	main_circle();

	return 0;
}
