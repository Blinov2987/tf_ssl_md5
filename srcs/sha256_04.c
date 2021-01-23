/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:39:48 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 18:16:35 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

void init_hash_buf_sha256(t_handler *handler)
{
	handler->state0 += 0x6A09E667;
	handler->state1 += 0xBB67AE85;
	handler->state2 += 0x3C6EF372;
	handler->state3 += 0xA54FF53A;
	handler->state4 += 0x510E527F;
	handler->state5 += 0x9B05688C;
	handler->state6 += 0x1F83D9AB;
	handler->state7 += 0x5BE0CD19;
}

void before_round_sha256(t_handler *handler)
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

void after_round_sha256(t_handler *handler)
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

t_list *fill_hash_buffer_sha256(t_handler *handler)
{
	t_list *result;

	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "fill_hash_buffer_sha256");
	result->content_size = 32;
	result->content = (uint8_t *)ft_safe_memalloc(32, "fill_hash_buffer_sha256");
	take_byte_from_int(&result->content[0], handler->state0);
	take_byte_from_int(&result->content[4], handler->state1);
	take_byte_from_int(&result->content[8], handler->state2);
	take_byte_from_int(&result->content[12], handler->state3);
	take_byte_from_int(&result->content[16], handler->state4);
	take_byte_from_int(&result->content[20], handler->state5);
	take_byte_from_int(&result->content[24], handler->state6);
	take_byte_from_int(&result->content[28], handler->state7);
	return (result);
}