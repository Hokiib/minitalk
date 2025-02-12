#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include "libft.h"

int	ft_printf(const	char *str, ...);
int	c_arg(int c);
int	s_arg(char *str);
int	p_arg(void *ptr);
int	d_arg(int n);
int	i_arg(int n);
int	u_arg(int n);
int	xlow_arg(int n);
int	xup_arg(int n);
int	prc_arg(void);
int	nbr_base(size_t nbr, char *base);
int	print_null(void);
int	print_nil(void);

#endif
