/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:01:19 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 13:44:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

static int	ft_isspace(char c)
{
	char	*spaces;

	spaces = " \t\n\r\f\v";
	while (*spaces)
	{
		if (c == *spaces)
			return (1);
		spaces++;
	}
	return (0);
}

static long	ft_atol(char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

static pid_t	ft_parse_pid(char *s)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
		i++;
	if (s[i] != '\0')
		return (-1);
	nb = ft_atol(s);
	if (nb > INT_MAX)
		return (-1);
	return ((pid_t)nb);
}

static void	ft_error(char *msg)
{
	ft_printf("[Client : %s]\n", msg);
	exit(0);
}

void	ft_parsing(int ac, char **av, pid_t *pid, char **msg)
{
	if (ac != 3)
		ft_error("wrong number of argument !");
	if (ft_parse_pid(av[1]) < 0)
		ft_error("wrong pid syntaxe!");
	*pid = ft_parse_pid(av[1]);
	*msg = av[2];
}
