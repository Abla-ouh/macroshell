/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:06:47 by midfath           #+#    #+#             */
/*   Updated: 2022/11/01 19:07:37 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

static int	env_del(char *ar)
{
	t_list	**tmp;
	t_list	*node;

	tmp = &g_glob.envx;
	node = NULL;
	while (*tmp)
	{
		if (!(ft_strcmp(ar, ((t_env *)(*tmp)->content)->title)))
		{
			node = *tmp;
			*tmp = (*tmp)->next;
			free(((t_env *)(node)->content)->title);
			free(((t_env *)(node)->content)->value);
			free(node->content);
			free(node);
			return (0);
		}
		tmp = &(*tmp)->next;
	}
	return (1);
}

int	check_ar(char *ar)
{
	int	i;

	i = 0;
	if (!ft_isalpha(ar[0]) && !(ar[0] == '_'))
		return (0);
	while ((ar[i] && ft_isalpha(ar[i])) \
		|| ft_isdigit(ar[i]) || ar[i] == '_')
		i++;
	return (!ar[i]);
}

int	ft_unset(char **ar)
{
	int	err;
	int	i;

	i = 1;
	err = 0;
	while (ar[i])
	{
		if (check_ar(ar[i]))
			env_del(ar[i]);
		else
		{
			err = 1;
			ft_perror(NULL, ar[i], "not a valid identifier");
		}
		i++;
	}
	return (err);
}
