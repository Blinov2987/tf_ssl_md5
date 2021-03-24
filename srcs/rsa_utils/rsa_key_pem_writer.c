/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_key_pem_writer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:58:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 20:05:29 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "base64.h"

void 	rsa_key_stream_write(int fd, t_list *key_der)
{
	out_base64_prism(key_der->content, &key_der->content_size);
	print_base64_stdout(fd, key_der->content, key_der->content_size);
}

//void 	rsa_public_pem_writer(t_rsa_args *args, t_rsa_output *out)
//{
//	t_list *der;
//	t_list *pem;
//	int fd;
//
//	fd = 1;
//	der = NULL;
//	pem = NULL;
//	ft_putendl_fd(RSA_PUB_START, fd);
//	der = get_pub_der_form(key);
//	pem = base64_enc(der->content, der->content_size);
//	rsa_key_stream_write(fd, pem);
//	ft_putendl_fd(RSA_PUB_END, fd);
//	ft_del_simple_list(&der);
//	ft_del_simple_list(&pem);
//}

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

void 	rsa_pem_writer(t_rsa_args *args, t_rsa_output *out, int fd)
{
	t_list *pem;

	pem = out->pem;
	ft_putendl_fd(pem->content, fd);
	pem = pem->next;
	if (args->des)
	{
		ft_putendl_fd(pem->content, fd);
		pem = pem->next;
		ft_putstr_fd(pem->content, fd);
		pem = pem->next;
		print_hex(pem->content, 8, fd);
		ft_putendl_fd("\n", fd);
		pem = pem->next;
	}
	rsa_key_stream_write(fd, pem);
	pem = pem->next;
	ft_putendl_fd(pem->content, fd);
}