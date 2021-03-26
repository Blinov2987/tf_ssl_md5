/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/26 21:09:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_RSA_H
# define FT_SSL_DES_RSA_H

#include "output.h"

# define IN 0
# define OUT 1
# define PUBIN 2
# define PUBOUT 3
# define OUTFORM 4
# define PASSOUT 5
# define DES_RSA 6
# define TEXT 7
# define NOOUT 8
# define MODULUS 9
# define CHECK 10
# define INFORM 11
# define PASSIN 12
# define INKEY 3
# define ENCRYPT 4
# define DECRYPT_UTL 5
# define HEXDUMP 6


static const char*	g_rsa_flags[] = {
	"inform", "outform", "in", "i", "passin", "out", "o",
	"passout", "des", "text", "noout", "modulus", "check",
	"pubin", "pubout"
};

static const char*	g_rsa_utl_flags[] = {
		"in", "i", "out", "o", "pubin", "inkey", "encrypt", "decrypt", "hexdump"
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
t_asn convert_key_to_asn(void *mem, size_t size);
t_list *collect_mem_to_output(t_asn asn[], size_t asn_size);
t_rsa_key gen_rand_rsa(uint32_t pub_e);
int 	rsa_priv_checker(t_rsa_key *key);
int 	miller_rabin(uint32_t val, int k, uint8_t is_silent);
void 	rsa_key_stream_write(int fd, t_list *key_der);
void 	rsa_private_pem_des_writer(t_rsa_key *key, t_rsa_args *args);
int				contains_rsa_arg(const char *args_table[],
		size_t table_size, char *str);
int		get_out_fd(t_rsa_args *args);
int cut_start_end(t_list **pem, size_t diff, size_t off);
int 	rsa_priv_checker(t_rsa_key *key);
t_rsa_key convert_der_to_pub_key(t_list *der);
int rsa_pub_checker(t_list *pub_key);

#endif
