/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:45:23 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 20:21:16 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

uint32_t s0(uint32_t x)
{
	return (rotate_right(x, 7) ^ rotate_right(x, 18) ^ shift_right(x, 3));
}

uint32_t s1(uint32_t x)
{
	return (rotate_right(x,17) ^ rotate_right(x,19) ^ shift_right(x,10));
}

uint32_t sum0(uint32_t x)
{
	return (rotate_right(x, 2) ^ rotate_right(x,13) ^ rotate_right(x,22));
}

uint32_t sum1(uint32_t x)
{
	return (rotate_right(x, 6) ^ rotate_right(x,11) ^ rotate_right(x,25));
}



void sha256_round(t_handler *hndlr, uint32_t words[], uint32_t round)
{
	if (round > 15)
		word_gen(words, round);
	hndlr->temp1 = sum0(hndlr->a) + maj(hndlr->a, hndlr->b, hndlr->c);
	hndlr->temp2 = hndlr->h + sum1(hndlr->e) + chan(hndlr->e, hndlr->f, hndlr->g)
			+ g_const[round] + words[round];
	hndlr->h = hndlr->g;
	hndlr->g = hndlr->f;
	hndlr->f = hndlr->e;
	hndlr->e = hndlr->d + hndlr->temp1;
	hndlr->d = hndlr->c;
	hndlr->c = hndlr->b;
	hndlr->b = hndlr->a;
	hndlr->a = hndlr->temp1 + hndlr->temp2;

//	hndlr->temp1 = hndlr->h
//	               + sum1(hndlr->e)
//	               + chan(hndlr->e, hndlr->f, hndlr->g)
//	               + g_const[round]
//			+ words[round];
//	hndlr->temp2 = sum0(hndlr->a) + maj(hndlr->a, hndlr->b, hndlr->c);
//	hndlr->d += hndlr->temp1;
//	hndlr->h = hndlr->temp1 + hndlr->temp2;

}