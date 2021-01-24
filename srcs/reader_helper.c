/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:39:32 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/24 18:40:06 by gemerald         ###   ########.fr       */
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

t_list *concat_list(t_list *asylum, size_t size)
{
	t_list *mem_zone;
	t_list *current;
	size_t current_ind;

	mem_zone = (t_list *)ft_safe_memalloc(sizeof(t_list), "concat_list");
	current_ind = 0;
	mem_zone->content_size = size;
	mem_zone->content = ft_safe_memalloc(size, "concat_list");

	while (asylum)
	{
		current = asylum;
		asylum = asylum->next;
		ft_mem_copy(&mem_zone->content[current_ind], current->content, current->content_size);
		current_ind += current->content_size;
		free(current->content);
		free(current);
	}
	return (mem_zone);
}

t_list *buffered_reader(int fd)
{
	uint8_t buf[128];
	uint8_t zero_board;
	size_t  size;
	t_list  *asylum;
	t_list *mem_zone;

	if (fd < 0)
		return (NULL);
	ft_bzero(&buf, 129);
	asylum = NULL;
	mem_zone = NULL;
	size = 0;
	while ((zero_board = read(fd, buf, 128)) > 0)
	{
		ft_lstadd_back(&asylum, ft_lstnew(buf, zero_board));
		size += zero_board;
	}
	if (!asylum)
		return (ft_lstnew(NULL, 0));
	return (mem_zone);
}

t_list *buffered_file_reader(t_args *args)
{
	int fd;
	t_list *output_stream;
	t_list *files;
	char filename[200];
	char buf;

	output_stream = NULL;
	files = args->filenames;
	while (files)
	{
		ft_bzero(filename, 200);
		ft_mem_copy(filename, files->content, files->content_size);
		fd = open(filename, O_RDONLY);
		if (fd > 2 && !(read(fd, &buf, 0)))
		{
			ft_lstadd_back(&output_stream, buffered_reader(fd));
			close(fd);
		}
		else
			ft_lstadd_back(&output_stream, ft_lstnew(NULL, 0));
		files = files->next;
	}
	return (output_stream);
}