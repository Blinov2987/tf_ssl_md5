/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_command_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:12:27 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/09 22:12:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		rsa_branch(t_cmd_type cmd, int ac, char **av)
{
	t_rsa_args *args;

	args = take_rsa_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args_rsa(&args))
		entrance_to_rsa(args);
	free_args((t_args **)&args);
}