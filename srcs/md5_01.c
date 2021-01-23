/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 09:57:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 12:24:58 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void    append_size(uint8_t *mem, uint64_t size)
{
	mem[0] = (uint8_t)(size >> 0);
	mem[1] = (uint8_t)(size >> 8);
	mem[2] = (uint8_t)(size >> 16);
	mem[3] = (uint8_t)(size >> 24);
	mem[4] = (uint8_t)(size >> 32);
	mem[5] = (uint8_t)(size >> 40);
	mem[6] = (uint8_t)(size >> 48);
	mem[7] = (uint8_t)(size >> 56);
}

uint32_t take_int_from_byte(uint8_t *mem)
{
	return ((uint32_t)mem[0]
			| ((uint32_t)mem[1] << 8)
			| ((uint32_t)mem[2] << 16)
	        | ((uint32_t)mem[3] << 24));
}

void take_byte_from_int(uint8_t *mem, uint32_t val)
{
	mem[0] = (uint8_t)(val);
	mem[1] = (uint8_t)(val >> 8);
	mem[2] = (uint8_t)(val >> 16);
	mem[3] = (uint8_t)(val >> 24);
}

void fill_chunk(uint32_t chunk[], uint8_t *mem)
{
	int i;
	int current_mem;

	i = -1;
	current_mem = 0;
	while (++i < 16)
	{
		chunk[i] = take_int_from_byte(&mem[current_mem]);
		current_mem += 4;

	}
}

uint32_t rotate_left(uint32_t left, uint32_t right)
{
	return (((left) << (right)) | ((left) >> (32 - (right))));
}

void make_round(t_handler *handler, uint32_t chunk[])
{
	int i;

	i = -1;

	while (++i < 64)
	{
		if (i < 16) {
			handler->f = (handler->b & handler->c) | ((~handler->b) & handler->d);
			handler->g = i;
		} else if (i < 32) {
			handler->f = (handler->d & handler->b) | ((~handler->d) & handler->c);
			handler->g = (5*i + 1) % 16;
		} else if (i < 48) {
			handler->f = handler->b ^ handler->c ^ handler->d;
			handler->g = (3*i + 5) % 16;
		} else {
			handler->f = handler->c ^ (handler->b | (~handler->d));
			handler->g = (7*i) % 16;
		}

		handler->swap = handler->d;
		handler->d = handler->c;
		handler->c = handler->b;
		handler->b = handler->b + rotate_left((handler->a + handler->f + g_radians[i] + chunk[handler->g]), g_round_shift[i]);
		handler->a = handler->swap;
	}
}

void   before_round(t_handler *handler)
{
	handler->a = handler->hash0;
	handler->b = handler->hash1;
	handler->c = handler->hash2;
	handler->d = handler->hash3;
}

void after_round(t_handler *handler)
{
	handler->hash0 += handler->a;
	handler->hash1 += handler->b;
	handler->hash2 += handler->c;
	handler->hash3 += handler->d;
}

t_list *md5_rounds(uint8_t *mem, size_t size)
{
	t_handler handler;
	size_t offset;
	uint32_t chunk[16];
	t_list *result;

	ft_bzero(&handler, sizeof(t_handler));
	ft_bzero(chunk, 64);
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "md5_rounds");
	result->content_size = 16;
	result->content = (uint8_t *)ft_safe_memalloc(16, "md5_rounds");
	handler.hash0 = 0x67452301;
	handler.hash1 = 0xefcdab89;
	handler.hash2 = 0x98badcfe;
	handler.hash3 = 0x10325476;
	offset = 0;

	while (offset < size)
	{
		fill_chunk(chunk, &mem[offset]);
		offset += 64;
		before_round(&handler);
		make_round(&handler, chunk);
		after_round(&handler);
	}
	take_byte_from_int(&result->content[0], handler.hash0);
	take_byte_from_int(&result->content[4], handler.hash1);
	take_byte_from_int(&result->content[8], handler.hash2);
	take_byte_from_int(&result->content[12], handler.hash3);
	return (result);
}

t_list *md5(void *to_hash_mem, size_t to_hash_size)
{
	uint8_t *hash_mem;
	size_t hash_size;
	size_t offset;
	t_list *result;

	offset = 64 - to_hash_size % 64;
	hash_size = to_hash_size + offset;
	hash_mem = (uint8_t *)ft_safe_memalloc(hash_size, "md5");
	ft_mem_copy(hash_mem, to_hash_mem, to_hash_size);
	hash_mem[to_hash_size] = 0x80;
	//append_size(&hash_mem[hash_size - 8], to_hash_size);
	take_byte_from_int(&hash_mem[hash_size - 8], to_hash_size*8);
	take_byte_from_int(&hash_mem[hash_size - 4], to_hash_size >> 29);
	offset++;
	result = md5_rounds(hash_mem, hash_size);
	free(hash_mem);
	return (result);
}