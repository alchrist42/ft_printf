#include "ft_printf.h"

/*
**	@brief	print character n times
**	
**	@param	c		character
**	@param	n		counter to print
**	@return	int		counter printed characters
*/
int	ft_putnchar(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

/*
**	@brief	counts lenght integer by its base
**	
**	@param	n			integer
**	@param	b_len		base lenght
**	@param	flags		pointer to format specificator flags structure
**	@return	size_t		lenght
*/
size_t	ft_lennbr_base(long long n, size_t b_len, t_flag *flags)
{
	size_t	lennbr;

	if (n < 0)
		n = (unsigned long long)-n;
	lennbr = 0;
	if (!n && flags->accuracy)
		return (1);
	while (n)
	{
		lennbr++;
		n /= b_len;
	}
	return (lennbr);
}

/*
**	@brief	write nbr by any base to standart output
**	
**	@param	n		integer
**	@param	b_len	base len
**	@param	base	pointer to base string
**	@return	int		total printed characters
*/
int	ft_putnbr_base(unsigned long long n, size_t b_len, char *base)
{
	if (n < b_len)
		return (ft_putnchar(base[n], 1));
	return (ft_putnbr_base(n / b_len, b_len, base)
		+ ft_putnchar(base[n % b_len], 1));
}

/*
**	@brief		Inicialize format specificator flags and fill first two
**	
**	@param	s			pointer to format specificator string
**	@param	flags		pointer to format specificator flags structure
**	@return	const char*	pointer to next args in string
*/
const char	*ft_inicialize_flags(const char *s, t_flag *flags)
{
	flags->minus = false;
	flags->zeros = false;
	flags->dot = false;
	flags->len = -1;
	flags->accuracy = -1;
	while (*++s)
	{
		if (*s == '-')
			flags->minus = true;
		else if (*s == '0')
			flags->zeros = true;
		else
			break ;
	}
	return (s);
}

/*
**	@brief	Fills format specificator flags
**	
**	@param	s		pointer to format specificator string
**	@param	args	type for getting uncountable args
**	@param	flags	pointer to format specificator flags structure
*/
void	ft_get_flags(const char *s, va_list args, t_flag *flags)
{
	s = ft_inicialize_flags(s, flags);
	if (*s && *s == '*')
	{
		flags->len = va_arg(args, int);
		if (flags->len < 0)
		{
			flags->len = -flags->len;
			flags->minus = true;
		}
	}
	else if (*s && ft_isdigit(*s))
		flags->len = atoi(s);
	while (ft_isdigit(*s) || *s == '*')
		s++;
	if (*s++ == '.')
	{
		flags->dot = true;
		flags->accuracy = 0;
		if (*s == '*')
			flags->accuracy = va_arg(args, int);
		else
			flags->accuracy = atoi(s);
	}
}
