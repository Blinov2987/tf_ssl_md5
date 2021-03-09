/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 10:25:46 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

void		convert64t_mem(uint8_t *dest, uint64_t *mem, size_t size_in_byte)
{
	size_t i;
	size_t byte_ind;

	i = 0;
	byte_ind = 0;
	while (i < size_in_byte / 8)
	{
		take_byte_from_int_sha512(&dest[byte_ind], mem[i]);
		byte_ind += 8;
		i++;
	}
}

void		append_mem_to_cipher(void *mem, size_t size,
			t_list *result, t_des_args *args)
{
	size_t	offset;
	size_t	i;

	i = 0;
	offset = 0;
	if (!args->flag_d || args->algo > PCBC)
		offset = (size % 8) ? (8 - (size % 8)) : 8;
	result->content_size = size + offset;
	result->content = ft_safe_memalloc(result->content_size,
			"append_mem_to_cipher");
	ft_mem_copy(result->content, mem, size);
	if (offset)
	{
		while (i < offset)
		{
			((uint8_t *)result->content)[size + i] = (uint8_t)offset;
			i++;
		}
	}
}

void		decrease_content(t_list *result)
{
	uint8_t offset;
	uint8_t *mem;

	if (!(result && result->content))
		return ;
	offset = 0;
	mem = (uint8_t *)result->content;
	if (!mem[result->content_size - 1])
		offset = 8;
	else
		offset = mem[result->content_size - 1];
	result->content_size -= offset;
}

static void	split_crypto_type(t_des_args *args,
			uint64_t **appended_mem, size_t rounds)
{
	void		(*cip)(uint64_t *, size_t, t_key_vector *, uint64_t (*)());
	uint64_t	(*des_template)(uint64_t, uint64_t *);

	cip = decide_cipher_mode(args);
	des_template = decide_des_template(args);
	cip(*appended_mem, rounds, &args->key_vector, des_template);
}

t_list		*general_cipher(void *mem, size_t size, t_des_args *args)
{
	uint64_t	*appended_mem;
	t_list		*result;
	size_t		i;
	size_t		cur_pos;

	result = ft_safe_memalloc(sizeof(t_list), "general_cipher");
	append_mem_to_cipher(mem, size, result, args);
	appended_mem = ft_safe_memalloc(result->content_size, "general_cipher");
	i = 0;
	cur_pos = 0;
	while (i < (result->content_size / 8))
	{
		appended_mem[i] = take_uint64_from_uint8(&result->content[cur_pos]);
		cur_pos += 8;
		i++;
	}
	ft_bzero(result->content, result->content_size);
	split_crypto_type(args, &appended_mem, result->content_size / 8);
	convert64t_mem(result->content, appended_mem, result->content_size);
	if (args->flag_d && args->algo < OFB)
		decrease_content(result);
	if (args->algo > PCBC)
		result->content_size = size;
	free(appended_mem);
	return (result);
}
