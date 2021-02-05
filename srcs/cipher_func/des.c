/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:23:36 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/05 18:34:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		entrance_to_des(t_des_args *args)
{
	t_output	output;
	t_list		*(*cipher_func)(void *, size_t, void *);

	uint8_t favor_mem[8] = {
			0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
	};

	uint8_t favor_key[8] = {
			0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1
	};

	output.string_hash = des(favor_mem, 8, favor_key);

//	if (args->flag_e || (!args->flag_e && !args->flag_d))
//		cipher_func = &base64_enc;
//	if (args->flag_d)
//		cipher_func = &base64_dec;
//	ft_bzero(&output, sizeof(t_output));
//	get_info_stream(args, &output);
//	output.string_hash = cipher_func(output.string_stream->content,
//			output.string_stream->content_size);
//	if (args->flag_e || (!args->flag_e && !args->flag_d))
//		out_base64_prism(output.string_hash->content,
//				&output.string_hash->content_size);
//	print_output_cipher(args, &output);
	free_output(&output);
}