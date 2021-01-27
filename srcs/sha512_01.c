/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:53:21 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:28:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

uint64_t	shift_right_512(uint64_t x, uint64_t n)
{
	return (x >> n);
}

uint64_t	rotate_right_512(uint64_t x, uint64_t n)
{
	return (x >> n | (x << (64 - n)));
}

uint64_t	maj_512(uint64_t a, uint64_t b, uint64_t c)
{
	return ((a & b) ^ (a & c) ^ (b & c));
}

uint64_t	chan_512(uint64_t e, uint64_t f, uint64_t g)
{
	return ((e & f) ^ ((~e) & g));
}

void		word_gen_512(uint64_t words[], uint64_t ind)
{
	words[ind] = s1_512(words[ind - 2]) + words[ind - 7]
		+ s0_512(words[ind - 15]) + words[ind - 16];
}
