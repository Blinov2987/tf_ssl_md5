/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:29:35 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/16 22:40:37 by gemerald         ###   ########.fr       */
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

int 	miller_rabin(uint32_t val, int k)
{
// если n == 2 или n == 3 - эти числа простые, возвращаем true
	if (val == 2 || val == 3)
		return (val);

	// если n < 2 или n четное - возвращаем false
	if (val < 2 || val % 2 == 0)
		return FALSE;

	// представим n − 1 в виде (2^s)·t, где t нечётно, это можно сделать последовательным делением n - 1 на 2
	uint32_t t = val - 1;

	uint32_t s = 0;

	while (t % 2 == 0)
	{
		t /= 2;
		s += 1;
	}

	// повторить k раз
	for (int i = 0; i < k; i++)
	{
		// выберем случайное целое число a в отрезке [2, n − 2]
		uint32_t a = get_rand_uint(val);

		// x ← a^t mod n, вычислим с помощью возведения в степень по модулю
//		a = 7;
//		t = 13;
//		val = 59;
		uint32_t x = get_pow_remainder(a, t, val);

		// если x == 1 или x == n − 1, то перейти на следующую итерацию цикла
		if (x == 1 || x == val - 1)
		{
			write(1, "+", 1);
			continue;
		}


		// повторить s − 1 раз
		for (int r = 1; r < s; r++)
		{
			// x ← x^2 mod n
			x = get_pow_remainder(x, 2, val);

			// если x == 1, то вернуть "составное"
			if (x == 1)
				return FALSE;

			// если x == n − 1, то перейти на следующую итерацию внешнего цикла
			if (x == val - 1)
				break;
		}

		if (x != val - 1)
			return FALSE;
		write(1, "+", 1);
	}

	// вернуть "вероятно простое"
	return (val);
}


int 	solovey_strassen(uint32_t val, int k)
{
	int i;
	uint32_t rand;
	uint32_t powered_rand;
	uint32_t jac_sym;

	i = -1;
	while (++i < k)
	{
		rand = get_rand_uint(val);
		if (get_nod(val, rand) > 1)
			return (FALSE);
//		jac_sym =
	}
	return (TRUE);
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


void extended_euclid(uint64_t a, uint64_t b, long *x)

/* calculates a * *x + b * *y = gcd(a, b) = *d */

{
	long y = 0;
//	(*y) = 0;
	long d = 1;
//	(*d) = 1;

	long q, r, x1, x2, y1, y2;

	x2 = 1, x1 = 0, y2 = 0, y1 = 1;

	while (b > 0) {

		q = a / b, r = a - q * b;

		*x = x2 - q * x1, y = y2 - q * y1;

		a = b, b = r;

		x2 = x1, x1 = *x, y2 = y1, y1 = y;

	}

	*x = x2;

}



void 	gen_rsa(t_rsa_args *args, t_rsa_output *output)
{
//	uint32_t x = 225227;
//	int result;
//	result = miller_rabin(x, 5);


	uint32_t p = get_rand_prime();
	ft_printf("%u\n", p);
	uint32_t q = get_rand_prime();
	ft_printf("%u\n", q);
	uint64_t multi =(uint64_t)p * (uint64_t)q;
	ft_printf("multi = %llu\n", multi);
	uint64_t eiler = (uint64_t)(p - 1) * (uint64_t)(q - 1);
	uint64_t pub_e = 0x10001;
//	int64_t priv_e;
	long euklid = 0;
	uint64_t ext_eucl;
	extended_euclid(pub_e, eiler, &euklid);
	if (euklid < 0)
		ext_eucl = euklid + eiler;
	else
		ext_eucl = euklid;
	int i = 5;
	i++;
	if (i < 4)
		return;
}

void some_trash(void)
{
	uint64_t max = 18446744073709551615;
	uint32_t max32 = 0xffffffff;
	uint64_t pow = 2;
	uint64_t count = 1;
	while (pow < max)
	{
		uint64_t prew_pow = pow;
		pow *= pow;
		if (prew_pow > pow)
		{
			ft_printf("max pow = %llu\n", prew_pow);
			break;
		}
		count++;
	}
}