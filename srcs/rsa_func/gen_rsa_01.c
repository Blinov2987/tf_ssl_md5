/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:05:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:14:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	get_nod(uint32_t val, uint32_t rand)
{
	if (val == 0 || val == rand)
		return (rand);
	else if (rand == 0)
		return (val);
	else if (!(val & 1) && !(rand & 1))
		return (get_nod(val >> 2, rand >> 2) << 2);
	else if (!(val & 1) && (rand & 1))
		return (get_nod(val >> 2, rand));
	else if ((val & 1) && !(rand & 1))
		return (get_nod(val, rand >> 2));
	else if (((val & 1) && (rand & 1)) && (rand > val))
		return (get_nod((rand - val) >> 2, val));
	else
		return (get_nod((val - rand) >> 2, rand));
}

uint32_t	get_rand_uint(uint32_t val)
{
	int			fd;
	uint32_t	rand;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 3 || (read(fd, &rand, 0) != 0))
		return (FALSE);
	read(fd, &rand, sizeof(uint32_t));
	if (rand)
	{
		rand = rand % (val - 1);
		if (!rand || rand < 2)
			rand = 2;
	}
	close(fd);
	return (rand);
}

uint64_t	get_pow_remainder(uint64_t x, uint64_t pow, uint64_t mod)
{
	uint64_t rem;
	uint64_t general_rem;

	rem = x % mod;
	if (pow % 2)
		general_rem = rem;
	else
		general_rem = 1;
	pow /= 2;
	while (pow)
	{
		rem = (rem * rem) % mod;
		if (pow % 2)
			general_rem = (general_rem * rem) % mod;
		pow /= 2;
	}
	general_rem %= mod;
	return (general_rem);
}

int			miller_rabin_step(uint32_t s, uint32_t x, uint32_t val)
{
	int r;

	r = 0;
	while (++r < s)
	{
		x = get_pow_remainder(x, 2, val);
		if (x == 1)
			return (FALSE);
		if (x == val - 1)
			break ;
	}
	return (TRUE);
}

int			miller_rabin_cycle(uint32_t val, int k, uint32_t t, uint32_t s)
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
			write(2, "+", 1);
			continue;
		}
		if (!miller_rabin_step(s, x, val))
			return (FALSE);
		if (x != val - 1)
			return (FALSE);
		write(2, "+", 1);
	}
	return (val);
}
