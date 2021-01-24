/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:09:11 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/24 19:11:49 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void ft_print_by_size(char *str, size_t size, int fd)
{
	write(fd, str, size);
}

void print_stdin(t_args *args, t_output *output)
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

void print_algo(t_args *args)
{
	char *algo;

	if (args->is_md5)
		algo = "MD5 ";
	if (args->is_sha256)
		algo = "SHA256 ";
	ft_putstr(algo);
}

void print_strings(t_args *args, t_output *output)
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

void print_files(t_args *args, t_output *output)
{
	t_list *stream;
	t_list *hash;

	stream = output->filenames;
	hash = output->file_hash;
	while (stream)
	{
		if (hash && hash->content)
		{
			print_algo(args);
			ft_putstr("(");
			ft_print_by_size(stream->content, stream->content_size, 1);
			ft_putstr(") = ");
			print_hex(hash->content, hash->content_size, 1);
			ft_putchar('\n');
		}
		else
			error_open_file(stream->content, stream->content_size);
		stream = stream->next;
		if (hash)
			hash = hash->next;
	}
}

void print_strings_and_files(t_args *args, t_output *output)
{
	print_strings(args, output);
	print_files(args, output);
}

void revers_print_strings(t_args *args, t_output *output)
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

void revers_print_files(t_args *args, t_output *output)
{
	t_list *stream;
	t_list *hash;

	stream = output->filenames;
	hash = output->file_hash;
	while (stream)
	{
		if (hash->content)
		{
			print_hex(hash->content, hash->content_size, 1);
			ft_putstr(" ");
			ft_print_by_size(stream->content, stream->content_size, 1);
			ft_putchar('\n');
		}
		else
			error_open_file(stream->content, stream->content_size);
		stream = stream->next;
		hash = hash->next;
	}
}

void revers_print_string_and_files(t_args *args, t_output *output)
{
	revers_print_strings(args, output);
	revers_print_files(args, output);
}

void silent_print(t_output *output)
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
			error_open_file(stream->content, stream->content_size);
		tmp = tmp->next;
		stream = stream->next;
	}
}

void print_output(t_args *args, t_output *output)
{
	if (args->flag_q)
		silent_print(output);
	else
	{
		print_stdin(args, output);
		if (args->flag_r)
			revers_print_string_and_files(args, output);
		else
			print_strings_and_files(args, output);
	}
}