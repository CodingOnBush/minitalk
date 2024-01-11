/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:25:03 by momrane           #+#    #+#             */
/*   Updated: 2024/01/11 10:54:02 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

int			g_bit_count;

static void	ft_handle_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("⬜");
	else if (signum == SIGUSR2)
		ft_printf("🌀");
	else
	{
		ft_printf("[Client : Stop sending]\n");
		exit(0);
	}
}

static void	ft_send_char(pid_t pid, char c)
{
	int		i;
	char	bit;

	i = 8;
	while (i--)
	{
		bit = (c >> i) & 1;
		if (bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		g_bit_count++;
		pause();
		usleep(100);
	}
}

static void	ft_send_msg(pid_t pid, char *msg)
{
	if (!msg)
		return ;
	while (*msg != '\0')
	{
		ft_send_char(pid, *msg);
		msg++;
	}
	ft_send_char(pid, '\0');
	ft_printf("\n[Client : Message sent ✅]\n");
}

int	main(int argc, char **argv)
{
	char	*msg;
	pid_t	spid;

	g_bit_count = 0;
	ft_parsing(argc, argv, &spid, &msg);
	ft_printf("[Client : Hi ! I'm the client and my PID is %d]\n", getpid());
	signal(SIGUSR1, ft_handle_signal);
	signal(SIGUSR2, ft_handle_signal);
	ft_send_msg(spid, msg);
	ft_printf("bit sent = %d\n", g_bit_count);
	return (0);
}
