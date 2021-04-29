#include "ft_printf.h"

int	ft_spec_switcher_part2(const char *s, va_list args, t_flag *flags, size_t *total)
{
	if (*s == 'l' && *(s + 1) != 'l')
		*total += ft_print_nbr_base(flags, va_arg(args, int), "0123456789");
	if (*s == 'l' && *(s + 1) == 'l')
		*total += ft_print_nbr_base(flags,
				va_arg(args, long long), "0123456789abcdef");
	else
		return (1);
	return (0);
}

int	ft_spec_switcher(const char *s, va_list args, t_flag *flags, size_t *total)
{
	if (*s == 's')
		*total += ft_print_string(flags, va_arg(args, char *));
	else if (*s == 'c')
		*total += ft_print_char(flags, va_arg(args, int));
	else if (*s == 'p')
		*total += ft_print_addr(flags, va_arg(args, unsigned long long));
	else if (*s == 'i' || *s == 'd')
		*total += ft_print_nbr_base(flags, va_arg(args, int), "0123456789");
	else if (*s == 'x')
		*total += ft_print_nbr_base(flags,
				va_arg(args, unsigned int), "0123456789abcdef");
	else if (*s == 'X')
		*total += ft_print_nbr_base(flags,
				va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (*s == 'u')
		*total += ft_print_nbr_base(flags,
				va_arg(args, unsigned int), "0123456789");
	else if (*s == '%')
		*total += ft_print_char(flags, '%');
	else
		return (ft_spec_switcher_part2(s, args, flags, total));
	return (0);
}

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
	if (s[i] == 'l' && s[i + 1] == 'l')
		i--;
	return (i + 1);
}

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
