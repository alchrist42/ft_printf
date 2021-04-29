#include "ft_printf.h"

int	ft_print_string(t_flag *flags, char *str)
{
	int		total;
	int		len;
	char	fil;
	int		i;

	total = 0;
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	fil = ' ';
	if (flags->zeros && !flags->minus)
		fil = '0';
	if (flags->accuracy > len || flags->accuracy <= -1)
		flags->accuracy = len;
	total += ft_putnchar(fil, !flags->minus * (flags->len - flags->accuracy));
	i = 0;
	while (i < flags->accuracy)
		total += ft_putnchar(str[i++], 1);
	total += ft_putnchar(fil, flags->minus * (flags->len - flags->accuracy));
	return (total);
}

int	ft_print_char(t_flag *flags, int ch)
{
	int		total;
	char	fil;

	total = 0;
	fil = ' ';
	if (flags->zeros && !flags->minus)
		fil = '0';
	if (flags->len == -1)
		flags->len = 1;
	total += ft_putnchar(fil, !flags->minus * (flags->len - 1));
	total += ft_putnchar(ch, 1);
	total += ft_putnchar(fil, flags->minus * (flags->len - 1));
	return (total);
}

int	ft_print_nbr(t_flag *flags, long long n, char *base)
{
	int		total;
	int		len;
	char	fil;

	total = 0;
	len = ft_lennbr_base(n, ft_strlen(base), flags);
	if (flags->accuracy < len)
		flags->accuracy = len;
	fil = ' ';
	if (!flags->dot && flags->zeros && !flags->minus)
		fil = '0';
	total += ft_putnchar('-', (fil == '0' && n < 0));
	total += ft_putnchar(fil, !flags->minus
			* (flags->len - flags->accuracy - (n < 0)));
	total += ft_putnchar('-', (fil == ' ' && n < 0));
	total += ft_putnchar('0', flags->accuracy - len);
	if (n < 0 && flags->accuracy)
		total += ft_putnbr_base(-n, ft_strlen(base), base);
	else if (n >= 0 && flags->accuracy)
		total += ft_putnbr_base(n, ft_strlen(base), base);
	total += ft_putnchar(' ', flags->minus
			* (flags->len - flags->accuracy - (n < 0)));
	return (total);
}

int	ft_print_addr(t_flag *flags, unsigned long long n)
{
	int		total;
	int		len;
	char	fil;

	total = 2;
	len = ft_lennbr_base(n, 16, flags);
	if (flags->accuracy < len)
		flags->accuracy = len;
	fil = ' ';
	if (!flags->dot && flags->zeros && !flags->minus)
		fil = '0';
	total += ft_putnchar(' ', !flags->minus
			* (flags->len - flags->accuracy - 2));
	ft_putstr_fd("0x", 1);
	total += ft_putnchar('0', flags->accuracy - len);
	if (n || flags->accuracy)
		total += ft_putnbr_base((long long)n, 16, "0123456789abcdef");
	total += ft_putnchar(' ', flags->minus
			* (flags->len - flags->accuracy - 2));
	return (total);
}
