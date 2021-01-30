/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_base64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:20:01 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/30 20:20:01 by gemerald         ###   ########.fr       */
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

t_output	process_base64(t_base64_args *args, t_list *(*hash_func)(void *, size_t))
{
	t_output output;

	ft_bzero(&output, sizeof(t_output));
	if (args->flag_p || (!args->flag_p && !args->flag_s &&
						 !args->flag_q && !args->flag_r && !args->filenames))
		stdin_process(&output, hash_func);
	if (args->filenames)
		file_process(args, &output, hash_func);
	return (output);
}

void		entrance_to_base64(t_base64_args *args)
{
	t_output	output;
	t_list		*(*hash_func)(void *, size_t);

	if (args->flag_e)
		hash_func = &base64_enc;
	if (args->flag_d)
		hash_func = &base64_dec;
	output = process_base64(args, hash_func);
//	print_output(args, &output);
	free_output(&output);
}
