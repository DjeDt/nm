#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *str = "globale";

int main(int ac, char **av)
{
	char *c;
	if (ac < 2)
	{
		printf("need arg, abort.\n");
		return (-1);
	}
	size_t len = strlen(av[1]) + 1;
	c = malloc(len);
	strncpy(c, av[1], len);
	printf("prog: %s -> %s\n", av[0], c);
	printf("%s\n", str);
	free(c);
	return (0);
}
