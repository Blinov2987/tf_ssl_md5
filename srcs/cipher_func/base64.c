/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:35:05 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/28 19:37:13 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_list *base64_enc(void *mem, size_t size)
{
	int rounds;
	int offset;
	t_list *result;

	rounds = size / 3;
	offset = size % 3;
	result = (t_list *)ft_safe_memalloc(sizeof(t_list), "base64_enc");
	result->content_size = 4 * rounds + (offset ? 1 : 0);
	result->content = ft_safe_memalloc(result->content_size, "base64_enc");
	return (result);
}

t_list *base64_dec(void *mem, size_t size)
{

}