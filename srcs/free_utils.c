/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:13:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/21 21:28:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "args.h"
#include "handler_info.h"

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

void	free_file(t_file **file)
{
	if (*file)
	{
		free(*file);
		(*file) = NULL;
	}
}
