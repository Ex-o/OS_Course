#include <stdio.h>
#include <stdlib.h>

int main() { // Fix 1
	char *s;
	char foo[] = "Hello World";
	s = foo;

	printf("s is %s\n", s);
	s[0] = foo[0];
	printf("s[0] is %c\n", s[0]);
	return 0;
}

int main() { //Fix 2
	char **s = (char**)malloc(sizeof(char**));
	char foo[] = "Hello World";
	*s = foo;
	
	printf("s is %s\n", *s);
	s[0] = foo;
	printf("s[0] is %s\n", s[0]);
	return 0;
}