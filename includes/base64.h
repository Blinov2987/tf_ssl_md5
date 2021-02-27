/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:18:44 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/31 16:18:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_SSL_DES_BASE64_H
#define FT_SSL_DES_BASE64_H

static const uint8_t g_enc64[65] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T',	'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7',	'8', '9', '+', '/',
		'='
};

static const uint8_t g_dec64[127] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 62, 0xff, 0xff, 0xff, 63,
		52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 0xff, 0xff, 0xff, 64, 0xff, 0xff,
		0xff, 0, 1, 2, 3, 4, 5, 6,
		7, 8, 9, 10, 11, 12, 13, 14,
		15, 16, 17, 18,	19, 20, 21, 22,
		23, 24, 25, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 26, 27, 28, 29, 30, 31, 32,
		33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, 0xff, 0xff, 0xff, 0xff
};

void	base64_enc_wrap(uint8_t *mem, size_t size, t_list *result);
void	base64_dec_wrap(uint8_t *mem, size_t offset, t_list *result);
void	out_base64_prism(uint8_t *mem, size_t *size);
void	in_base64_prism(uint8_t *mem, size_t *size);

#endif
