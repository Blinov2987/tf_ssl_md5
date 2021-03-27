/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 18:21:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_RSA_H
# define FT_SSL_DES_RSA_H

# define IN 0
# define OUT 1
# define PUBIN 2
# define PUBOUT 3
# define OUTFORM 4
# define PASO 5
# define DES_RSA 6
# define TEXT 7
# define NOOUT 8
# define MODULUS 9
# define CHECK 10
# define INFORM 11
# define PASI 12
# define INKEY 3
# define ENCRYPT 4
# define DECRYPT_UTL 5
# define HEXDUMP 6

static const char *g_rsa_flags[] = {
	"inform", "outform", "in", "i", "passin", "out", "o",
	"passout", "des", "text", "noout", "modulus", "check",
	"pubin", "pubout"
};

static const char *g_rsa_utl_flags[] = {
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

uint32_t	get_rand_uint(uint32_t val);
int			miller_rabin_step(uint32_t s, uint32_t x, uint32_t val);
int			miller_rabin_cycle(uint32_t val, int k, uint32_t t, uint32_t s);
int			miller_rabin_silent_cycle(uint32_t val, int k,
			uint32_t t, uint32_t s);
uint64_t	mod_power_rem(uint64_t x, uint64_t pow, uint64_t mod);
void		print_byte_row(uint8_t *mem, size_t bound, int fd);
void		print_one_byte(uint8_t byte, int fd);
void		set_flag_rsa(int flag, t_rsa_args *args);

#endif
