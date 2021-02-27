/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_dec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:41:10 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 09:33:32 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

void	base64_dec_round(uint8_t *mem, uint8_t *result_mem)
{
	result_mem[0] = (mem[0] << 2) | (mem[1] >> 4);
	result_mem[1] = ((mem[1] & 0x0f) << 4) | (mem[2] >> 2);
	result_mem[2] = (mem[2] << 6) | mem[3];
}

void	base_64_dec_last_round(uint8_t *mem, uint8_t *result_mem, size_t offset)
{
	if (offset == 2)
	{
		result_mem[0] = (mem[0] << 2) | (mem[1] >> 4);
	}
	if (offset == 1)
	{
		result_mem[0] = (mem[0] << 2) | (mem[1] >> 4);
		result_mem[1] = ((mem[1] & 0x0f) << 4) | (mem[2] >> 2);
	}
}

void	base64_dec_wrap(uint8_t *mem, size_t offset, t_list *result)
{
	size_t	rounds_len;
	size_t	mem_ind;
	size_t	result_mem_ind;
	size_t	round;

	rounds_len = result->content_size / 3;
	mem_ind = 0;
	result_mem_ind = 0;
	round = 0;
	while (round < rounds_len)
	{
		base64_dec_round(&mem[mem_ind], &result->content[result_mem_ind]);
		result_mem_ind += 3;
		mem_ind += 4;
		round++;
	}
	if (offset)
		base_64_dec_last_round(&mem[mem_ind], &result->content[result_mem_ind]
				, offset);
}
