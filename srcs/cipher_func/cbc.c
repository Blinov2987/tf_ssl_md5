/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:46:41 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/14 18:18:45 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

void 	des_cbc_enc(uint64_t *mem, size_t size, t_key_vector *key_vector,
		uint64_t (*cipher)(uint64_t, uint64_t *))
{
	size_t round;
	uint64_t current;
	uint64_t keys[48];
	uint64_t vector;

	round = 0;
	key_gen(keys, key_vector->keys[0]);
	key_gen(&keys[16], key_vector->keys[1]);
	key_gen(&keys[32], key_vector->keys[2]);
	vector = key_vector->vector;
	while (round < size)
	{
		mem[round] ^= vector;
		current = cipher(mem[round], keys);
		mem[round] = current;
		vector = current;
		round++;
	}
}

void 	des_cbc_dec(uint64_t *mem, size_t size, t_key_vector *key_vector,
		uint64_t (*cipher)(uint64_t, uint64_t *))
{
	size_t round;
	uint64_t current;
	uint64_t keys[48];
	uint64_t vector;
	uint64_t vector2;

	round = 0;
	key_gen(keys, key_vector->keys[0]);
	key_gen(&keys[16], key_vector->keys[1]);
	key_gen(&keys[32], key_vector->keys[2]);
	vector2 = key_vector->vector;
	while (round < size)
	{
		vector = mem[round];
		current = cipher(mem[round], keys);
		mem[round] = current;
		mem[round] ^= vector2;
		vector2 = vector;
		round++;
	}
}