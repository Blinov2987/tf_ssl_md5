/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:14:29 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/26 21:19:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

void init_hash_buf_sha512(t_handler *handler)
{
	handler->state0 += 0x6a09e667f3bcc908;
	handler->state1 += 0xbb67ae8584caa73b;
	handler->state2 += 0x3c6ef372fe94f82b;
	handler->state3 += 0xa54ff53a5f1d36f1;
	handler->state4 += 0x510e527fade682d1;
	handler->state5 += 0x9b05688c2b3e6c1f;
	handler->state6 += 0x1f83d9abfb41bd6b;
	handler->state7 += 0x5be0cd19137e2179;
}

void before_round_sha512(t_handler *handler)
{
	handler->a = handler->state0;
	handler->b = handler->state1;
	handler->c = handler->state2;
	handler->d = handler->state3;
	handler->e = handler->state4;
	handler->f = handler->state5;
	handler->g = handler->state6;
	handler->h = handler->state7;
}

void after_round_sha512(t_handler *handler)
{
	handler->state0 += handler->a;
	handler->state1 += handler->b;
	handler->state2 += handler->c;
	handler->state3 += handler->d;
	handler->state4 += handler->e;
	handler->state5 += handler->f;
	handler->state6 += handler->g;
	handler->state7 += handler->h;
}

void take_byte_from_int_sha512(uint8_t *mem, uint64_t val)
{
	mem[0] = (uint8_t)(val >> 56);
	mem[1] = (uint8_t)(val >> 48);
	mem[2] = (uint8_t)(val >> 40);
	mem[3] = (uint8_t)(val >> 32);
	mem[4] = (uint8_t)(val >> 24);
	mem[5] = (uint8_t)(val >> 16);
	mem[6] = (uint8_t)(val >> 8);
	mem[7] = (uint8_t)(val);
}

t_list *fill_hash_buffer_sha512(t_handler *handler)
{
	t_list *result;

	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "fill_hash_buffer_sha512");
	result->content_size = 64;
	result->content = (uint8_t *)ft_safe_memalloc(64, "fill_hash_buffer_sha512");
	take_byte_from_int_sha512(&result->content[0], handler->state0);
	take_byte_from_int_sha512(&result->content[8], handler->state1);
	take_byte_from_int_sha512(&result->content[16], handler->state2);
	take_byte_from_int_sha512(&result->content[24], handler->state3);
	take_byte_from_int_sha512(&result->content[32], handler->state4);
	take_byte_from_int_sha512(&result->content[40], handler->state5);
	take_byte_from_int_sha512(&result->content[48], handler->state6);
	take_byte_from_int_sha512(&result->content[56], handler->state7);
	return (result);
}