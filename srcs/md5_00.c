/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:26:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 12:25:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void print_hex(uint8_t *mem, size_t size);

void md5_process(t_args *args)
{
	t_list *out_stream;
	t_list *stdin_stream;
	t_list *file_stream;



	stdin_stream = NULL;
	file_stream = NULL;

//	if (args->flag_p)
//		ft_lstadd_back(&stdin_stream, buffered_reader(0));
//	if (args->filenames)
//		ft_lstadd_back(&file_stream, buffered_file_reader(args));
	out_stream = md5(args->strings->content, args->strings->content_size);
	print_hex(out_stream->content, out_stream->content_size);

}

void print_hex(uint8_t *mem, size_t size)
{
	size_t i;
	char *byte;

	i = 0;
	byte = NULL;
	while (i < size)
	{
		byte = ft_itoa_base(mem[i], 16);
		if (ft_strlen(byte) == 1)
			ft_putchar('0');
		ft_putstr(byte);
		i++;
	}
	ft_putchar('\n');
	ft_putendl("acbd18db4cc2f85cedef654fccc4a4d8");
}

void test_func(void)
{
	//	out_stream = file_stream;
//	while (out_stream)
//	{
//		write(2, out_stream->content, out_stream->content_size);
//		out_stream = out_stream->next;
//	}

//	stdin_stream = buffered_reader(0);
//	write(2, stdin_stream->content, stdin_stream->content_size);
}