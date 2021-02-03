/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/03 21:09:04 by gemerald         ###   ########.fr       */
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
		result += (num >> (size - ip_tab[i]));
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

void 	make_des_rounds(uint64_t *mem, size_t size, uint64_t key)
{
	size_t round;
	uint64_t current;
	uint64_t result;
	uint32_t left;
	uint32_t right;

	round = 0;
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
	void *appended_mem;
	size_t 	 appended_size;

	u_key = take_uint64_from_uint8(key);
	appended_size = (size + (size % 8));
	appended_mem = ft_safe_memalloc(appended_size, "des");
	ft_mem_copy(appended_mem, mem, size);
	make_des_rounds(appended_mem, appended_size / 8, u_key);
}