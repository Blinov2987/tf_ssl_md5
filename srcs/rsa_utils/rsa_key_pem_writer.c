/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_key_pem_writer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:58:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/26 18:45:57 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "base64.h"

void	rsa_key_stream_write(int fd, t_list *key_der)
{
	out_base64_prism(key_der->content, &key_der->content_size);
	print_base64_stdout(fd, key_der->content, key_der->content_size);
}

int		get_out_fd(t_rsa_args *args)
{
	int fd;

	if (!args->output_files)
		return (1);
	if ((fd = open(args->output_files->content, O_WRONLY | O_CREAT, 0666)) < 2)
	{
		error_bad_file_descriptor(args->output_files->content);
		ft_putendl_fd("Redirect out to stdout", 2);
		return (1);
	}
	return (fd);
}

void	rsa_pem_writer(t_rsa_args *args, t_rsa_output *out, int fd)
{
	t_list *pem;

	pem = out->pem;
	ft_putstr_fd(pem->content, fd);
	pem = pem->next;
	if (args->des)
	{
		ft_putendl_fd(pem->content, fd);
		pem = pem->next;
		ft_putstr_fd(pem->content, fd);
		pem = pem->next;
		print_hex(pem->content, 8, fd);
		ft_putstr_fd("\n\n", fd);
		pem = pem->next;
	}
	rsa_key_stream_write(fd, pem);
	pem = pem->next;
	ft_putstr_fd(pem->content, fd);
}
