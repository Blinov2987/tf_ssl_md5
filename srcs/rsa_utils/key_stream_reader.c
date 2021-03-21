/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_stream_reader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:41:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/21 16:41:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

t_list  *read_der_form(int fd)
{
	return (buffered_reader(fd));
}

t_list *read_pem_form(int fd)
{
	t_list *pem;

	pem = buffered_reader(fd);
}