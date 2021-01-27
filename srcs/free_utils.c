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
		free(*args);
		(*args) = NULL;
	}
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
