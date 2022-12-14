/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:25:13 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 14:02:44 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	outfiles_fail(char **lines, char *tokens, t_cord *cords, int *outfiles)
{
	if ((tokens[cords->j] == '>' || tokens[cords->j] == 'A')
		&& access(lines[(*cords->sync) + 1], W_OK) == -1
		&& access(lines[(*cords->sync) + 1], F_OK) != -1)
	{
		outfiles[cords->i] = F_PERMISSION_DENIED;
		ft_fprintf(2, "minishell: %s: Permission denied\n", lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (F_PERMISSION_DENIED);
	}
	return (1);
}

void	to_open(t_cord *cords, char *tokens, char **lines, int *outfiles)
{
	if (tokens[cords->j] == '>')
		outfiles[cords->i] = open(lines[(*cords->sync) + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		outfiles[cords->i] = open(lines[(*cords->sync) + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
}

void	ft_skipout(char *tokens, t_cord *cords, int *sync)
{
	while (tokens[cords->j] && (tokens[cords->j] != '>'
			&& tokens[cords->j] != 'A'))
	{
		(*sync)++;
		cords->j++;
	}
}

int	*count_check_out(char *tokens, t_cord *cords, int *out, int *sync)
{
	int	*outfiles;

	cords->i = 0;
	cords->j = 0;
	cords->sync = sync;
	*out = find_op(tokens, '>');
	*out += find_op(tokens, 'A');
	outfiles = (int *)malloc(sizeof(int) * (*out));
	if (!outfiles)
		return (NULL);
	if (!(*out))
	{
		cords->sync += ft_strlen(tokens);
		free(outfiles);
		return (NULL);
	}
	return (outfiles);
}

int	*ft_open_outfiles(char **lines, char *tokens, int *sync)
{
	t_cord	cords;
	int		*outfiles;
	int		out;

	out = 0;
	outfiles = count_check_out(tokens, &cords, &out, sync);
	while (cords.i < out)
	{
		while (tokens[cords.j] && (tokens[cords.j] != '>'
				&& tokens[cords.j] != 'A'))
		{
			(*sync)++;
			cords.j++;
		}
		if (!tokens[cords.j] || outfiles_fail(lines, \
			tokens, &cords, outfiles) < 0 || g_glob.flag == -1)
			break ;
		if (g_glob.flag != -1)
			to_open(&cords, tokens, lines, outfiles);
		cords.i++;
		cords.j++;
		*sync += 1;
	}
	*sync += ft_strlen(&tokens[cords.j]);
	return (outfiles);
}
