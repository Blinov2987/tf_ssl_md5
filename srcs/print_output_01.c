/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:03:41 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:04:01 by gemerald         ###   ########.fr       */
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
		ft_print_by_size(output->stdin_hash->content,
				output->stdin_hash->content_size, 1);
		ft_putchar('\n');
	}
}

void	print_algo(t_args *args)
{
	char *algo;

	if (args->is_md5)
		algo = "MD5 ";
	if (args->is_sha256)
		algo = "SHA256 ";
	if (args->is_sha512)
		algo = "SHA512 ";
	ft_putstr(algo);
}
