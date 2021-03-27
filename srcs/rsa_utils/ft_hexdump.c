/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:51:28 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:23:46 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "hexdump.h"
#include "rsa.h"

void	print_one_byte(uint8_t byte, int fd)
{
	ft_putchar_fd(g_sym[byte >> 4], fd);
	ft_putchar_fd(g_sym[byte & 0xf], fd);
}

void	print_hex_row(uint8_t *mem, size_t bound, int fd)
{
	size_t i;

	i = 0;
	while (i < 16 && i < bound)
	{
		if (mem[i] >= 0x20 && mem[i] <= 0x7e)
			ft_putchar_fd(mem[i], fd);
		else
			ft_putchar_fd('.', fd);
		i++;
	}
}

void	print_stage(uint32_t stage, int fd)
{
	print_one_byte((stage & 0xff00) >> 8, fd);
	print_one_byte(stage & 0xff, fd);
	ft_putstr_fd(" - ", fd);
}

void	print_border(size_t bound, int fd)
{
	int i;

	if (bound >= 16)
		ft_putstr_fd("   ", fd);
	else
	{
		i = ((16 - bound) * 3) + 3;
		while (--i >= 0)
			ft_putchar_fd(' ', fd);
	}
}

void	print_hex_dump(t_list *mem, int fd)
{
	uint32_t	stage;
	size_t		i;
	uint8_t		*hex;
	long		bound;

	stage = 0;
	i = 0;
	hex = (uint8_t *)mem->content;
	while (1)
	{
		bound = (long)mem->content_size - i;
		if (bound <= 0)
			break ;
		print_stage(stage, fd);
		print_byte_row(&hex[i], bound, fd);
		print_border(bound, fd);
		print_hex_row(&hex[i], bound, fd);
		ft_putchar_fd('\n', fd);
		stage += 0x10;
		i += 16;
	}
}
