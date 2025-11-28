#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char	**argv;
	char	**env;
	char	**argv_cmd;
	char	*path;
	int		p_pipe;
	int		n_pipe[2];
	int		fd_file1;
	int		fd_file2;
	int		argc;
	int		fork_id;
	int		status;
	int		i;
	int		nb_cmd;
}	t_list;

//libft
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strclear(char **str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin_safe(char *s1, char *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_strdup(char *s1);

//gnl
char	*get_next_line(int fd);
char	*ft_substr_safe(const char *s, unsigned int start, size_t len);

//pipex
char	*get_path(char *cmd, char **env);
char	*my_getenv(char *name, char **env);
void	ft_close_all(t_list *value);
void	ft_close_fd_files(t_list *value);
void	ft_define_value(t_list *value, int argc, char **argv, char **env);

//close prev while
void	ft_close_files(t_list *value);
void	ft_close_files_and_n_pipe(t_list *value);
void	ft_close_not_used_files(t_list *value);

//close on while
void	ft_close_prev_files(t_list *value);
void	ft_close_prev_and_n_pipe(t_list *value);
void	ft_close_non_use(t_list *value);

#endif
