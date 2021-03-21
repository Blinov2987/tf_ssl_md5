/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_key_pem_writer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:58:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/21 15:18:26 by gemerald         ###   ########.fr       */
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

void 	rsa_public_pem_writer(t_rsa_key *key, t_rsa_args *args)
{
	t_list *der;
	t_list *pem;
	int fd;

	fd = 1;
	der = NULL;
	pem = NULL;
	ft_putendl_fd(RSA_PUB_START, fd);
	der = get_pub_der_form(key);
	pem = base64_enc(der->content, der->content_size);
	rsa_key_stream_write(fd, pem);
	ft_putendl_fd(RSA_PUB_END, fd);
	ft_lst_free(&der);
	ft_lst_free(&pem);
}

void 	rsa_private_pem_writer(t_rsa_key *key, t_rsa_args *args)
{
	t_list *der;
	t_list *pem;
	int fd;

	fd = 1;
	der = NULL;
	pem = NULL;
	ft_putendl_fd(RSA_PRIV_START, fd);
	der = get_priv_der_form(key);
	pem = base64_enc(der->content, der->content_size);
	rsa_key_stream_write(fd, pem);
	ft_putendl_fd(RSA_PRIV_END, fd);
	ft_lst_free(&der);
	ft_lst_free(&pem);
}