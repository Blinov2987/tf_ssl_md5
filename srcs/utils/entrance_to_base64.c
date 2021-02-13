/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_base64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 20:20:01 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/31 16:03:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"


static void 		get_info_stream(t_base64_args *args, t_output *output)
{
	if (!args->input_files)
		ft_lstadd_back(&output->string_stream, buffered_reader(0));
	else
		ft_lstadd_back(&output->string_stream,
				buffered_file_reader(args->input_files));
	if (args->flag_d)
		in_base64_prism(output->string_stream->content,
				&output->string_stream->content_size);

}

void				entrance_to_base64(t_base64_args *args)
{
	t_output	output;
	t_list		*(*cipher_func)(void *, size_t);

	if (args->flag_e || (!args->flag_e && !args->flag_d))
		cipher_func = &base64_enc;
	if (args->flag_d)
		cipher_func = &base64_dec;
	ft_bzero(&output, sizeof(t_output));
	get_info_stream(args, &output);
	output.string_hash = cipher_func(output.string_stream->content,
			output.string_stream->content_size);
	if (args->flag_e || (!args->flag_e && !args->flag_d))
		out_base64_prism(output.string_hash->content,
				&output.string_hash->content_size);
	print_output_cipher(args, &output);
	free_output(&output);
}
