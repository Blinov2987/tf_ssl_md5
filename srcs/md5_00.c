/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:26:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:44:16 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_hex(uint8_t *mem, size_t size, int fd)
{
	size_t	i;
	char	*byte;

	i = 0;
	byte = NULL;
	while (i < size)
	{
		byte = ft_itoa_base(mem[i], 16);
		if (ft_strlen(byte) == 1)
			ft_putchar_fd('0', fd);
		ft_putstr_fd(byte, fd);
		free(byte);
		i++;
	}
}
