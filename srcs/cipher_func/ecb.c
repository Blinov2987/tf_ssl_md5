/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:33:06 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/14 17:49:17 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

void 	des_ecb(uint64_t *mem, size_t size, t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *))
{
	size_t round;
	uint64_t current;
	uint64_t keys[48];

	round = 0;
	key_gen(keys, key_vector->keys[0]);
	key_gen(&keys[16], key_vector->keys[1]);
	key_gen(&keys[32], key_vector->keys[2]);
	while (round < size)
	{
		current = cipher(mem[round], keys);
		mem[round] = current;
		round++;
	}
}