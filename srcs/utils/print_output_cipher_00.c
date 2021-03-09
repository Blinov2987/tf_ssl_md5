/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_cipher_00.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:48:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/26 19:29:17 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_base64_stdout(int fd, uint8_t *mem, size_t size)
{
	size_t offset;
	size_t cur_size;

	offset = 0;
	while (offset < size)
	{
		cur_size = 64;
		if (64 > (size - offset))
			cur_size = size - offset;
		write(fd, &mem[offset], cur_size);
		ft_putchar_fd('\n', fd);
		offset += 64;
	}
}

static void	print_files(t_base64_args *args, t_output *output)
{
	int fd;

	fd = open(args->output_files->content, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		error_open_file(args->output_files->content);
		return ;
	}
	if (args->flag_d)
	{
		write(fd, output->string_hash->content,
				output->string_hash->content_size);
	}
	else
	{
		print_base64_stdout(fd, output->string_hash->content,
				output->string_hash->content_size);
	}
	close(fd);
}

void		print_output_cipher(t_base64_args *args, t_output *output)
{
	if (!output->string_hash->content || !output->string_hash->content_size)
		return ;
	if (args->output_files)
		print_files(args, output);
	else if (args->flag_d)
	{
		write(1, output->string_hash->content,
				output->string_hash->content_size);
	}
	else
	{
		print_base64_stdout(1, output->string_hash->content,
				output->string_hash->content_size);
	}
}
