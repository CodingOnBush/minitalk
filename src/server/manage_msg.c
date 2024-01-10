/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:41:42 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 15:15:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

static int	ft_pow(int base, int power)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < power)
	{
		res *= base;
		i++;
	}
	return (res);
}

static void	ft_extend_str(t_data *db)
{
	int		power;
	char	*newstr;
	int		len;

	power = db->power + 1;
	len = ft_pow(2, power);
	newstr = (char *)malloc(sizeof(char) * len);
	if (!newstr)
		ft_handle_error(db, "Server : malloc error !\n");
	ft_bzero(newstr, len);
	ft_memcpy(newstr, db->str, db->len);
	free(db->str);
	db->str = newstr;
	db->power = power;
	db->len = ft_pow(2, power);
}

static char	ft_get_char(int *buffer)
{
	char	c;
	int		i;

	c = 0;
	i = 0;
	while (i < 8)
	{
		c += buffer[i] * ft_pow(2, 7 - i);
		i++;
	}
	return (c);
}

void	ft_add_buffer_to_str(t_data *db)
{
	char	c;
	int		i;

	if (!db)
		return ;
	if (db->buffer[7] == -1)
		return ;
	if (db->str == NULL)
		ft_extend_str(db);
	if (db->str[db->len - 1] != '\0')
		ft_extend_str(db);
	c = ft_get_char(db->buffer);
	i = 0;
	while (db->str[i] != '\0')
		i++;
	db->str[i] = c;
	ft_reset_buffer(db->buffer);
	if (c == '\0')
	{
		ft_printf("%s\n", db->str);
		ft_printf("bit received = %d\n", db->bit_count);
		ft_init_data(db, db->pid);
	}
}
