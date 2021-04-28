#include "libftprintf.h"
#include <stdio.h> // todo del

int	ft_get_flags(const char *s, va_list args, t_flag *flags, size_t end)
{
	size_t	i;

	flags->minus = false;
	flags->zeros = false;
	flags->dot = false;
	flags->len = -1;
	flags->accuracy = -1;

	i = 0;
	while (i < end) //formating block
	{
		if (s[i] == '-')
			flags->minus = true;
		else if (s[i] == '0')
			flags->zeros = true;
		else
			break;
		i++;
	}
	if (i < end && s[i] == '*')
		flags->len = va_arg(args, int);
	else if (i < end && ft_isdigit(s[i]))
		flags->len = atoi(&s[i]);
	while (ft_isdigit(s[i]) || s[i] == '*')
		i++;
	if (s[i] == '.')
	{
		flags->dot = true;
		flags->accuracy = 0; // ?
		if (s[i + 1] == '*')
			flags->accuracy = va_arg(args, int);
		else
			flags->accuracy = atoi(&s[i + 1]);
	}
	// printf("\nFlags %.*s:\n\tminus %7i\n\tzeros %7i\n\tdot   %7i\n\tlen   %7i\n\taccur %7i\n", (int)end, s, flags->minus, flags->zeros, flags->dot, flags->len, flags->accuracy);
	return (0);
}

int	ft_print_by_spec(const char *s, va_list args, size_t *total)
{
	size_t	i;
	t_flag	flags;

	i = 0;
	while (s[i] && !ft_isalpha(s[i]) && s[i] != '%')
		i++;
	ft_get_flags(s, args, &flags, i);
	if (s[i] == 's')
		*total += ft_print_string(&flags, va_arg(args, char *));
	else if (s[i] == 'c')
		*total += ft_print_char(&flags, va_arg(args, int));
	else if (s[i] == 'i' || s[i] == 'd')
		*total += ft_print_nbr(&flags, va_arg(args, int));
	else if (s[i] == 'p')
		*total += ft_print_addr(&flags, va_arg(args, unsigned long long));
	else if (s[i] == 'x')
		*total += ft_print_nbr_base(&flags, va_arg(args, unsigned int), "0123456789abcdef");
	else if (s[i] == 'X')
		*total += ft_print_nbr_base(&flags, va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (s[i] == 'u')
		*total += ft_print_nbr_base(&flags, va_arg(args, unsigned int), "0123456789");
	else if (s[i] == '%')
		*total += ft_print_char(&flags, '%');
	else
		return (-1);
	return (i + 1);
}

int	ft_printf(const char *f, ...)
{
	va_list	args;
	size_t	i;
	int		j;
	size_t	total;

	va_start(args, f);
	i = 0;
	total = 0;
	while (f[i])
		if (f[i] != '%')
			total += ft_putnchar(f[i++], 1);
		else
		{
			j = ft_print_by_spec(&f[++i], args, &total);
			if (j < 0)
			{
				va_end(args);
				return (-1);
			}
			else
				i += j;
		}
	va_end(args);
	return (total);
}