/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:04:00 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:43:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	take_int_from_byte(uint8_t *mem)
{
	return ((uint32_t)mem[0]
			| ((uint32_t)mem[1] << 8)
			| ((uint32_t)mem[2] << 16)
			| ((uint32_t)mem[3] << 24));
}

void		take_byte_from_int(uint8_t *mem, uint32_t val)
{
	mem[0] = (uint8_t)(val);
	mem[1] = (uint8_t)(val >> 8);
	mem[2] = (uint8_t)(val >> 16);
	mem[3] = (uint8_t)(val >> 24);
}

void		fill_chunk_512(uint32_t *chunk, uint8_t *mem)
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

t_list		*append_mem_len(void *to_hash_mem,
				size_t to_hash_size, size_t mod_len)
{
	uint8_t		*hash_mem;
	size_t		hash_size;
	size_t		offset;
	t_list		*result;

	offset = mod_len - to_hash_size % mod_len;
	if (offset <= mod_len / 8)
		offset += 64;
	hash_size = to_hash_size + offset;
	hash_mem = (uint8_t *)ft_safe_memalloc(hash_size, "append_mem_len");
	ft_mem_copy(hash_mem, to_hash_mem, to_hash_size);
	hash_mem[to_hash_size] = 0x80;
	take_byte_from_int(&hash_mem[hash_size - 8], to_hash_size * 8);
	take_byte_from_int(&hash_mem[hash_size - 4], to_hash_size >> 29);
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "append_mem_len");
	result->content_size = hash_size;
	result->content = hash_mem;
	return (result);
}

uint32_t	rotate_left(uint32_t left, uint32_t right)
{
	return (((left) << (right)) | ((left) >> (32 - (right))));
}
