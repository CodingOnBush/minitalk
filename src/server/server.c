/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:27:47 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 18:11:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

t_data		*g_db;

static void	ft_handle_sigusr(pid_t client_pid, int bit)
{
	int	i;

	if (g_db == NULL)
	{
		g_db = ft_create_db(client_pid);
		if (!g_db)
			ft_handle_error(g_db, "Server : malloc error !\n");
	}
	if (g_db->pid != client_pid)
		ft_init_data(g_db, client_pid);
	g_db->bit_count++;
	i = 0;
	while (g_db->buffer[i] != -1)
		i++;
	g_db->buffer[i] = bit;
	if (i == 7)
		ft_add_buffer_to_str(g_db);
	usleep(100);
	if (bit)
		kill(client_pid, SIGUSR2);
	else
		kill(client_pid, SIGUSR1);
}

static void	ft_sigactions(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		ft_handle_sigusr(info->si_pid, 0);
	else if (signum == SIGUSR2)
		ft_handle_sigusr(info->si_pid, 1);
	else
		ft_handle_error(g_db, "Server : wrong signal received !");
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void)av;
	if (ac != 1)
		ft_handle_error(g_db, "Server : wrong number of argument !");
	g_db = ft_create_db(-1);
	if (!g_db)
		ft_handle_error(g_db, "Server : malloc error !");
	act.sa_sigaction = ft_sigactions;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	ft_printf("[Hi ! I'm the server and here is my PID %d]\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		sigaction(SIGINT, &act, NULL);
		pause();
	}
	return (0);
}
