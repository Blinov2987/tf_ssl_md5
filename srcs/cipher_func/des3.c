/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:00:31 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/14 17:08:32 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

uint64_t 	pure_des3_ede_encrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = pure_des_encrypt(mem, keys);
	result = pure_des_decrypt(result, &keys[16]);
	result = pure_des_encrypt(result, &keys[32]);
	return (result);
}

uint64_t 	pure_des3_ede_decrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = pure_des_decrypt(mem, keys);
	result = pure_des_encrypt(result, &keys[16]);
	result = pure_des_decrypt(result, &keys[32]);
	return (result);
}