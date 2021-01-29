/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:24:37 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/29 22:33:04 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_cmd_type take_command_type(char *command)
{
	t_cmd_type cmd;

	ft_bzero(&cmd, sizeof(t_cmd_type));
	fill_hash_cmd(&cmd, command);
	fill_cipher_cmd(&cmd, command);
	return (cmd);
}

void	hashing_branch(t_cmd_type cmd, int ac, char **av)
{
	t_args *args;

	args = take_hash_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args(&args))
		entrance_to_hash(args);
	free_args(&args);
}

void	base64_branch(t_cmd_type cmd, int ac, char **av)
{
	t_base64_args *args;

	args = take_base64_args(ac, av);
	args->type = cmd.type;
	args->algo = cmd.algo;
	if (validate_args(&args))
		entrance_to_hash(args);
	free_args(&args);
}

void	des_branch(t_cmd_type cmd, int ac, char **av)
{

}

void	split_by_commands(int ac, char **av)
{
	t_cmd_type cmd;

	if (ac < 2)
	{
		print_usage();
		return ;
	}
	cmd = take_command_type(av[1]);
	if (!cmd.type)
	{
		print_incorrect_command(av[1]);
		return ;
	}
	if (cmd.type == HASHING_COMMAND)
		hashing_branch(cmd, ac, av);
	if (cmd.type == BASE64_COMMAND)
		base64_branch(cmd, ac, av);
	if (cmd.type == DES_COMMAND)
		des_branch(cmd, ac, av);
}