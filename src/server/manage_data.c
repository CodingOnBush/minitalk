/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:40:37 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 15:15:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

void	ft_reset_buffer(int *buffer)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		buffer[i] = -1;
		i++;
	}
}

void	ft_init_data(t_data *db, int pid)
{
	if (db == NULL)
		return ;
	db->pid = pid;
	if (db->str != NULL)
		free(db->str);
	db->str = NULL;
	db->len = 0;
	db->bit_count = 0;
	db->power = 0;
	ft_reset_buffer(db->buffer);
}

t_data	*ft_create_db(int pid)
{
	t_data	*out;

	out = (t_data *)malloc(sizeof(t_data));
	if (!out)
		ft_handle_error(out, "Server : malloc error !\n");
	out->str = NULL;
	ft_init_data(out, pid);
	return (out);
}
