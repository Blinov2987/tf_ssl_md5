/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:09:11 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:05:22 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	revers_print_strings(t_output *output)
{
	t_list *stream;
	t_list *hash;

	stream = output->string_stream;
	hash = output->string_hash;
	while (stream)
	{
		print_hex(hash->content, hash->content_size, 1);
		ft_putstr(" \"");
		ft_print_by_size(stream->content, stream->content_size, 1);
		ft_putstr("\"");
		ft_putchar('\n');
		stream = stream->next;
		hash = hash->next;
	}
}

void	revers_print_files(t_output *output)
{
	t_list *filenames;
	t_list *hash;

	filenames = output->filenames;
	hash = output->file_hash;
	while (filenames)
	{
		if (hash->content)
		{
			print_hex(hash->content, hash->content_size, 1);
			ft_putstr(" ");
			ft_print_by_size(filenames->content, filenames->content_size, 1);
			ft_putchar('\n');
		}
		else
			error_open_file(filenames->content);
		filenames = filenames->next;
		hash = hash->next;
	}
}

void	revers_print_string_and_files(t_output *output)
{
	revers_print_strings(output);
	revers_print_files(output);
}

void	silent_print(t_output *output)
{
	t_list *tmp;
	t_list *stream;

	if (output->stdin_hash)
		print_hex(output->stdin_hash->content,
				output->stdin_hash->content_size, 1);
	ft_putchar('\n');
	tmp = output->string_hash;
	while (tmp)
	{
		print_hex(tmp->content, tmp->content_size, 1);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	tmp = output->file_hash;
	stream = output->filenames;
	while (tmp)
	{
		if (tmp->content)
		{
			print_hex(tmp->content, tmp->content_size, 1);
			ft_putchar('\n');
		}
		else
			error_open_file(stream->content);
		tmp = tmp->next;
		stream = stream->next;
	}
}

void	print_output(t_args *args, t_output *output)
{
	if (args->flag_q)
		silent_print(output);
	else
	{
		print_stdin(args, output);
		if (args->flag_r)
			revers_print_string_and_files(output);
		else
			print_strings_and_files(args, output);
	}
}
