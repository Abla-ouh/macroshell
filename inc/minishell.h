/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:18:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/20 00:00:11 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "exe.h"

# define F_NO_SUCH_FILE -2
# define F_PERMISSION_DENIED -3

typedef struct s_cmds
{
	char			*path;
	char			**args;
	int				in;
	int				out;
	int				is_exec;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_expand
{
	int				type;
	char			*arg;
	struct s_expand	*next;
}	t_expand;

typedef struct s_data
{
	char	**lines;
	char	*tokens;
	char	**splitted_tokens;
	int		**here_fds;
	int		**infiles;
	int		**outfiles;
}	t_data;

t_cmds	*ft_parser(char *line);
char	*ft_tokenize(char **lines);
char	*expand(char *arg);
int		ft_syntax_error(char **lines, char *token);
int		ft_check_redir_filename(char **lines, char *tokens);
int		*ft_open_hdocs(char **lines, char *tokens, int *sync_lines);
int		setup_last_io(int *last_io, char *token, t_data *data, int cmd_idx);
int		*ft_open_infiles(char **lines, char *tokens, int *sync_lines);
int		*ft_open_outfiles(char **lines, char *tokens, int *sync_lines);
char	**ft_fill_args(char **lines, char *tokens, int *sync_lines);
void	count_until_not(char *trim_line, int i, int *len, char o);
void	count_string(char *trim_line, int i, int *len);
int		find_until_not(char *str_trim, int *i, char o);
void	find_string(char *str_trim, int *i);
void	skip_quote(char *str_trim, int *i, char q);
int		is_single_quoted(char *arg);
char	*get_cmd_path(t_cmds *cmds);
int		find_op(char *tokens, char c);
char	**ft_lexer(char *line, char *set);
int		count_dup(char *str_trim, char o);
char	*ft_str_trim(char *s, char *set);
char	*ft_tokenize(char **lines);
#endif
