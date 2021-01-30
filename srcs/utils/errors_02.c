/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:46:06 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/30 19:18:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_incorrect_command(char *command)
{
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("' is an invalid command.\n", 2);
	print_commands();
}

void	error_print_multiple_flags_base64(t_base64_args *args)
{
	ft_putstr_fd("ft_ssl: for the ", 2);
	if (args->flag_d > 1)
		ft_putstr_fd("-decrypt ", 2);
	if (args->flag_e > 1)
		ft_putstr_fd("-encrypt ", 2);
	if (args->flag_i > 1)
		ft_putstr_fd("-input-file ", 2);
	if (args->flag_o > 1)
		ft_putstr_fd("-output-file ", 2);
	ft_putstr_fd("option: may only occur zero or one times!\n", 2);
}

void	error_print_multiple_flags_des(t_des_args *args)
{
	ft_putstr_fd("ft_ssl: for the ", 2);
	if (args->flag_d > 1)
		ft_putstr_fd("-decrypt ", 2);
	if (args->flag_e > 1)
		ft_putstr_fd("-encrypt ", 2);
	if (args->flag_i > 1)
		ft_putstr_fd("-input-file ", 2);
	if (args->flag_o > 1)
		ft_putstr_fd("-output-file ", 2);
	if (args->flag_a > 1)
		ft_putstr_fd("-base64-handler ", 2);
	if (args->flag_k > 1)
		ft_putstr_fd("-key-in-hex ", 2);
	if (args->flag_p > 1)
		ft_putstr_fd("-password-in-ascii ", 2);
	if (args->flag_s > 1)
		ft_putstr_fd("-salt-in-hex ", 2);
	if (args->flag_v > 1)
		ft_putstr_fd("-initialization-vector-in-hex ", 2);
	ft_putstr_fd("option: may only occur zero or one times!\n", 2);
}

void 	error_decrypt_encrypt(void)
{
	ft_putstr_fd("ft_ssl: for the cipher commands concurrent ", 2);
	ft_putstr_fd("encryption and decryption not allow\n", 2);
}