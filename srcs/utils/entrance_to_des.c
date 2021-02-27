/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_des.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:14:18 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 09:14:33 by gemerald         ###   ########.fr       */
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

void 		add_salt_to_stream(t_des_args *args, t_crypt_output *output)
{
	void	*mem;
	size_t	new_size;

	new_size = 8 + 8 + output->output_stream->content_size;
	mem = ft_safe_memalloc(new_size, "add_salt_to_stream");
	ft_mem_copy(mem, "Salted__", 8);
	ft_mem_copy(&((uint8_t *)mem)[8], args->salt->content, 8);
	ft_mem_copy(&((uint8_t *)mem)[16], output->output_stream->content,
			output->output_stream->content_size);
	free(output->output_stream->content);
	output->output_stream->content = mem;
	output->output_stream->content_size = new_size;
}

void		get_salt_from_content(t_des_args *args, t_crypt_output *output)
{
	void	*mem;
	size_t	new_size;

	new_size = output->mem->content_size - 16;
	mem = ft_safe_memalloc(new_size, "get_salt_from_content");
	ft_mem_copy(args->salt->content,
			&((uint8_t *)output->mem->content)[8], 8);
	ft_mem_copy(mem, &((uint8_t *)output->mem->content)[16], new_size);
	free(output->mem->content);
	output->mem->content = mem;
	output->mem->content_size = new_size;
}

static void entrance_continue(t_des_args *args, t_crypt_output *output)
{
	if (!args->flag_k && args->flag_d && !ft_strncmp("Salted__",
			output->mem->content, 8) && output->mem->content_size > 16)
		get_salt_from_content(args, output);
	else if ((!args->flag_k && args->flag_d) && (ft_strncmp("Salted__",
			output->mem->content, 8) || output->mem->content_size > 16))
	{
		error_bad_salt();
		free_crypt_output(output);
		return ;
	}
	if (args->pass_in_ascii)
		pbkfd(args, &args->key_vector);
	output->output_stream = general_cipher(output->mem->content,
			output->mem->content_size, args);
	if (!args->flag_k && !args->flag_d)
		add_salt_to_stream(args, output);
	if (!args->flag_d && args->flag_a)
		get_based_output(output);
	print_output_des(args, output);
	free_crypt_output(output);
}

void		entrance_to_des(t_des_args *args)
{
	t_crypt_output 	output;

	ft_bzero(&output, sizeof(t_crypt_output));
	if ((args->algo == CBC || args->algo == PCBC
		|| args->algo == CFB || args->algo == OFB) && !args->key_vector.vector)
	{
		error_bad_vector();
		return ;
	}
	get_info_stream(args, &output);
	if (output.mem->content_size == 0)
	{
		error_bad_file_descriptor(args->input_files->content);
		free_crypt_output(&output);
		return ;
	}
	entrance_continue(args, &output);
}
