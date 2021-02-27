/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:23:36 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 09:49:43 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

uint64_t	pure_des_encrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = perrm_64(mem, g_ip_in, 64, 64);
	result = make_f_net(result, keys);
	result = perrm_64(result, g_ip_out, 64, 64);
	return (result);
}

uint64_t	pure_des_decrypt(uint64_t mem, uint64_t keys[])
{
	uint64_t result;

	result = perrm_64(mem, g_ip_in, 64, 64);
	result = make_decrypt_f_net(result, keys);
	result = perrm_64(result, g_ip_out, 64, 64);
	return (result);
}
