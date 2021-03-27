/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_cipher_process_01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:16:42 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:19:05 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

uint64_t	safe_mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	uint64_t res;
	uint64_t temp_b;

	res = 0;
	if (b >= mod)
		b = (mod > UINT64_MAX / 2u) ? b - mod : b % mod;
	while (a != 0)
	{
		if (a & 1)
		{
			if (b >= mod - res)
				res -= mod;
			res += b;
		}
		a >>= 1;
		temp_b = b;
		if (b >= mod - b)
			temp_b -= mod;
		b += temp_b;
	}
	return (res);
}

uint64_t	mod_power_rem(uint64_t x, uint64_t pow, uint64_t mod)
{
	uint64_t power;
	uint64_t result;

	result = 1;
	power = x;
	while (pow > 0)
	{
		if ((pow & 1) == 1)
			result = safe_mul_mod(result, power, mod);
		power = safe_mul_mod(power, power, mod);
		pow >>= 1;
	}
	return (result);
}
