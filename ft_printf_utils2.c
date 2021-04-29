#include "ft_printf.h"

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

int	ft_putnbr_base(unsigned long long n, size_t b_len, char *base)
{
	if (n < b_len)
		return (ft_putnchar(base[n], 1));
	return (ft_putnbr_base(n / b_len, b_len, base)
		+ ft_putnchar(base[n % b_len], 1));
}

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
