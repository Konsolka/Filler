#include "../includes/filler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
	char	kek[16] = "<got (O): [8, 2]";
	char	*lol;

	lol = strdup("[8, 2]");
	printf("%d", atoi(strchr(lol, '[') + 1));
	return (0);
}