/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_args_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:16:16 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 11:19:03 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		add_to_args_list(char **av, int *cur_position, t_list **list)
{
	(*cur_position)++;
	ft_lstadd_back(list,
			ft_lstnew(av[*cur_position],
					ft_strlen(av[*cur_position]) + 1));
}

t_des_args	*take_des_args(int ac, char **av)
{
	int			i;
	t_des_args	*args;

	args = ft_safe_memalloc(sizeof(t_des_args), "take_base64_args");
	i = 1;
	while (++i < ac)
		pars_args_des(ac, av, &i, args);
	return (args);
}
