#include "ft_printf.h"
#include "../libft.h"
#include <locale.h>

/*
   int main(void)
   {
   wchar_t s[] = L"இŵŢ";
   int mine;
   int real;

   setlocale(LC_ALL, "");

   mine = ft_printf("%43S", s);
   printf("\n");
   real = printf("%43S", s);
   printf("\nmy printf len = %d and real printf len = %d\n", mine, real);
   return (0);
   }
   */

int             main(int argc, char *argv[])
{
        if (argc == 4)
        {
                char *test;
                int myone;
                char hi;
                int realone;

                hi = 'h';
                test = &hi;
                //myone = ft_printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
                //myone = ft_printf(argv[1], ft_atol(argv[2]), argv[3], test);
                myone = ft_printf(argv[1], atof(argv[2]), argv[3][0], test);
                ft_putchar('\n');
                //realone = printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
                //realone = printf(argv[1], ft_atol(argv[2]), argv[3], test);
                realone = printf(argv[1], atof(argv[2]), argv[3][0], test);
                printf("\nmy printf len = %d and real printf len = %d\n", myone, realone);
        }
        return (0);
}

/*
int main()
{
	//long double test = 412343524354235.565321432514521413;

	ft_printf("%40.19Lf\n", test);
	printf("%40.19Lf\n", test);
	return(0);
}
*/
/*
   int main(int argc, char *argv[])
   {
   if (argc == 2)
   {
   int i;
   char test;
   int len1;
   int len2;

   i = 15643;
   test = 'O';
   len1 = ft_printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\nhallo %d\n0x55 = 0x%x\n", i, argv[1], test, (unsigned int)&i, 0x55);
   len2 = printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\nhallo %d\n0x55 = 0x%x\n", i, argv[1], test, (unsigned int)&i, 0x55);
   printf("ft_printf len == %d and printf len == %d", len1, len2);
   }
   return (0);
   }
   */
