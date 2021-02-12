/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:12:08 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/12 19:18:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_list	*get_random_bytes(void)
{
	int			i;
	t_list		*rnd;
	int			fd;
	uint8_t 	byte;

	i = -1;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 3)
		return (NULL);
	rnd = ft_safe_memalloc(sizeof(t_list), "get_random_bytes");
	rnd->content = ft_safe_memalloc(8, "get_random_bytes");
	rnd->content_size = 8;
	while (++i < 8)
	{
		read(fd, &byte, 1);
		((uint8_t *)rnd->content)[i] = byte;
	}
	close(fd);
	return (rnd);
}