/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:51:28 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/22 21:28:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "hexdump.h"

void 	print_one_byte(uint8_t byte)
{
	ft_putchar(g_sym[byte >> 4]);
	ft_putchar(g_sym[byte & 0xf]);
}

void 	print_byte_row(uint8_t *mem, size_t bound)
{
	size_t i;

	i = 0;
	while (i < 16 && i < bound)
	{
		print_one_byte(mem[i]);
		ft_putchar(' ');
		i++;
	}
}

void	print_hex_row(uint8_t *mem, size_t bound)
{
	size_t i;

	i = 0;
	while (i < 16 && i < bound)
	{
		if (mem[i] >= 0x20 && mem[i] <= 0x7e)
			ft_putchar(mem[i]);
		else
			ft_putchar('.');
		i++;
	}
}

void 	print_stage(uint32_t stage)
{
	print_one_byte((stage & 0xff00) >> 8);
	print_one_byte(stage & 0xff);
	ft_putstr(" - ");
}

void 	print_border(size_t bound)
{
	int i;

	if (bound >= 16)
		ft_putstr("   ");
	else
	{
		i = ((16 - bound) * 3) + 3;
		while (--i >= 0)
			ft_putchar(' ');
	}
}

void 	print_hex_dump(t_list *mem)
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
		print_stage(stage);
		print_byte_row(&hex[i], bound);
		print_border(bound);
		print_hex_row(&hex[i], bound);
		ft_putchar('\n');
		stage += 0x10;
		i += 16;
	}
}
