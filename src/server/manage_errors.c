/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:41:36 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 15:15:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_minitalk.h"

void	ft_handle_error(t_data *db, char *msg)
{
	ft_printf("\n[Server error : %s]\n", msg);
	if (db != NULL)
	{
		if (db->str != NULL)
			free(db->str);
		free(db);
	}
	exit(0);
}
