/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:10:38 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/29 21:29:45 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		contains_char_sym(char *str, char to_count)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == to_count)
			return (TRUE);
	}
	return (FALSE);
}

void	set_flag(char f, t_args *args)
{
	if (f == 'p')
		args->flag_p++;
	if (f == 'q')
		args->flag_q++;
	if (f == 'r')
		args->flag_r++;
	if (f == 's')
		args->flag_s++;
}

void	find_args(char *str, t_args *args)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (contains_char_sym(HASHING_FLAGS, str[i]))
			set_flag(str[i], args);
		else
		{
			ft_lstadd_back(&args->bad_argums,
					ft_lstnew(str, ft_strlen(str) + 1));
			break ;
		}
	}
}
