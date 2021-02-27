/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 09:49:49 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 09:53:52 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

uint64_t		perrm_64(uint64_t num, const uint8_t ip_tab[], size_t tab_len,
		size_t size)
{
	uint64_t	result;
	size_t		i;

	i = 0;
	result = 0;
	while (i < tab_len)
	{
		result <<= 1;
		result += (num >> (size - ip_tab[i]) & 1);
		i++;
	}
	return (result);
}

void			fill_point_arr(uint64_t pointers, uint8_t point_arr[])
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

uint8_t			take_inbox_row(uint8_t num)
{
	return (((num >> 4) & 2) | (num & 1)) * 16;
}

uint8_t			take_inbox_column(uint8_t num)
{
	return ((num >> 1) & 0xf);
}

uint32_t		boxes(uint64_t pointers)
{
	uint8_t		point_arr[8];
	uint32_t	result;
	uint8_t		shift;
	int			i;

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
