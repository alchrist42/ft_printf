#include "libftprintf.h"

int	ft_putnchar(char c, int n)
{
	size_t	i;

	i = 0;
	while(n-- > 0)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

size_t	ft_lennbr_base(long long n, int b_len)
{
	size_t	lennbr;

	lennbr = 0;
	if (!n)
		return (1);
	// if (n < 0)
	// 	lennbr++;
	while (n)
	{
		lennbr++;
		n /= b_len;
	}
	return (lennbr);
}

void	ft_putnbr_base_fd(long long n, int b_len, char *base)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		if (n > -b_len)
			ft_putchar_fd(base[-n], 1);
		else
		{
			ft_putnbr_base_fd(-(n / b_len), b_len, base);
			ft_putchar_fd(base[-(n % b_len)], 1);
		}
	}
	else
	{
		if (n < b_len)
			ft_putchar_fd(base[n], 1);
		else
		{
			ft_putnbr_base_fd(n / b_len, b_len, base);
			ft_putchar_fd(base[n % b_len], 1);
		}
	}
}

