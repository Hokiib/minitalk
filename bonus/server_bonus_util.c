#include "minitalk_bonus.h"

void	free_server_data(t_sdata **data)
{
	free((*data)->result);
	free(*data);
	*data = 0;
}

int	try_kill(int pid, int signal, t_sdata **data)
{
	if (kill(pid, signal) == -1)
	{
		ft_printf("Le client a été déconnecté\n");
		free_server_data(data);
		return (0);
	}
	return (1);
}

void	error(char *str, t_sdata **data)
{
	free(str);
	free_server_data(data);
	ft_printf("Une erreur est survenue\n");
	exit(0);
}
