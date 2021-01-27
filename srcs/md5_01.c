/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 09:57:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:38:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static void	make_round(t_handler *hndl, uint32_t chunk[])
{
	int i;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			md5_round_shit_before_16(hndl, i);
		else if (i < 32)
			md5_round_shit_before_32(hndl, i);
		else if (i < 48)
			md5_round_shit_before_48(hndl, i);
		else
			md5_round_shit_before_64(hndl, i);
		hndl->swap = hndl->d;
		hndl->d = hndl->c;
		hndl->c = hndl->b;
		hndl->b = hndl->b + rotate_left((hndl->a + hndl->f + g_radians[i]
				+ chunk[hndl->g]), g_round_shift[i]);
		hndl->a = hndl->swap;
	}
}

t_list		*md5_rounds(uint8_t *mem, size_t size)
{
	t_handler	handler;
	size_t		offset;
	uint32_t	chunk[16];
	t_list		*result;

	ft_bzero(&handler, sizeof(t_handler));
	ft_bzero(chunk, 64);
	init_hash_buf(&handler);
	offset = 0;
	while (offset < size)
	{
		fill_chunk_512(chunk, &mem[offset]);
		offset += 64;
		before_round(&handler);
		make_round(&handler, chunk);
		after_round(&handler);
	}
	result = fill_hash_512(&handler);
	return (result);
}

t_list		*md5(void *to_hash_mem, size_t to_hash_size)
{
	t_list *appended_mem_to_hash;
	t_list *result;

	appended_mem_to_hash = append_mem_len(to_hash_mem, to_hash_size, 64);
	result = md5_rounds(appended_mem_to_hash->content,
			appended_mem_to_hash->content_size);
	free(appended_mem_to_hash->content);
	free(appended_mem_to_hash);
	return (result);
}
