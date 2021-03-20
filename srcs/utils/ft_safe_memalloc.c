/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_memalloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:41:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:41:28 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	*ft_safe_memalloc(size_t size, char *function_name)
{
	void *ptr;

	ptr = NULL;
	if (!(ptr = ft_memalloc(size)))
	{
		error_safe_memalloc(function_name);
		exit(12);
	}
	return (ptr);
}
