int     ft_wcharlen(int nbbits)
{
        if (nbbits <= 7)
                return (1);
        else if (nbbits > 7 && nbbits <= 11)
                return (2);
        else if (nbbits > 11 && nbbits <= 16)
                return (3);
        else if (nbbits > 16)
                return (4);
        else
                return (-1);
}
