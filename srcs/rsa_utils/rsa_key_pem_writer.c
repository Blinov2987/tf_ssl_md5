/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_key_pem_writer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:58:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/20 18:35:42 by gemerald         ###   ########.fr       */
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

void 	rsa_pem_writer(t_rsa_key *key, t_rsa_args *args)
{
	t_list *der;
	t_list *pem;
	int fd;

	fd = 1;
	der = NULL;
	pem = NULL;
//	der = get_priv_der_form(key);
	der = get_pub_der_form(key);
	pem = base64_enc(der->content, der->content_size);
//	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", fd);
	ft_putendl_fd("-----BEGIN PUBLIC KEY-----", fd);
	rsa_key_stream_write(fd, pem);
	ft_putendl_fd("-----END PUBLIC KEY-----", fd);
//	ft_putendl_fd("-----END RSA PRIVATE KEY-----", fd);

}