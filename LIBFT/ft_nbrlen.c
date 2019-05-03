int      ft_nbrlen(int n)
{
        int             nbdigits;

        nbdigits = 0;
        if (n == 0)
                return (1);
        if (n < nbdigits)
                nbdigits++;
        while (n != 0)
        {
                n = n / 10;
                nbdigits++;
        }
        return (nbdigits);
}
