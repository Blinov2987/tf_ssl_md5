/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:17:10 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:09:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

uint64_t	swap64(uint64_t val)
{
	uint64_t x;

	x = val;
	x = (x & 0xffffffff00000000) >> 32 | (x & 0x00000000ffffffff) << 32;
	x = (x & 0xffff0000ffff0000) >> 16 | (x & 0x0000ffff0000ffff) << 16;
	x = (x & 0xff00ff00ff00ff00) >> 8 | (x & 0x00ff00ff00ff00ff) << 8;
	return (x);
}

uint32_t	take_int_from_byte_sha256(uint8_t *mem)
{
	return ((uint32_t)mem[0] << 24
			| ((uint32_t)mem[1] << 16)
			| ((uint32_t)mem[2] << 8)
			| ((uint32_t)mem[3]));
}
