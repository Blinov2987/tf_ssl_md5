/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:39:32 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/22 21:37:31 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
void    ft_mem_copy(void *dest, void *src, size_t size)
{
	uint8_t *d;
	uint8_t *s;
	size_t current;

	d = (uint8_t *)dest;
	s = (uint8_t *)src;
	current = 0;
	while (current < size)
	{
		d[current] = s[current];
		current++;
	}
}

t_mem_zone concat_list(t_list *asylum, size_t size)
{
	t_mem_zone mem_zone;
	t_list *current;
	size_t current_ind;

	ft_bzero(&mem_zone, sizeof(mem_zone));
	current_ind = 0;
	mem_zone.size = size;
	mem_zone.mem = ft_safe_memalloc(size, "concat_list");

	while (asylum)
	{
		current = asylum;
		asylum = asylum->next;
		ft_mem_copy(&mem_zone.mem[current_ind], current->content, current->content_size);
		current_ind += current->content_size;
		free(current->content);
		free(current);
	}
	return (mem_zone);
}

t_mem_zone buffered_reader(int fd)
{
	uint8_t buf[128];
	uint8_t zero_board;
	size_t  size;
	t_list  *asylum;
	t_mem_zone mem_zone;

	ft_bzero(&mem_zone, sizeof(mem_zone));
	if (fd < 0)
		return (mem_zone);
	ft_bzero(&buf, 129);
	asylum = NULL;
	size = 0;
	while ((zero_board = read(fd, buf, 128)) > 0)
	{
		ft_lstadd_back(&asylum, ft_lstnew(buf, zero_board));
		size += zero_board;
	}
	mem_zone = concat_list(asylum, size);
	return (mem_zone);
}