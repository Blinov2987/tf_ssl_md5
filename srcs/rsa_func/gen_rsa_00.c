/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:29:35 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/17 21:36:50 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

uint32_t get_nod(uint32_t val, uint32_t rand)
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
		return get_nod((val - rand) >> 2, rand);

}

uint32_t get_rand_uint(uint32_t val)
{
	int fd;
	uint32_t rand;

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

int		get_pow_remainder(uint32_t x, uint32_t pow, uint32_t mod)
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

int		miller_rabin_step(uint32_t s, uint32_t x, uint32_t val)
{
	int r;

	r = 0;
	while (++r < s)
	{
		x = get_pow_remainder(x, 2, val);
		if (x == 1)
			return FALSE;
		if (x == val - 1)
			break;
	}
	return (TRUE);
}

int		miller_rabin_cycle(uint32_t val, int k, uint32_t t, uint32_t s)
{
	int i;
	uint32_t x;

	i = -1;
	while (++i < k)
	{
		x = get_rand_uint(val);
		x = get_pow_remainder(x, t, val);
		if (x == 1 || x == val - 1)
		{
			write(1, "+", 1);
			continue;
		}
		if (!miller_rabin_step(s, x, val))
			return (FALSE);
		if (x != val - 1)
			return FALSE;
		write(1, "+", 1);
	}
	return (val);
}

int 	miller_rabin(uint32_t val, int k)
{
	uint32_t t;
	uint32_t s;

	if (val == 2 || val == 3)
		return (val);
	if (val < 2 || val % 2 == 0)
		return FALSE;
	t = val - 1;
	s = 0;
	while (t % 2 == 0)
	{
		t /= 2;
		s += 1;
	}
	return (miller_rabin_cycle(val, k, t, s));
}

uint32_t  get_rand_prime(void)
{
	uint32_t prime;

	prime = 0;
	while (!prime)
	{
		prime = 0;
		prime = get_rand_uint(prime);
		prime = miller_rabin(prime, 5);
		if (!prime)
			write(1, ".", 1);
	}
	write(1, "\n", 1);
	return (prime);
}


void 	extended_euclid(uint64_t a, uint64_t b, long *x)
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



void 	gen_rsa(t_rsa_args *args, t_rsa_output *output)
{
	t_rsa_key key;

	ft_bzero(&key, sizeof(t_rsa_key));
	key.prime1 = get_rand_prime();
	ft_printf("%u\n", key.prime1);
	key.prime2 = get_rand_prime();
	ft_printf("%u\n", key.prime2);
	key.prime1 = 3383235047;
	key.prime2 = 3360900689;
	key.modulus =(uint64_t)key.prime1 * (uint64_t)key.prime2;
	ft_printf("key.modulus = %llu\n", key.modulus);
	uint64_t eiler = (uint64_t)(key.prime1 - 1) * (uint64_t)(key.prime2 - 1);
	key.public_exponent = 0x10001;
	long euklid = 0;
	extended_euclid(key.public_exponent, eiler, &euklid);
	if (euklid < 0)
		key.private_exponent = euklid + eiler;
	else
		key.private_exponent = euklid;
	key.exponent1 = key.private_exponent % (key.prime1 - 1);
	key.exponent2 = key.private_exponent % (key.prime2 - 1);
	key.coefficient =get_pow_remainder(key.prime2, key.prime1 - 2, key.prime1);
	get_der_form(key);
	int i = 5;
	i++;
	if (i < 4)
		return;
}