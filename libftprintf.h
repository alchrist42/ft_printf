#ifndef LIBPRINTF_H
# define LIBPRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_flag
{
	int		minus;
	int		len;
	int		dot;
	int		accuracy;
	int		zeros;


}				t_flag;


int	ft_printf(const char *f, ...);
int	ft_print_string(t_flag *flags, char *str);
int	ft_print_char(t_flag *flags, int ch);
int	ft_print_nbr(t_flag *flags, long long n);
int	ft_print_addr(t_flag *flags, unsigned long long n);
int	ft_print_nbr_base(t_flag *flags, long long n, char *base);
// int	ft_print_nbr_base(t_flag *flags, unsigned long long);
void	ft_putnbr_base_fd(long long n, int b_len, char *base);
size_t	ft_lennbr_base(long long n, int b_len);

int	ft_putnchar(char c, int n);

#endif
