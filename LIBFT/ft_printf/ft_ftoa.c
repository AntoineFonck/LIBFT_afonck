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

	len = 0;
    // Extract integer part 
    int ipart = (int)n; 
  	len += ft_nbrlen(ipart);
    // Extract floating part 
    double fpart = n - (double)ipart; 
  
    // convert integer part to string 
    ft_putnbr_fd(ipart, fd);
  
    // check for display option after point 
    if (afterpoint != 0) 
    { 
        write(1, ".", 1);  // add dot 
	len++;  
	printf("fpart before pow = %f and len = %d\n", fpart, ft_nbrlen((int)fpart));
        fpart = fpart * ft_pow(10, afterpoint); 
	printf("fpart after pow = %f and len = %d\n", fpart, ft_nbrlen((int)fpart));
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
