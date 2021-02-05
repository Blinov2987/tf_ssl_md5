/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/05 20:59:38 by gemerald         ###   ########.fr       */
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
	//	result += (num >> (ip_tab[i]));
	}
	return (result);
}

uint32_t feistel(uint32_t part, uint64_t key)
{
	uint32_t result;
	uint64_t expanded;

	expanded = perrm_64(part, g_extend, 48, 64);
}

uint64_t  make_f_net(uint64_t num, uint64_t key)
{
	int i;
	uint64_t result;
	uint32_t left;
	uint32_t right;

	i = -1;
	left = (uint32_t)(num >> 32);
	right = (uint32_t)num;
	while (++i < 16)
	{

	}
}

uint32_t left_shift_28b(uint32_t val, uint32_t shift)
{
	return (val >> (28 - shift)) | ((val << shift) & 0xfffffff);
}

void 	key_gen(uint64_t keys[], uint64_t orig_key)
{
	int i;
	uint32_t in_left;
	uint32_t in_right;
	uint32_t left[16];
	uint32_t right[16];
	uint64_t permut_key;

	i = -1;
	ft_bzero(keys, 8 * 16);
	ft_bzero(left, 4 * 16);
	ft_bzero(right, 4 * 16);
	permut_key = perrm_64(orig_key, g_key_ext, 56, 64);
	in_left = permut_key >> 28;;
	in_right = permut_key & 0xfffffff;
	while (++i < 16)
	{
		left[i] = left_shift_28b(in_left, g_shift_left[i]);
		right[i] = left_shift_28b(in_right, g_shift_left[i]);
		in_left = left[i];
		in_right = right[i];
	}
}

void 	make_des_rounds(uint64_t *mem, size_t size, uint64_t key)
{
	size_t round;
	uint64_t current;
	uint64_t result;
	uint32_t left;
	uint32_t right;
	uint64_t keys[16];

	round = 0;
	key_gen(keys, key);
	while (round < size)
	{
		current = perrm_64(mem[round], g_ip_in, 64, 64);
		current = perrm_64(current, g_ip_out, 64, 64);
		round++;
	}
}

t_list *des(void *mem, size_t size, void *key)
{
	uint64_t u_key;
	uint64_t *appended_mem;
	size_t 	 appended_size;
	size_t i;
	size_t cur_position;

	u_key = take_uint64_from_uint8(key);
	appended_size = (size + (size % 8));
	appended_mem = ft_safe_memalloc(appended_size, "des");
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