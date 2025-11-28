/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_close_on_while.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/28 15:25:37 by jualissa       #+#    #+#                */
/*   Updated: 2025/11/28 15:25:39 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_prev_files(t_list *value)
{
	close(value->p_pipe);
	close(value->fd_file2);
}

void	ft_close_prev_and_n_pipe(t_list *value)
{
	ft_close_prev_files(value);
	close(value->n_pipe[0]);
	close(value->n_pipe[1]);
}

void	ft_close_non_use(t_list *value)
{
	close(value->p_pipe);
	close(value->n_pipe[1]);
}
