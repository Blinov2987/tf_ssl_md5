/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:04:52 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:05:49 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_strings(t_args *args, t_output *output)
{
	t_list *stream;
	t_list *hash;

	stream = output->string_stream;
	hash = output->string_hash;
	while (stream)
	{
		print_algo(args);
		ft_putstr("(\"");
		ft_print_by_size(stream->content, stream->content_size, 1);
		ft_putstr("\") = ");
		print_hex(hash->content, hash->content_size, 1);
		ft_putchar('\n');
		stream = stream->next;
		hash = hash->next;
	}
}

void	print_files(t_args *args, t_output *output)
{
	t_list *filenames;
	t_list *hash;

	filenames = output->filenames;
	hash = output->file_hash;
	while (filenames)
	{
		if (hash && hash->content)
		{
			print_algo(args);
			ft_putstr("(");
			ft_print_by_size(filenames->content, filenames->content_size, 1);
			ft_putstr(") = ");
			print_hex(hash->content, hash->content_size, 1);
			ft_putchar('\n');
		}
		else
			error_open_file(filenames->content);
		filenames = filenames->next;
		if (hash)
			hash = hash->next;
	}
}

void	print_strings_and_files(t_args *args, t_output *output)
{
	print_strings(args, output);
	print_files(args, output);
}
