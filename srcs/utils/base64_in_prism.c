/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_in_prism.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:47:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/31 17:36:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

void	in_base64_prism(uint8_t *mem, size_t *size)
{
	size_t i;
	int error;
	size_t cur_mem_ind;

	i = 0;
	cur_mem_ind = 0;
	error = FALSE;
	while (i < (*size))
	{
		if (ft_isspace(mem[i]))
		{
			i++;
			continue ;
		}
		mem[cur_mem_ind] = g_dec64[mem[i]];
		if (mem[cur_mem_ind] == 0xff)
			error = TRUE;
		i++;
		cur_mem_ind++;
	}
	if (error || (cur_mem_ind % 4))
		*size = 0;
	else
		*size = cur_mem_ind;
}

void	out_base64_prism(uint8_t *mem, size_t *size)
{
	size_t cur_mem_ind;

	cur_mem_ind = 0;
	while (cur_mem_ind < (*size))
	{
		mem[cur_mem_ind] = g_enc64[mem[cur_mem_ind]];
		cur_mem_ind++;
	}
}