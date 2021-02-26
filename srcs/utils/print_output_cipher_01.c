/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_cipher_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:19:01 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/26 19:29:17 by gemerald         ###   ########.fr       */
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

static void		print_base_files(t_des_args *args, t_crypt_output *output)
{
	int fd;

	fd = open(args->output_files->content, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		error_open_file(args->output_files->content);
		return ;
	}
	print_base64_stdout(fd, output->output_stream->content,
			output->output_stream->content_size);
	close(fd);
}

void 	print_output_des(t_des_args *args, t_crypt_output *output)
{
	if (!output->output_stream->content || !output->output_stream->content_size)
		return ;
	if (args->flag_a && !args->flag_d)
	{
		if (args->output_files)
			print_base_files(args, output);
		else
			print_base64_stdout(1, output->output_stream->content,
					output->output_stream->content_size);
	}
	else
	{
		if (args->output_files)
			print_files(args, output);
		else
			write(1, output->output_stream->content,
					output->output_stream->content_size);
	}

}