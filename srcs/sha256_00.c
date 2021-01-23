/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:27:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 15:36:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void sha256_process(t_args *args)
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
	out_stream = sha256(args->strings->content, args->strings->content_size);
	print_hex(out_stream->content, out_stream->content_size);
	ft_putendl("23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa");
	free(out_stream->content);
	free(out_stream);
}