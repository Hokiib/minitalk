#ifndef MINITALK_H
# define MINITALK_H
# include "ft_printf.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_cdata
{
	int		pid;
	char	*message;
	int		index;
	int		char_index;
}				t_cdata;

typedef struct s_sdata
{
	char			*result;
	unsigned char	current;
	int				c_index;
	int				pid;
}				t_sdata;

void	free_server_data(t_sdata **data);
int		try_kill(int pid, int signal, t_sdata **data);
void	error(char *str, t_sdata **data);

#endif