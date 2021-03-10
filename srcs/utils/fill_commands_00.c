/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:39:38 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/10 21:57:37 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "constants.h"

static void		fill_cmd_type(t_cmd_type *cmd, int type, int algo)
{
	cmd->type = type;
	cmd->algo = algo;
}

void			fill_hash_cmd(t_cmd_type *cmd, char *command)
{
	if (!ft_strcmp("md5", command))
		fill_cmd_type(cmd, HASHING_COMMAND, MD5);
	if (!ft_strcmp("sha256", command))
		fill_cmd_type(cmd, HASHING_COMMAND, SHA256);
	if (!ft_strcmp("sha512", command))
		fill_cmd_type(cmd, HASHING_COMMAND, SHA512);
}

static void		fill_des_type(t_cmd_type *cmd, int type, char *command)
{
	if (!ft_strcmp("ecb", command))
		fill_cmd_type(cmd, type, ECB);
	if (!ft_strcmp("cbc", command))
		fill_cmd_type(cmd, type, CBC);
	if (!ft_strcmp("ofb", command))
		fill_cmd_type(cmd, type, OFB);
	if (!ft_strcmp("cfb", command))
		fill_cmd_type(cmd, type, CFB);
	if (!ft_strcmp("ctr", command))
		fill_cmd_type(cmd, type, CTR);
	if (!ft_strcmp("pcbc", command))
		fill_cmd_type(cmd, type, PCBC);
}

void			fill_cipher_cmd(t_cmd_type *cmd, char *command)
{
	if (!ft_strcmp("base64", command))
		fill_cmd_type(cmd, BASE64_COMMAND, FALSE);
	if (!ft_strncmp("des-", command, 4) && ft_strlen(command) > 4)
		fill_des_type(cmd, DES_COMMAND, &command[4]);
	else if (!ft_strncmp("des3-", command, 5) && ft_strlen(command) > 5)
		fill_des_type(cmd, DES3_COMMAND, &command[5]);
	else if (!ft_strcmp("des3", command))
		fill_cmd_type(cmd, DES3_COMMAND, CBC);
	else if (!ft_strcmp("des", command))
		fill_cmd_type(cmd, DES_COMMAND, CBC);
}

void			fill_rsa_cmd(t_cmd_type *cmd, char *command)
{
	if (!ft_strcmp("rsa", command))
		fill_cmd_type(cmd, RSA, FALSE);
	if (!ft_strcmp("rsautl", command))
		fill_cmd_type(cmd, RSAUTL, FALSE);
	if (!ft_strcmp("genrsa", command))
		fill_cmd_type(cmd, GEN_RSA, FALSE);
}
