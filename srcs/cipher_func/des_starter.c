/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/19 18:48:39 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

uint64_t perrm_64(uint64_t num, const uint8_t ip_tab[], size_t tab_len, size_t size)
{
	uint64_t	result;
	int			i;

	i = -1;
	result = 0;
	while (++i < tab_len)
	{
		result <<= 1;
		result += (num >> (size - ip_tab[i]) & 1);
	}
	return (result);
}

void 	fill_point_arr(uint64_t pointers, uint8_t point_arr[])
{
	int i;
	int shift;

	i = -1;
	shift = 48;
	while (++i < 8)
	{
		shift -= 6;
		point_arr[i] = (pointers >> shift) & 0x3f;
	}
}

uint8_t	take_inbox_row(uint8_t num)
{
	return (((num >> 4) & 2) | (num & 1)) * 16;
}

uint8_t take_inbox_column(uint8_t num)
{
	return ((num >> 1) & 0xf);
}

uint32_t boxes(uint64_t pointers)
{
	uint8_t point_arr[8];
	uint32_t result;
	uint8_t shift;
	int i;

	i = -1;
	result = 0;
	fill_point_arr(pointers, point_arr);
	while (++i < 8)
	{
		result <<= 4;
		shift = take_inbox_row(point_arr[i]) + take_inbox_column(point_arr[i]);
		result += g_rounds[i][shift];
	}
	return (result);
}

uint32_t f_expansion(uint32_t part, uint64_t key)
{
	uint32_t result;
	uint64_t expanded;
	uint32_t final;

	expanded = perrm_64(part, g_extend, 48, 32);
	expanded ^= key;
	result = boxes(expanded);
	final = perrm_64(result, g_final_f_perm, 32, 32);
	return (final);
}

uint64_t  make_f_net(uint64_t num, uint64_t key[])
{
	int i;
	uint64_t result;
	uint32_t left[17];
	uint32_t right[17];

	i = 0;
	left[0] = (uint32_t)(num >> 32);
	right[0] = (uint32_t)num;
	while (++i < 17)
	{
		left[i] = right[i - 1];
		right[i] = left[i - 1] ^ f_expansion(right[i - 1], key[i - 1]);
	}
	result = ((uint64_t)right[16] << 32) | left[16];
	return (result);
}

uint32_t left_shift_28b(uint32_t val, uint32_t shift)
{
	return (val >> (28 - shift)) | ((val << shift) & 0xfffffff);
}

void 	key_gen(uint64_t keys[16], uint64_t orig_key)
{
	int i;
	uint32_t in_left;
	uint32_t in_right;
	uint32_t halfs[32];
	uint64_t permut_key;

	i = 0;
	ft_bzero(keys, 8 * 16);
	ft_bzero(halfs, 4 * 32);
	permut_key = perrm_64(orig_key, g_key_ext_in, 56, 64);
	in_left = permut_key >> 28;;
	in_right = permut_key & 0xfffffff;
	while (i < 31)
	{
		halfs[i] = left_shift_28b(in_left, g_shift_left[i / 2]);
		halfs[i + 1] = left_shift_28b(in_right, g_shift_left[i / 2]);
		in_left = halfs[i];
		in_right = halfs[i + 1];
		keys[i / 2] = (((uint64_t)in_left) << 28) | (uint64_t)in_right;
		keys[i / 2] = perrm_64(keys[i / 2], g_key_ext_out, 48, 56);
		i += 2;
	}
}

uint64_t 	pure_des_encrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = perrm_64(mem, g_ip_in, 64, 64);
	result = make_f_net(result, keys);
	result = perrm_64(result, g_ip_out, 64, 64);
	return (result);
}

uint64_t make_decrypt_f_net(uint64_t num, uint64_t key[])
{
	int i;
	uint64_t result;
	uint32_t left[17];
	uint32_t right[17];

	i = 17;
	right[16] = (uint32_t)(num >> 32);
	left[16] = (uint32_t)num;
	while (--i > 0)
	{
		left[i - 1] = right[i] ^ f_expansion(left[i], key[i - 1]);
		right[i - 1] = left[i];
	}
	result = ((uint64_t)left[0] << 32) | right[0];
	return (result);
}

uint64_t 	pure_des_decrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = perrm_64(mem, g_ip_in, 64, 64);
	result = make_decrypt_f_net(result, keys);
	result = perrm_64(result, g_ip_out, 64, 64);
	return (result);
}

void 	make_des_rounds(uint64_t *mem, size_t size, uint64_t key)
{
	size_t round;
	uint64_t current;
	uint64_t keys[16];

	round = 0;
	key_gen(keys, key);
	while (round < size)
	{
		current = pure_des_encrypt(mem[round], keys);
		current = pure_des_decrypt(current, keys);
		mem[round] = current;
		round++;
	}
}

void 	convert64t_mem(uint8_t *dest, uint64_t *mem, size_t size_in_byte)
{
	int i;
	int byte_ind;

	i = -1;
	byte_ind = 0;
	while (++i < size_in_byte / 8)
	{
		take_byte_from_int_sha512(&dest[byte_ind], mem[i]);
		byte_ind += 8;
	}
}

void 	append_mem_to_cipher(void *mem, size_t size, t_list *result, t_des_args *args)
{
	size_t offset;
	int i;

	i = -1;
	offset = 0;
	if (!args->flag_d || args->algo > PCBC)
		offset = (size % 8) ? (8 - (size % 8)) : 8;
	result->content_size = size + offset;
	result->content = ft_safe_memalloc(result->content_size,
			"append_mem_to_cipher");
	ft_mem_copy(result->content, mem, size);
	if (offset)
	{
		while (++i < offset)
			((uint8_t *)result->content)[size + i] = (uint8_t)offset;
	}
}

void 	decrease_content(t_list *result)
{
	uint8_t offset;
	uint8_t *mem;
	uint8_t *last_mem;

	if (!(result && result->content))
		return ;
	offset = 0;
	mem = (uint8_t *)result->content;
	last_mem = &mem[result->content_size - 8];
	if (!mem[result->content_size - 1])
		offset = 8;
	else
		offset = mem[result->content_size - 1];
	result->content_size -= offset;
}

t_list *general_cipher(void *mem, size_t size, t_key_vector *key_vector, t_des_args *args)
{
	uint64_t	*appended_mem;
	t_list		*result;
	size_t		i;
	size_t		cur_position;
	void	(*cipher_mode)(uint64_t *, size_t, t_key_vector *,
			uint64_t (*cipher)(uint64_t, uint64_t *));
	uint64_t  (*des_template)(uint64_t, uint64_t *);

	result = ft_safe_memalloc(sizeof(t_list), "general_cipher");
	append_mem_to_cipher(mem, size, result, args);
	appended_mem = ft_safe_memalloc(result->content_size, "general_cipher");
	i = 0;
	cur_position = 0;
	while (i < (result->content_size / 8))
	{
		appended_mem[i] = take_uint64_from_uint8(&result->content[cur_position]);
		cur_position += 8;
		i++;
	}
	ft_bzero(result->content, result->content_size);
	cipher_mode = decide_cipher_mode(args);
	des_template = decide_des_template(args);
	cipher_mode(appended_mem, result->content_size / 8, key_vector, des_template);
	//make_des_rounds(appended_mem, result->content_size / 8, key_vector->keys[0]);
	convert64t_mem(result->content, appended_mem, result->content_size);
	if (args->flag_d && args->algo < OFB)
		decrease_content(result);
	if (args->algo == OFB || args->algo == CFB)
		result->content_size = size;
	free(appended_mem);
	return (result);
}