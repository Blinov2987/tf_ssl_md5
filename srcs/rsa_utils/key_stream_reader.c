/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_stream_reader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:41:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:26:21 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

size_t		get_end_offset(uint8_t *mem, size_t size)
{
	size_t offset;

	offset = 0;
	while (--size > 0)
	{
		if (!ft_isspace(mem[size]))
			break ;
		offset++;
	}
	return (offset);
}

int			cut_start_end(t_list **pem, size_t diff, size_t off)
{
	uint8_t	*new_mem;
	size_t	new_size;

	new_size = (*pem)->content_size - diff;
	new_mem = (uint8_t *)ft_safe_memalloc(new_size, "cut_priv");
	ft_mem_copy(new_mem, (&((uint8_t *)(*pem)->content)[off]), new_size);
	free((*pem)->content);
	(*pem)->content = new_mem;
	(*pem)->content_size = new_size;
	return (TRUE);
}

int			read_pem_form(t_list *pem, t_rsa_output *output)
{
	size_t endl_offset;

	if (pem->content_size < 50)
		return (FALSE);
	endl_offset = get_end_offset(pem->content, pem->content_size);
	if ((!ft_memcmp(pem->content, RSA_PRIV_START, 32) && (
			!ft_memcmp(&((uint8_t *)pem->content)[(pem->content_size - 30
			- endl_offset)],
					RSA_PRIV_END, 30))))
	{
		output->is_private_key_found = 1;
		return (cut_start_end(&pem, 62 + endl_offset, 32));
	}
	else if ((!ft_memcmp(pem->content, RSA_PUB_START, 27) && (
			!ft_memcmp(&((uint8_t *)pem->content)[(pem->content_size - 25
			- endl_offset)],
					RSA_PUB_END, 25))))
	{
		return (cut_start_end(&pem, 52 + endl_offset, 27));
	}
	return (FALSE);
}
