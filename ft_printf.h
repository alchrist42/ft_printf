#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
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

int			ft_printf(const char *f, ...);

int			ft_print_string(t_flag *flags, char *str);
int			ft_print_char(t_flag *flags, int ch);
int			ft_print_nbr_base(t_flag *flags, long long n, char *base);
int			ft_print_addr(t_flag *flags, unsigned long long n);

int			ft_putnchar(char c, int n);
int			ft_putnbr_base(unsigned long long n, size_t b_len, char *base);
size_t		ft_lennbr_base(long long n, size_t b_len, t_flag *flags);
const char	*ft_inicialize_flags(const char *s, t_flag *flags);
void		ft_get_flags(const char *s, va_list args, t_flag *flags);

#endif
