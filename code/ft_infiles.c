/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:24:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 15:29:37 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	infiles_fail(char **lines, char *tokens, t_cord	*cords, int *infiles)
{
	if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], F_OK) == -1)
	{
		infiles[cords->i] = F_NO_SUCH_FILE;
		g_glob.flag = -1;
		ft_fprintf(2, "minishell: %s: No such file or directory\n", \
			lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (F_NO_SUCH_FILE);
	}
	else if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], R_OK) == -1)
	{
		infiles[cords->i] = F_PERMISSION_DENIED;
		g_glob.flag = -1;
		ft_fprintf(2, "minishell: %s: Permission denied\n", \
			lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (F_PERMISSION_DENIED);
	}
	return (0);
}

void	init_cords(t_cord *cords, int *sync)
{
	cords->i = 0;
	cords->j = 0;
	cords->sync = sync;
}

void	ft_skipin(char *tokens, t_cord *cords, int *sync)
{
	while (tokens[cords->j] && tokens[cords->j] != '<')
	{
		(*sync)++;
		cords->j++;
	}
}

int	*ft_open_infiles(char **lines, char *tokens, int *sync)
{
	t_cord	cords;
	int		*infiles;

	g_glob.flag = 0;
	init_cords(&cords, sync);
	if (!find_op(tokens, '<'))
	{
		*sync += ft_strlen(tokens);
		return (NULL);
	}
	infiles = malloc(sizeof(int) * (find_op(tokens, '<')));
	while (cords.i < find_op(tokens, '<'))
	{
		ft_skipin(tokens, &cords, sync);
		if (!tokens[cords.j]
			|| infiles_fail(lines, tokens, &cords, infiles) < 0)
			break ;
		infiles[cords.i] = open(lines[*sync + 1], O_RDONLY);
		cords.i++;
	}
	*sync += ft_strlen(&tokens[cords.j]);
	return (infiles);
}
