/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:52:13 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 10:28:10 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

uint32_t		f_expansion(uint32_t part, uint64_t key)
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

uint64_t		make_f_net(uint64_t num, uint64_t key[])
{
	int			i;
	uint64_t	result;
	uint32_t	left[17];
	uint32_t	right[17];

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

uint32_t		left_shift_28b(uint32_t val, uint32_t shift)
{
	return (val >> (28 - shift)) | ((val << shift) & 0xfffffff);
}

void			key_gen(uint64_t keys[16], uint64_t orig_key)
{
	int			i;
	uint32_t	in_left;
	uint32_t	in_right;
	uint32_t	halfs[32];
	uint64_t	permut_key;

	i = 0;
	ft_bzero(keys, 8 * 16);
	ft_bzero(halfs, 4 * 32);
	permut_key = perrm_64(orig_key, g_key_ext_in, 56, 64);
	in_left = permut_key >> 28;
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

uint64_t		make_decrypt_f_net(uint64_t num, uint64_t key[])
{
	int			i;
	uint64_t	result;
	uint32_t	left[17];
	uint32_t	right[17];

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
