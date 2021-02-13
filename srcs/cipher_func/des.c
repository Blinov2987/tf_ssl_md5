/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:23:36 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 12:32:24 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		entrance_to_des(t_des_args *args)
{
	t_crypt_output 	output;
	t_list		*(*cipher_func)(void *, size_t, void *);

	ft_bzero(&output, sizeof(t_crypt_output));
	uint8_t salt[8] = {
			0xB6, 0x49, 0xC3, 0x48, 0xC3, 0x24, 0xB5, 0x7A
	};
	pbkfd(args->pass_in_ascii, ft_lstnew(salt, 8));

	uint8_t favor_mem[8] = {
			0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
	};

	uint8_t favor_key[8] = {
			0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1
	};

	des_ecb(favor_mem, 8, favor_key);
	free_crypt_output(&output);
}