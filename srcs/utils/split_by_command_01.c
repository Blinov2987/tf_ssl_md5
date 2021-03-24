/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_command_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:12:27 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/23 21:56:22 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void 		rsa_utl_branch(t_cmd_type cmd, int ac, char **av)
{
	t_rsa_args *args;

	args = take_rsa_utl_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args_rsa(&args))
		entrance_to_rsa_utl(args);
	free_rsa_args(&args);
}

void 		gen_rsa_branch(t_cmd_type cmd, int ac, char **av)
{
	t_rsa_args *args;

	args = take_gen_rsa_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args_rsa(&args))
		entrance_to_gen_rsa(args);
	free_rsa_args(&args);
}

void 		rsa_branch(t_cmd_type cmd, int ac, char **av)
{
	t_rsa_args *args;

	args = take_rsa_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args_rsa(&args))
		entrance_to_rsa(args);
	free_rsa_args(&args);
}

void		split_on_rsa(t_cmd_type cmd, int ac, char **av)
{

	if (cmd.type == RSA)
		rsa_branch(cmd, ac, av);
	if (cmd.type == GEN_RSA)
		gen_rsa_branch(cmd, ac, av);
	if (cmd.type == RSAUTL)
		rsa_utl_branch(cmd, ac, av);
}