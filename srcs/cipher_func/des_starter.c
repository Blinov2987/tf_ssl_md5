/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/11 18:27:58 by gemerald         ###   ########.fr       */
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

t_list *des_ecb(void *mem, size_t size, void *key)
{
	uint64_t u_key;
	uint64_t *appended_mem;
	size_t 	 appended_size;
	size_t i;
	size_t cur_position;

	u_key = take_uint64_from_uint8(key);
	appended_size = (size + (size % 8));
	appended_mem = ft_safe_memalloc(appended_size, "des_ecb");
	i = 0;
	cur_position = 0;
	while (i < (appended_size / 8))
	{
		appended_mem[i] = take_uint64_from_uint8((uint8_t *)&mem[cur_position]);
		cur_position += 8;
		i++;
	}
//	ft_mem_copy(appended_mem, mem, size);
	make_des_rounds(appended_mem, appended_size / 8, u_key);
}