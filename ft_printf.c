#include "ft_printf.h"

/*
**	@brief	selects the format specificator
**	
**	@param	s		point to format specificator string
**	@param	args		type for getting uncountable args
**	@param	flags		format specificator attributes
**	@param	total		pointer to printed chars counter
**	@return	int			1 if found specificator. else 0
*/
int	ft_spec_switcher(const char *s, va_list args, t_flag *flags, size_t *total)
{
	if (*s == 's')
		*total += ft_print_string(flags, va_arg(args, char *));
	else if (*s == 'c')
		*total += ft_print_char(flags, va_arg(args, int));
	else if (*s == 'p')
		*total += ft_print_addr(flags, va_arg(args, unsigned long long));
	else if (*s == 'i' || *s == 'd')
		*total += ft_print_nbr(flags, va_arg(args, int), BASE10);
	else if (*s == 'x')
		*total += ft_print_nbr(flags, va_arg(args, unsigned int), BASE16L);
	else if (*s == 'X')
		*total += ft_print_nbr(flags, va_arg(args, unsigned int), BASE16U);
	else if (*s == 'u')
		*total += ft_print_nbr(flags, va_arg(args, unsigned int), BASE10);
	else if (*s == '%')
		*total += ft_print_char(flags, '%');
	else if (*s == 'n')
		*(unsigned long long *)va_arg(args, unsigned long long) = *total;
	else
		return (1);
	return (0);
}

/*
**	@brief	prints formated text by placeholder specification
**	
**	@param	s		point to format string
**	@param	args	type for getting uncountable args
**	@param	total	pointer to printed chars counter
**	@return	int		lenght parsed string
*/
int	ft_print_by_spec(const char *s, va_list args, size_t *total)
{
	size_t	i;
	t_flag	flags;

	ft_get_flags(s++, args, &flags);
	i = 0;
	while (s[i] && !ft_isalpha(s[i]) && s[i] != '%')
		i++;
	if (ft_spec_switcher(&s[i], args, &flags, total))
		return (-1);
	return (i + 1);
}

/*
**	@brief	A simple printf function
**	
**	@param	f		pointer to format string
**	@param	...		variadic arguments
**	@return	int		total printed chars
*/
int	ft_printf(const char *f, ...)
{
	va_list	args;
	int		j;
	size_t	total;

	va_start(args, f);
	total = 0;
	while (*f)
	{
		if (*f != '%')
			total += ft_putnchar(*f++, 1);
		else
		{
			j = ft_print_by_spec(f++, args, &total);
			if (j < 0)
			{
				va_end(args);
				return (-1);
			}
			else
				f += j;
		}
	}
	va_end(args);
	return (total);
}
