/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:24:37 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:20:55 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		stdin_process(t_output *output,
			t_list *(*hash_func)(void *, size_t))
{
	ft_lstadd_back(&output->stdin_stream, buffered_reader(0));
	ft_lstadd_back(&output->stdin_hash,
			hash_func(output->stdin_stream->content,
					output->stdin_stream->content_size));
}

void		string_process(t_args *args, t_output *output,
			t_list *(*hash_func)(void *, size_t))
{
	t_list *tmp;

	output->string_stream = args->strings;
	args->strings = NULL;
	tmp = output->string_stream;
	while (tmp)
	{
		ft_lstadd_back(&output->string_hash,
				hash_func(tmp->content, tmp->content_size));
		tmp = tmp->next;
	}
}

void		file_process(t_args *args, t_output *output,
			t_list *(*hash_func)(void *, size_t))
{
	t_list *streams;

	output->filenames = args->filenames;
	ft_lstadd_back(&output->file_stream, buffered_file_reader(args));
	args->filenames = NULL;
	streams = output->file_stream;
	while (streams)
	{
		if (streams->content)
			ft_lstadd_back(&output->file_hash,
					hash_func(streams->content, streams->content_size));
		else
			ft_lstadd_back(&output->file_hash, ft_lstnew(NULL, 0));
		streams = streams->next;
	}
}

t_output	process(t_args *args, t_list *(*hash_func)(void *, size_t))
{
	t_output output;

	ft_bzero(&output, sizeof(t_output));
	if (args->flag_p || (!args->flag_p && !args->flag_s &&
							!args->flag_q && !args->flag_r && !args->filenames))
		stdin_process(&output, hash_func);
	if (args->strings)
		string_process(args, &output, hash_func);
	if (args->filenames)
		file_process(args, &output, hash_func);
	return (output);
}

void		entrance_to_hash(t_args *args)
{
	t_output	output;
	t_list		*(*hash_func)(void *, size_t);

	if (args->is_md5)
		hash_func = &md5;
	if (args->is_sha256)
		hash_func = &sha256;
	if (args->is_sha512)
		hash_func = &sha512;
	output = process(args, hash_func);
	print_output(args, &output);
	free_output(&output);
}
