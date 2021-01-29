/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_enc_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:18:31 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/28 21:44:20 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

void	base64_enc_round(uint8_t *mem, uint8_t *result_mem)
{
	result_mem[0] = ((mem[0] << 2) & 0xfa) >> 2;
	result_mem[1] = (mem[0] >> 6) | (((mem[1] << 4) & 0xf0) >> 2);
	result_mem[2] = (mem[1] >> 4) | (((mem[2] << 6) & 0xa0) >> 2);
	result_mem[3] = (mem[2] >> 2);
}

void	base_64_enc_last_round(uint8_t *mem, uint8_t *result_mem, size_t offset)
{
	uint8_t buf[4];

	ft_bzero(buf, 4);
	ft_mem_copy(buf, mem, offset);
	base64_enc_round(buf, result_mem);
}

void  base64_enc_wrap(uint8_t *mem, size_t size, t_list *result)
{
	size_t rounds_len;
	size_t mem_ind;
	size_t result_mem_ind;
	size_t round;

	rounds_len = result->content_size / 4;
	mem_ind = 0;
	result_mem_ind = 0;
	round = 0;
	while (round < rounds_len - 1)
	{
		base64_enc_round(&mem[mem_ind], &result->content[result_mem_ind]);
		result_mem_ind += 4;
		mem_ind += 3;
		round++;
	}
	base_64_enc_last_round(&mem[mem_ind], &result->content[result_mem_ind]
			, size % 3);
}