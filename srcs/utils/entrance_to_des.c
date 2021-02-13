/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_des.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:14:18 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 20:37:47 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

static void 	get_info_stream(t_des_args *args, t_crypt_output *output)
{
	t_list	*base64_result;

	if (args->input_files)
		ft_lstadd_back(&output->mem,
				buffered_file_reader(args->input_files));
	else
		ft_lstadd_back(&output->mem,
				buffered_reader(0));
	if (args->flag_d && args->flag_a)
	{
		in_base64_prism(output->mem->content,
				&output->mem->content_size);
		base64_result = base64_dec(output->mem->content,
				output->mem->content_size);
		ft_lstdel(&output->mem, &free_list);
		output->mem = base64_result;
	}
}

static void 	get_based_output(t_crypt_output *output)
{
	t_list	*base64_result;

	base64_result = base64_enc(output->output_stream->content,
			output->output_stream->content_size);
	ft_lstdel(&output->output_stream, &free_list);
	output->output_stream = base64_result;
	out_base64_prism(output->output_stream->content,
			&output->output_stream->content_size);
}

void		entrance_to_des(t_des_args *args)
{
	t_crypt_output 	output;
	t_list		*(*cipher_func)(void *, size_t, t_key_vector *);

	ft_bzero(&output, sizeof(t_crypt_output));
	if ((args->algo == CBC || args->algo == PCBC
		|| args->algo == CFB || args->algo == OFB) && !args->key_vector.vector)
	{
		error_bad_vector();
		return ;
	}

}
