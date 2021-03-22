/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/22 20:01:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_RSA_H
#define FT_SSL_DES_RSA_H

static const char*	g_rsa_flags[] = {
	"inform", "outform", "in", "i", "passin", "out", "o",
	"passout", "des", "text", "noout", "modulus", "check",
	"pubin", "pubout", "inkey", "encrypt", "decrypt", "hexdump"
};

static const uint8_t g_der_bit_string[] = {
	0x30, 0x24, 0x30, 0xd, 0x6, 0x9, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0xd, 0x1,
	0x1, 0x1, 0x5, 0, 0x3, 0x13, 0
};

static const uint8_t g_pub_key_version[] = {
	0x30, 0xd, 0x6, 0x9, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0xd, 0x1,
	0x1, 0x1, 0x5, 0, 0x3
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

t_rsa_key
gen_rsa_key_on_primes(uint32_t prime1, uint32_t prime2, uint32_t pub_e);
t_list *get_priv_der_form(t_rsa_key *key);
t_list *get_pub_der_form(t_rsa_key *key);
void 	rsa_private_pem_writer(t_rsa_key *key, t_rsa_args *args);
t_asn convert_key_to_asn(void *mem, size_t size);
t_list *collect_mem_to_output(t_asn asn[], size_t asn_size);
t_rsa_key gen_rand_rsa(uint32_t pub_e);
int 	rsa_priv_checker(t_rsa_key *key);
t_list 	*des_hiding(t_list *der);
void 	rsa_key_stream_write(int fd, t_list *key_der);
void 	rsa_private_pem_des_writer(t_rsa_key *key, t_rsa_args *args);


#endif
