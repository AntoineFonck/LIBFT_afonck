#include <stdio.h>
#include "../libft.h"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int i;

		i = ft_atoi(argv[1]);
		printf("%d\n", i);
		ft_putstr("so far so good");
		ft_putchar('\n');
		ft_putstr(ft_itoa(i));
	}
	return(0);
}
