/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:07:54 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:14:37 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int		miller_rabin_silent_cycle(uint32_t val, int k, uint32_t t, uint32_t s)
{
	int			i;
	uint32_t	x;

	i = -1;
	while (++i < k)
	{
		x = get_rand_uint(val);
		x = get_pow_remainder(x, t, val);
		if (x == 1 || x == val - 1)
		{
			continue;
		}
		if (!miller_rabin_step(s, x, val))
			return (FALSE);
		if (x != val - 1)
			return (FALSE);
	}
	return (val);
}
