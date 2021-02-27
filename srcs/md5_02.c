/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:08:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:46:50 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

t_list		*fill_hash_512(t_handler *handler)
{
	t_list	*result;

	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "fill_hash_512");
	result->content_size = 16;
	result->content = (uint8_t *)ft_safe_memalloc(16, "fill_hash_512");
	take_byte_from_int(&result->content[0], handler->hash0);
	take_byte_from_int(&result->content[4], handler->hash1);
	take_byte_from_int(&result->content[8], handler->hash2);
	take_byte_from_int(&result->content[12], handler->hash3);
	return (result);
}

void		init_hash_buf(t_handler *handler)
{
	handler->hash0 = 0x67452301;
	handler->hash1 = 0xefcdab89;
	handler->hash2 = 0x98badcfe;
	handler->hash3 = 0x10325476;
}

void		before_round(t_handler *handler)
{
	handler->a = handler->hash0;
	handler->b = handler->hash1;
	handler->c = handler->hash2;
	handler->d = handler->hash3;
}

void		after_round(t_handler *handler)
{
	handler->hash0 += handler->a;
	handler->hash1 += handler->b;
	handler->hash2 += handler->c;
	handler->hash3 += handler->d;
}
