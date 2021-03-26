/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_pub_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:05:51 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/21 16:22:02 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int rsa_pub_checker(t_list *pub_key)
{
	uint8_t *key_mem;
	uint32_t seq_start;

	if (pub_key->content_size < 34)
		return (FALSE);
	key_mem = (uint8_t *)pub_key->content;
	seq_start = 1;
	while (++seq_start < pub_key->content_size)
	{
		if (key_mem[seq_start] == 0x30)
			break ;
	}
	if (seq_start == pub_key->content_size
		|| (pub_key->content_size - seq_start) < 16)
		return (FALSE);
	if (key_mem[0] != 0x30 || ft_memcmp(&key_mem[seq_start],
			g_pub_key_version, 16))
		return (FALSE);
	return (TRUE);
}