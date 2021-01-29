/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:03:41 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:27:29 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_print_by_size(char *str, size_t size, int fd)
{
	write(fd, str, size);
}

void	print_stdin(t_args *args, t_output *output)
{
	if (args->flag_p && output->stdin_stream)
	{
		ft_print_by_size(output->stdin_stream->content,
				output->stdin_stream->content_size, 1);
		ft_putchar('\n');
	}
	if (output->stdin_stream)
	{
		print_hex(output->stdin_hash->content,
				output->stdin_hash->content_size, 1);
		ft_putchar('\n');
	}
}

void	print_algo(t_args *args)
{
	char *algo;

	if (args->algo == MD5)
		algo = "MD5 ";
	if (args->algo == SHA256)
		algo = "SHA256 ";
	if (args->algo == SHA512)
		algo = "SHA512 ";
	ft_putstr(algo);
}

void	print_silent_files(t_list *tmp, t_list *stream)
{
	if (tmp->content)
	{
		print_hex(tmp->content, tmp->content_size, 1);
		ft_putchar('\n');
	}
	else
		error_open_file(stream->content);
}
