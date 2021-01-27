/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:44:21 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:11:41 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

uint32_t	shift_right(uint32_t x, uint32_t n)
{
	return (x >> n);
}

uint32_t	rotate_right(uint32_t x, uint32_t n)
{
	return (x >> n | (x << (32 - n)));
}

uint32_t	maj(uint32_t a, uint32_t b, uint32_t c)
{
	return ((a & b) ^ (a & c) ^ (b & c));
}

uint32_t	chan(uint32_t e, uint32_t f, uint32_t g)
{
	return ((e & f) ^ ((~e) & g));
}

void		word_gen(uint32_t words[], uint32_t ind)
{
	words[ind] = s1(words[ind - 2]) + words[ind - 7] +
			s0(words[ind - 15]) + words[ind - 16];
}
