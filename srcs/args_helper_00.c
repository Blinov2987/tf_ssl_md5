/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:10:38 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:38:36 by gemerald         ###   ########.fr       */
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

int		is_correct_flag(char f)
{
	if (contains_char_sym(ARGS_SYMBOLS, f))
		return (TRUE);
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
		if (is_correct_flag(str[i]))
			set_flag(str[i], args);
		else
		{
			ft_lstadd_back(&args->bad_argums,
					ft_lstnew(str, ft_strlen(str) + 1));
			break ;
		}
	}
}

int		take_command(char *command, t_args *args)
{
	if (!ft_strcmp("md5", command))
		args->is_md5 = TRUE;
	if (!ft_strcmp("sha256", command))
		args->is_sha256 = TRUE;
	if (!ft_strcmp("sha512", command))
		args->is_sha512 = TRUE;
	if (!args->is_md5 && !args->is_sha256 && !args->is_sha512)
		return (FAIL);
	return (SUCCESS);
}
