/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:35:05 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/31 18:53:55 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

t_list *base64_enc(void *mem, size_t size)
{
	size_t rounds;
	size_t offset;
	t_list *result;

	rounds = size / 3;
	offset = size % 3;
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "base64_enc");
	result->content_size = 4 * (rounds + (offset ? 1 : 0));
	result->content = ft_safe_memalloc(result->content_size, "base64_enc");
	base64_enc_wrap(mem, size, result);
	return (result);
}

t_list *base64_dec(void *mem, size_t size)
{
	size_t rounds;
	size_t offset;
	t_list *result;

	if (size == 0)
		return (ft_lstnew(NULL, 0));
	offset = 0;
	rounds = size;
	while (((uint8_t *)mem)[--rounds] == 64)
		offset++;
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "base64_enc");
	rounds = size / 4;
	result->content_size = (3 * rounds) - offset;
	result->content = ft_safe_memalloc(result->content_size, "base64_enc");
	base64_dec_wrap(mem, size, offset, result);
	return (result);
}