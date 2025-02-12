#include "minitalk_bonus.h"

t_sdata	*g_data = 0;

t_sdata	*new_data(int pid)
{
	t_sdata	*data;

	data = malloc(sizeof(t_sdata));
	if (!data)
	{
		ft_printf("Une erreur est survenue\n");
		exit(0);
		return (0);
	}
	data->result = 0;
	data->current = 0;
	data->c_index = 0;
	data->pid = pid;
	return (data);
}

char	*to_string(char c)
{
	char	*result;

	result = malloc(2);
	if (!result)
		return (0);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

void	add_back(char c)
{
	int		size;
	char	*copy;
	char	*str;

	size = 0;
	if (g_data->result)
	{
		size = ft_strlen(g_data->result);
		copy = ft_strdup(g_data->result);
		free(g_data->result);
	}
	else
		copy = ft_strdup("");
	if (!copy)
		error(copy, &g_data);
	size += 2;
	str = to_string(c);
	g_data->result = ft_strjoin(copy, str);
	free(copy);
	free(str);
	if (!g_data->result)
		error(g_data->result, &g_data);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	if (!g_data)
		g_data = new_data(info->si_pid);
	g_data->current |= (SIGUSR1 == signal);
	g_data->c_index++;
	(void) context;
	if (g_data->c_index == 8)
	{
		if (g_data->current == '\0')
		{
			ft_printf(g_data->result);
			ft_printf("\n");
			if (!try_kill(info->si_pid, SIGUSR2, &g_data))
				return ;
			free_server_data(&g_data);
			return ;
		}
		else
			add_back(g_data->current);
		g_data->c_index = 0;
		g_data->current = 0;
	}
	g_data->current <<= 1;
	try_kill(info->si_pid, SIGUSR1, &g_data);
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	ft_printf("My PID is %d\n", getpid());
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		if (g_data && kill(g_data->pid, 0) == -1)
		{
			ft_printf("Le client a été déconnecté\n");
			free_server_data(&g_data);
		}
		else
			usleep(100);
	}
}
