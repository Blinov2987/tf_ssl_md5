/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:13:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:27:29 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	free_list(void *mem, size_t size)
{
	if (!size)
		size++;
	if (mem)
	{
		free(mem);
		mem = NULL;
	}
}

void	free_args(t_args **args)
{
	if (*args)
	{
		ft_lstdel(&(*args)->bad_argums, &free_list);
		ft_lstdel(&(*args)->filenames, &free_list);
		ft_lstdel(&(*args)->strings, &free_list);
		(*args)->bad_argums = NULL;
		(*args)->filenames = NULL;
		(*args)->strings = NULL;
		free(*args);
		(*args) = NULL;
	}
}

void	free_des_args(t_des_args **args)
{
	if (*args)
	{
		ft_lstdel(&(*args)->bad_argums, &free_list);
		ft_lstdel(&(*args)->input_files, &free_list);
		ft_lstdel(&(*args)->output_files, &free_list);
		ft_lstdel(&(*args)->key_in_hex, &free_list);
		ft_lstdel(&(*args)->pass_in_ascii, &free_list);
		ft_lstdel(&(*args)->vector, &free_list);
		ft_lstdel(&(*args)->salt, &free_list);
		(*args)->bad_argums= NULL;
		(*args)->input_files = NULL;
		(*args)->output_files = NULL;
		(*args)->key_in_hex = NULL;
		(*args)->pass_in_ascii = NULL;
		(*args)->vector = NULL;
		(*args)->salt = NULL;
		free(*args);
		(*args) = NULL;
	}
}

void 	free_crypt_output(t_crypt_output **output)
{
	t_list *pointers_to_free;

	pointers_to_free = (*output)->pointers_to_free;
	while (pointers_to_free)
	{
		ft_lstdel(((t_list *)&pointers_to_free)->content, &free_list);
		pointers_to_free = pointers_to_free->next;
	}
	ft_lstdel(&(*output)->mem, &free_list);
	ft_lstdel(&(*output)->output_stream, &free_list);
}

void	free_output(t_output *output)
{
	ft_lstdel(&output->stdin_stream, &free_list);
	ft_lstdel(&output->stdin_hash, &free_list);
	ft_lstdel(&output->string_stream, &free_list);
	ft_lstdel(&output->string_hash, &free_list);
	ft_lstdel(&output->filenames, &free_list);
	ft_lstdel(&output->file_stream, &free_list);
	ft_lstdel(&output->file_hash, &free_list);
}
