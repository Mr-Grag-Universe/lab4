#ifndef MENU
#define MENU
struct Folder{
	char * name;
	struct Folder ** folders;
	struct Folder * previous;
	char ** functions;
};

struct Menu{
	struct Folder * root;
	struct Folder ** all_folders;
	int nof;
};
#endif