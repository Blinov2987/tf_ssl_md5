/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_enc_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:18:31 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/31 17:35:14 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

void	base64_enc_round(uint8_t *mem, uint8_t *result_mem)
{
	result_mem[0] = (mem[0]) >> 2;
	result_mem[1] = ((mem[0] << 4) & 0x30) | (mem[1] >> 4);
	result_mem[2] = ((mem[1] << 2) & 0x3c) | ((mem[2] >> 6));
	result_mem[3] = (mem[2] & 0x3f);
}

void	base_64_enc_last_round(uint8_t *mem, uint8_t *result_mem, size_t offset)
{
	uint8_t buf[3];

	ft_bzero(buf, 3);
	ft_mem_copy(buf, mem, offset);
	base64_enc_round(buf, result_mem);
	if (offset > 0)
		result_mem[3] = 64;
	if (offset == 1)
		result_mem[2] = 64;
}

void	base64_enc_wrap(uint8_t *mem, size_t size, t_list *result)
{
	size_t	rounds_len;
	size_t	mem_ind;
	size_t	result_mem_ind;
	size_t	offset;
	int		round;

	offset = size % 3;
	rounds_len = offset ? (result->content_size / 4) - 1
			: result->content_size / 4;
	mem_ind = 0;
	result_mem_ind = 0;
	round = 0;
	while (round < rounds_len)
	{
		base64_enc_round(&mem[mem_ind], &result->content[result_mem_ind]);
		result_mem_ind += 4;
		mem_ind += 3;
		round++;
	}
	if (offset)
		base_64_enc_last_round(&mem[mem_ind], &result->content[result_mem_ind]
				, offset);
}
