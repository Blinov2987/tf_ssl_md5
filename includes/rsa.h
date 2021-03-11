/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/11 19:31:45 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_RSA_H
#define FT_SSL_DES_RSA_H

static const char*	g_rsa_flags[] = {
	"inform", "outform", "in", "i", "passin", "out", "o",
	"passout", "des", "text", "noout", "modulus", "check",
	"pubin", "pubout", "inkey", "encrypt", "decrypt", "hexdump"
};

typedef struct 		s_rsa_key
{
	uint32_t version;
	uint32_t modulus;
	uint32_t public_exponent;
	uint32_t private_exponent;
	uint32_t prime1;
	uint32_t prime2;
	uint32_t exponent1;
	uint32_t exponent2;
	uint32_t coefficient;
}					t_rsa_key;

void 	gen_rsa(t_rsa_args *args, t_rsa_output *output);

#endif
