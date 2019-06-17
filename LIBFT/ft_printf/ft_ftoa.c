#include "../libft.h"
#include "ft_printf.h"

double ft_pow(double x, int y) {
    double r = 1;

    while (y > 0) {
        if (y & 1)
            r *= x;
        x *= x;
        y >>= 1;
    }
    return (r);
}

int ft_ftoa(double n, int afterpoint, int fd) 
{ 
	int len;
	int ipart;
	double fpart;
	int morezero;

	len = 0;
    // Extract integer part 
    	ipart = (int)n; 
    // Extract floating part 
    	fpart = n - (double)ipart;
	morezero = 0;

  	len += ft_nbrlen(ipart);
    // convert integer part to string 
    ft_putnbr_fd(ipart, fd);
  
    // check for display option after point 
    if (afterpoint != 0) 
    { 
        write(1, ".", 1);  // add dot 
	len++;  
	printf("fpart before pow = %f and len = %d\n", fpart, ft_nbrlen((int)fpart));
        fpart = fpart * ft_pow(10, afterpoint);
	morezero = afterpoint - ft_nbrlen((int)fpart);
	printf("fpart after pow = %f and len = %d\n", fpart, ft_nbrlen((int)fpart));
	if (morezero > 0)
		pad_zero(morezero, fd);
	if (fpart == 0)
	{
		len += afterpoint;
		pad_zero(afterpoint, fd);
	}
	else
	{
		len += ft_nbrlen((int)fpart);
        	ft_putnbr_fd((int)fpart, fd);
	}
    } 
	printf("len from ftoa = %d\n", len);
	return (len);
}

int ft_floatlen(double n)
{
	int len;
	int ipart;
	int fpart;

	len = 0;
	ipart = ((int)n);
	fpart = n - (double)ipart;
	len += ft_nbrlen(ipart);
	len += ft_nbrlen((int)fpart);
	printf("LEN IN FLOATLEN = %d\n", len);
	return (len);
}
