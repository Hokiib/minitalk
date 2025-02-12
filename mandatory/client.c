#include "minitalk.h"

t_cdata	*g_data;

char	get_char(void)
{
	int	i;

	i = 0;
	while (g_data->message[i] != '\0')
	{
		if (g_data->index == i)
			return (g_data->message[i]);
		i++;
	}
	return (0);
}

void	send_bit(void)
{
	unsigned char	temp;
	int				i;
	int				signal;

	if (g_data->char_index == 0)
	{
		g_data->char_index = 8;
		g_data->index++;
	}
	temp = get_char();
	i = 8;
	g_data->char_index--;
	while (i > g_data->char_index)
		temp = get_char() >> --i;
	if (temp % 2 == 0)
		signal = SIGUSR2;
	else
		signal = SIGUSR1;
	if (kill(g_data->pid, signal) == -1)
	{
		ft_printf("Le serveur a été déconnecté\n");
		free(g_data);
		exit(0);
	}
}

void	handler(int signal)
{
	if (signal == SIGUSR1)
		send_bit();
	else if (signal == SIGUSR2)
	{
		ft_printf("Message recu par le serveur !\n");
		free(g_data);
		exit(0);
	}
}

void	while_check(void)
{
	while (1)
	{
		if (g_data && kill(g_data->pid, 0) == -1)
		{
			ft_printf("Le serveur a été déconnecté\n");
			free(g_data);
			exit(0);
		}
		else
			usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage : ./client_bonus PID \"Message\"\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0))
	{
		ft_printf("Le pid n'est pas valide\n");
		return (0);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	g_data = malloc(sizeof(t_cdata));
	if (!g_data)
		return (0);
	g_data->pid = pid;
	g_data->message = argv[2];
	g_data->index = 0;
	g_data->char_index = 8;
	send_bit();
	while_check();
}
