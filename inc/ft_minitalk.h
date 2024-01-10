/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:27:46 by momrane           #+#    #+#             */
/*   Updated: 2024/01/10 15:09:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# include "../lib/ft_printf/include/ft_printf.h"
# include "../lib/libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

typedef struct s_data
{
	int		pid;
	char	*str;
	int		len;
	int		bit_count;
	int		power;
	int		buffer[8];
}			t_data;

void		ft_parsing(int ac, char **av, pid_t *pid, char **msg);
void		ft_reset_buffer(int *buffer);
void		ft_init_data(t_data *db, int pid);
t_data		*ft_create_db(int pid);
void		ft_handle_error(t_data *db, char *msg);
void		ft_add_buffer_to_str(t_data *db);

#endif