/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_des_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:23:23 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 11:24:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		get_salt_from_content(t_des_args *args, t_crypt_output *output)
{
	void	*mem;
	size_t	new_size;

	new_size = output->mem->content_size - 16;
	mem = ft_safe_memalloc(new_size, "get_salt_from_content");
	ft_mem_copy(args->salt->content,
			&((uint8_t *)output->mem->content)[8], 8);
	ft_mem_copy(mem, &((uint8_t *)output->mem->content)[16], new_size);
	free(output->mem->content);
	output->mem->content = mem;
	output->mem->content_size = new_size;
}
