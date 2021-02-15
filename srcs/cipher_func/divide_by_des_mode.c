/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_by_des_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:49:45 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/15 19:41:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void 	*decide_des_template(t_des_args *args)
{
	uint64_t  (*des_template)(uint64_t, uint64_t *);

	des_template = NULL;
	if (args->type == DES_COMMAND)
	{
		if (args->flag_d)
			des_template = &pure_des_decrypt;
		else
			des_template = &pure_des_encrypt;
	}
	else
	{
		if (args->flag_d)
			des_template = &pure_des3_ede_decrypt;
		else
			des_template = &pure_des3_ede_encrypt;
	}
	return (des_template);
}

void 	*decide_cipher_mode(t_des_args  *args)
{
	void	(*cipher_mode)(uint64_t *, size_t, t_key_vector *,
			uint64_t (*cipher)(uint64_t, uint64_t *));

	cipher_mode = NULL;
	if (args->algo == ECB)
		cipher_mode = &des_ecb;
	if (args->algo == CBC)
		cipher_mode = args->flag_e ? &des_cbc_enc : &des_cbc_dec;
	if (args->algo == OFB)
		cipher_mode =args->flag_e ? &des_ofb_enc : &des_ofb_dec;
	if (args->algo == CFB)
		cipher_mode = args->flag_e ? &des_cfb_enc : &des_cfb_dec;
	if (args->algo == CTR)
		cipher_mode = args->flag_e ? &des_ctr_enc : &des_ctr_dec;
	if (args->algo == PCBC)
		cipher_mode = args->flag_e ? &des_pcbc_enc : &des_pcbc_dec;
	return (cipher_mode);
}