/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:42:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:15:43 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

static void	make_round(t_handler *hndlr, uint64_t words[64])
{
	int round;

	round = -1;
	while (++round < 80)
	{
		if (round > 15)
			word_gen_512(words, round);
		hndlr->temp1 = hndlr->h + sum1_512(hndlr->e)
						+ chan_512(hndlr->e, hndlr->f, hndlr->g)
						+ g_const_512[round] + words[round];
		hndlr->temp2 = sum0_512(hndlr->a)
						+ maj_512(hndlr->a, hndlr->b, hndlr->c);
		hndlr->h = hndlr->g;
		hndlr->g = hndlr->f;
		hndlr->f = hndlr->e;
		hndlr->e = hndlr->d + hndlr->temp1;
		hndlr->d = hndlr->c;
		hndlr->c = hndlr->b;
		hndlr->b = hndlr->a;
		hndlr->a = hndlr->temp1 + hndlr->temp2;
	}
}

void		fill_chunk_sha512(uint64_t *chunk, uint8_t *mem)
{
	int i;
	int current_mem;

	i = -1;
	current_mem = 0;
	while (++i < 16)
	{
		chunk[i] = take_uint64_from_uint8(&mem[current_mem]);
		current_mem += 8;
	}
}

t_list		*sha512_rounds(uint8_t *mem, size_t size)
{
	t_handler	handler;
	size_t		offset;
	uint64_t	chunk[128];
	t_list		*result;

	ft_bzero(&handler, sizeof(t_handler));
	ft_bzero(chunk, 1024);
	init_hash_buf_sha512(&handler);
	offset = 0;
	while (offset < size)
	{
		fill_chunk_sha512(chunk, &mem[offset]);
		offset += 128;
		before_round_sha512(&handler);
		make_round(&handler, chunk);
		after_round_sha512(&handler);
	}
	result = fill_hash_buffer_sha512(&handler);
	return (result);
}

t_list		*append_mem_len_sha512(void *to_hash_mem,
				size_t to_hash_size, size_t mod_len)
{
	uint8_t	*hash_mem;
	size_t	hash_size;
	size_t	offset;
	size_t	bit_len;
	t_list	*result;

	offset = mod_len - to_hash_size % mod_len;
	if (offset <= 16)
		offset += 128;
	hash_size = to_hash_size + offset;
	hash_mem = (uint8_t *)ft_safe_memalloc(hash_size, "append_mem_len");
	ft_mem_copy(hash_mem, to_hash_mem, to_hash_size);
	hash_mem[to_hash_size] = 0x80;
	bit_len = ft_swap64(to_hash_size * 8);
	ft_mem_copy(&hash_mem[hash_size - 8], &bit_len, 8);
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "append_mem_len");
	result->content_size = hash_size;
	result->content = hash_mem;
	return (result);
}

t_list		*sha512(void *to_hash_mem, size_t to_hash_size)
{
	t_list *appended_mem_to_hash;
	t_list *result;

	appended_mem_to_hash = append_mem_len_sha512(to_hash_mem,
			to_hash_size, 128);
	result = sha512_rounds(appended_mem_to_hash->content,
			appended_mem_to_hash->content_size);
	free(appended_mem_to_hash->content);
	free(appended_mem_to_hash);
	return (result);
}
