/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:05:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/26 21:09:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

uint64_t s0_512(uint64_t x)
{
	return (rotate_right_512(x, 1) ^ rotate_right_512(x, 8) ^ shift_right_512(x, 7));
}

uint64_t s1_512(uint64_t x)
{
	return (rotate_right_512(x,19) ^ rotate_right_512(x,61) ^ shift_right_512(x,6));
}

uint64_t sum0_512(uint64_t x)
{
	return (rotate_right_512(x, 28) ^ rotate_right_512(x,34) ^ rotate_right_512(x,39));
}

uint64_t sum1_512(uint64_t x)
{
	return (rotate_right_512(x, 14) ^ rotate_right_512(x,18) ^ rotate_right_512(x,41));
}