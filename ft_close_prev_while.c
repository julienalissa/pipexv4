/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_close_prev_while.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/28 15:25:48 by jualissa       #+#    #+#                */
/*   Updated: 2025/11/28 15:25:52 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_files(t_list *value)
{
	if (value->i == 2)
		close(value->fd_file1);
	close(value->fd_file2);
}

void	ft_close_files_and_n_pipe(t_list *value)
{
	ft_close_files(value);
	close(value->n_pipe[0]);
	close(value->n_pipe[1]);
}

void	ft_close_not_used_files(t_list *value)
{
	if (value->i == 2)
		close(value->fd_file1);
	close(value->n_pipe[1]);
}
