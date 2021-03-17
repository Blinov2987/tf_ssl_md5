/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/17 21:36:50 by gemerald         ###   ########.fr       */
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
	uint64_t modulus;
	uint32_t public_exponent;
	uint64_t private_exponent;
	uint32_t prime1;
	uint32_t prime2;
	uint32_t exponent1;
	uint32_t exponent2;
	uint32_t coefficient;
}					t_rsa_key;

typedef struct		s_ext_euclid
{
	int64_t y;
	int64_t q;
	int64_t r;
	int64_t x1;
	int64_t x2;
	int64_t y1;
	int64_t y2;

}					t_ext_euclid;

typedef struct		s_asn
{
	uint8_t		mem[16];
	uint8_t		size;
}					t_asn;

void 	gen_rsa(t_rsa_args *args, t_rsa_output *output);
t_list *get_der_form(t_rsa_key key);

#endif
