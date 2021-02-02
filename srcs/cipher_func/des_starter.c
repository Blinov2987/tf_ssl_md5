/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/02 19:37:15 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t perrm_64(uint64_t num, uint8_t ip_tab[])
{
	uint64_t	result;
	int			i;

	i = -1;
	result = 0;
	while (++i < 64)
	{
		result <<= 1;
		result += num >> (64 - ip_tab[i]);
	}
	return (result);
}

t_list *des(void *mem, size_t size, void *key)
{

}