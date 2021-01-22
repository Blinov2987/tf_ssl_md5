/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:26:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/22 20:11:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void md5_process(t_args *args)
{
	t_list *out_stream;
	t_mem_zone mem_zone;

	mem_zone = buffered_reader(0);
	write(2, mem_zone.mem, mem_zone.size);


//	if (args->flag_p)
//		ft_lstadd_back(&out_stream, take_stdin(args));
//	if (args->strings)
//		ft_lstadd_back(&out_stream, take_strings(args));
//	if (args->filenames)
//		ft_lstadd_back(&out_stream, take_files(args));
}