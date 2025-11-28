/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:26:52 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/28 16:50:13 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_heredoc(char *delimiter)
{
	char	*line;
	int		len;
	int		pipe_fd[2];

	len = ft_strlen(delimiter);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
		{
			perror("gnl");
			exit(1);
		}
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			close(pipe_fd[1]);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		ft_strlen(line);
		free(line);
	}
	return (pipe_fd[0]);
}

void	ft_define_value(t_list *value, int argc, char **argv, char **environ)
{
	value->argv = argv;
	value->env = environ;
	value->argc = argc;
	value->argv_cmd = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		value->fd_file1 = ft_heredoc(argv[2]);
		value->i = 3;
		value->nb_cmd = argc - 4;
		value->fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (value->fd_file2 == -1)
		{
			close(value->fd_file1);
			perror("file2");
			exit(1);
		}
	}
	else
	{
		value->fd_file1 = open(argv[1], O_RDONLY);
		if (value->fd_file1 == -1)
		{
			perror("file1");
			exit (1);
		}
		value->i = 2;
		value->nb_cmd = argc - 3;
		value->fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (value->fd_file2 == -1)
		{
			close(value->fd_file1);
			perror("file2");
			exit(1);
		}
	}
}

void	ft_check_less_five_arg(int argcc)
{
	if (argcc < 5)
	{
		write(1, "./pipex file1 cmd1 cmd2 file2\n", 31);
		exit (1);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_list	value;

	ft_check_less_five_arg(argc);
	ft_define_value(&value, argc, argv, environ);
	if (pipe(value.n_pipe) == -1)
	{
		ft_close_files(&value);
		perror("pipe");
		return (1);
	}

	value.fork_id = fork();
	if (value.fork_id == -1)
	{
		ft_close_files_and_n_pipe(&value);
		perror("fork");
		exit(1);
	}


		if (value.fork_id == 0)
		{
			if (dup2(value.fd_file1, 0) == -1)
			{
				ft_close_files_and_n_pipe(&value); // sur le parent close n_pipe 0 et 1 et f1 et f2
				exit(1);
			}
			if (dup2(value.n_pipe[1], 1) == -1)
			{
				ft_close_files_and_n_pipe(&value); // sur le parent close n_pipe 0 et 1 et f1 et f2
				exit(1);
			}
			ft_close_files_and_n_pipe(&value);
			value.argv_cmd = ft_split(argv[value.i], ' ');
			value.path = get_path(value.argv_cmd[0], value.env);
			execve(value.path, value.argv_cmd, value.env);
			perror("execeve");

			exit(1);
		}

		value.p_pipe = value.n_pipe[0];
		ft_close_not_used_files(&value);

		value.i++;











		while (value.i < argc - 2)
		{
			if (pipe(value.n_pipe) == -1)
			{
				ft_close_prev_files(&value);
				perror("pipe");
				exit(1);
			}
			value.fork_id = fork();
			if (value.fork_id == -1)
			{
				ft_close_prev_and_n_pipe(&value);
				perror("pipe");
				exit(1);
			}
			if (value.fork_id == 0)
			{
				if (dup2(value.p_pipe, 0) == -1)
				{
					ft_close_prev_and_n_pipe(&value);
					perror("dup2");
					exit(1); //check_wait pour close parent commen ft_close_middle
				}
				if (dup2(value.n_pipe[1], 1) == -1)
				{
					ft_close_prev_and_n_pipe(&value);
					perror("dup2");
					exit(1);  //check_wait pour close parent commen ft_close_middle
				}
				ft_close_prev_and_n_pipe(&value);

				value.argv_cmd = ft_split(argv[value.i], ' ');
				value.path = get_path(value.argv_cmd[0], value.env);
				execve(value.path, value. argv_cmd, value.env);
				exit(1);
			}
			ft_close_non_use(&value);
			value.p_pipe = value.n_pipe[0];
			value.i++;
		}




	value.fork_id = fork();
	if (value.fork_id == -1)
	{
		ft_close_prev_files(&value);
		perror("fork");
		exit(1);
	}
	if (value.fork_id == 0)
	{
		if (dup2(value.p_pipe, 0) == -1)
		{
			ft_close_prev_files(&value);
			perror("dup");
			exit(1); // close meme chose dans le pere
		}
		if (dup2(value.fd_file2, 1)  == -1)
		{
			ft_close_prev_files(&value);
			perror("dup");
			exit(1); // close meme chose dansl epere
		}
		ft_close_prev_files(&value);
		value.argv_cmd = ft_split(argv[argc - 2] , ' ');
		value.path = get_path(value.argv_cmd[0], value.env);
		execve(value.path, value.argv_cmd, value.env);
		exit(1);
	}
	ft_close_prev_files(&value);
	value.i = 0;
	while (value.i < value.nb_cmd)
	{
		wait(&value.status);
		value.i = value.i + 1;
	} // faire waitpid pour close en fonction des fd

}
