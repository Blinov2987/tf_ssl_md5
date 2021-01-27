/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:37:58 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:39:55 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		print_usage(void)
{
	ft_putendl(USAGE_STRING);
	return (FALSE);
}

int		print_commands(void)
{
	ft_putendl(STD_COMMANDS);
	ft_putendl(DIGEST_COMMANDS);
	ft_putendl(CIPHER_COMMANDS);
	return (FALSE);
}

void	error_print_multiple_flags(t_args *args)
{
	ft_putstr_fd("ft_ssl: for the ", 2);
	if (args->flag_p > 1)
		ft_putstr_fd("-print-stdin-stdout ", 2);
	if (args->flag_q > 1)
		ft_putstr_fd("-quiet-mode ", 2);
	if (args->flag_r > 1)
		ft_putstr_fd("-reverse-format-output ", 2);
	ft_putstr_fd("option: may only occur zero or one times!\n", 2);
}

void	error_print_bad_argums(t_args *args)
{
	t_list *iter;

	iter = args->bad_argums;
	while (iter)
	{
		ft_putstr_fd("ft_ssl: Unknown command line argument '-", 2);
		ft_putstr_fd(iter->content, 2);
		ft_putstr_fd("'\n", 2);
		iter = iter->next;
	}
}

void	error_safe_memalloc(char *funtion_name)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd("can't allocate mem in function ", 2);
	ft_putstr_fd(funtion_name, 2);
	ft_putstr_fd("\n", 2);
}
