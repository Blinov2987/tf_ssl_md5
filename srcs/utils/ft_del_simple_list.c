/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_simple_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:39:27 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/22 20:39:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_list(void *mem, size_t size)
{
	if (!size)
		size++;
	if (mem)
	{
		free(mem);
		mem = NULL;
	}
}

void			ft_del_simple_list(t_list **begin)
{
	ft_lstdel(begin, &free_list);
}