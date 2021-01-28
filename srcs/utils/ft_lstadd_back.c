/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:03:29 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:41:10 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*list;

	if (!new)
		return ;
	list = *alst;
	if (!list)
	{
		*alst = new;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = new;
}
