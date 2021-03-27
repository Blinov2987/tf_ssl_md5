/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa_utl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:59:53 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 10:19:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		rsa_utl_printer(t_rsa_args *args, t_rsa_output *out)
{
	int fd;

	fd = get_out_fd(args);
	if (args->hexdump)
		print_hex_dump(out->output_stream, fd);
	else
		write(fd, out->output_stream->content,
				out->output_stream->content_size);
	if (fd > 1)
		close(fd);
}

void		entrance_to_rsa_utl(t_rsa_args *args)
{
	t_rsa_output	output;

	ft_bzero(&output, sizeof(t_rsa_output));
	if (!get_key_from_user(args, &output))
	{
		free_rsa_out(&output);
		return ;
	}
	if (args->decrypt && !output.is_private_key_found)
	{
		ft_putendl_fd("A private key is needed for this operation", 2);
		free_rsa_out(&output);
		return ;
	}
	if (!rsa_process(args, &output))
		return ;
	rsa_utl_printer(args, &output);
	free_rsa_out(&output);
}
