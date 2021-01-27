/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:45:23 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:12:37 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

uint32_t	s0(uint32_t x)
{
	return (rotate_right(x, 7) ^ rotate_right(x, 18) ^ shift_right(x, 3));
}

uint32_t	s1(uint32_t x)
{
	return (rotate_right(x, 17) ^ rotate_right(x, 19) ^ shift_right(x, 10));
}

uint32_t	sum0(uint32_t x)
{
	return (rotate_right(x, 2) ^ rotate_right(x, 13) ^ rotate_right(x, 22));
}

uint32_t	sum1(uint32_t x)
{
	return (rotate_right(x, 6) ^ rotate_right(x, 11) ^ rotate_right(x, 25));
}
