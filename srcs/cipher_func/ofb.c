/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:44:06 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/14 19:47:42 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

void 	des_ofb_enc(uint64_t *mem, size_t size, t_key_vector *key_vector,
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
		current = cipher(vector, keys);
		vector = current;
		mem[round] ^= current;
		round++;
	}
}

void 	des_ofb_dec(uint64_t *mem, size_t size, t_key_vector *key_vector,
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
		current = cipher(vector, keys);
		vector = current;
		mem[round] ^= current;
		round++;
	}
}
