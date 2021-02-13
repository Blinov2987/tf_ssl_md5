/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_cipher_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:19:01 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 21:32:57 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		print_files(t_des_args *args, t_crypt_output *output)
{
	int fd;

	fd = open(args->output_files->content, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		error_open_file(args->output_files->content);
		return ;
	}
	write(fd, output->output_stream->content,
			output->output_stream->content_size);
	close(fd);
}

static void print_des_stdout(uint8_t *mem, size_t size)
{
	size_t offset;
	size_t cur_size;

	offset = 0;
	while (offset < size)
	{
		cur_size = 64;
		if (64 > (size - offset))
			cur_size = size - offset;
		write(1, &mem[offset], cur_size);
		ft_putchar('\n');
		offset += 64;
	}
}

void 	print_output_des(t_des_args *args, t_crypt_output *output)
{
	if (args->output_files)
		print_files(args, output);
	else
		write(0, output->output_stream->content,
				output->output_stream->content_size);
}