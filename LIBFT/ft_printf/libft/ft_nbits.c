int	ft_nbits(unsigned int nbr)
{
	int i;

	i = 1;
	while (nbr >>= 1)
		i++;
	return (i);
}
