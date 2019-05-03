#ifndef FT_PRINTF
# define FT_PRINTF
# define FALSE 0
# define TRUE 1

typedef struct s_converter 
{
	char format;
	int boolean;
	int (*fun_ptr)(va_list, int*);
}	t_converter;

#endif
