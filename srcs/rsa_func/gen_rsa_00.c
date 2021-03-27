/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:29:35 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:11:04 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int			miller_rabin(uint32_t val, int k, uint8_t is_silent)
{
	uint32_t t;
	uint32_t s;

	if (val == 2 || val == 3)
		return (val);
	if (val < 2 || val % 2 == 0)
		return (FALSE);
	t = val - 1;
	s = 0;
	while (t % 2 == 0)
	{
		t /= 2;
		s += 1;
	}
	if (is_silent)
		return (miller_rabin_silent_cycle(val, k, t, s));
	else
		return (miller_rabin_cycle(val, k, t, s));
}

uint32_t	get_rand_prime(void)
{
	uint32_t prime;

	prime = 0;
	while (!prime)
	{
		prime = 0;
		prime = get_rand_uint(prime);
		prime = miller_rabin(prime, 5, 0);
		if (!prime)
			write(2, ".", 1);
	}
	write(2, "\n", 1);
	return (prime);
}

void		extended_euclid(uint64_t a, uint64_t b, long *x)
{
	t_ext_euclid e;

	ft_bzero(&e, sizeof(t_ext_euclid));
	e.x2 = 1;
	e.y1 = 1;
	while (b > 0)
	{
		e.q = a / b;
		e.r = a - e.q * b;
		*x = e.x2 - e.q * e.x1;
		e.y = e.y2 - e.q * e.y1;
		a = b;
		b = e.r;
		e.x2 = e.x1;
		e.x1 = *x;
		e.y2 = e.y1;
		e.y1 = e.y;
	}
	*x = e.x2;
}

t_rsa_key	gen_rsa_key_on_primes(uint32_t prime1,
		uint32_t prime2, uint32_t pub_e)
{
	t_rsa_key	key;
	uint64_t	eiler;
	long		euklid;

	ft_bzero(&key, sizeof(t_rsa_key));
	key.prime1 = prime1;
	key.prime2 = prime2;
	key.modulus = (uint64_t)key.prime1 * (uint64_t)key.prime2;
	eiler = (uint64_t)(key.prime1 - 1) * (uint64_t)(key.prime2 - 1);
	key.public_exponent = pub_e;
	euklid = 0;
	extended_euclid(key.public_exponent, eiler, &euklid);
	if (euklid < 0)
		key.private_exponent = euklid + eiler;
	else
		key.private_exponent = euklid;
	key.exponent1 = key.private_exponent % (key.prime1 - 1);
	key.exponent2 = key.private_exponent % (key.prime2 - 1);
	key.coefficient = get_pow_remainder(key.prime2, key.prime1 - 2, key.prime1);
	return (key);
}

t_rsa_key	gen_rand_rsa(uint32_t pub_e)
{
	uint32_t prime1;
	uint32_t prime2;

	prime1 = get_rand_prime();
	prime2 = get_rand_prime();
	write(2, "e is 65537 (0x10001)\n", 21);
	return (gen_rsa_key_on_primes(prime1, prime2, pub_e));
}
