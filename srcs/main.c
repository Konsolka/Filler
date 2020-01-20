#include "../includes/filler.h"
#include "../includes/libft.h"

int		main(void)
{
	char	kek[16] = "<got (O): [8, 2]";

	printf("%i", atoi(strrchr(kek, ' ')));
	return (0);
}