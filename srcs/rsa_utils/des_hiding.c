/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_hiding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:18:51 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/26 21:59:50 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void 	rsa_private_pem_des_writer(t_rsa_key *key, t_rsa_args *args)
{
	t_list *der;
	t_list *pem;
	int fd;

	fd = 1;
	der = NULL;
	pem = NULL;
	der = get_priv_der_form(key);
//	der = des_hiding(der);
	ft_putendl_fd(RSA_PRIV_START, fd);
	ft_putendl_fd("Proc-Type: 4,ENCRYPTED", fd);
	ft_putstr_fd("DEK-Info: DES-CBC,", fd);
	print_hex(der->next->content, 8, fd);
	ft_putendl_fd("\n", fd);
	pem = base64_enc(der->content, der->content_size);
	rsa_key_stream_write(fd, pem);
	ft_putendl_fd(RSA_PRIV_END, fd);
	der->content_size += 1;
	print_hex_dump(der);
	ft_putchar('\n');
	ft_del_simple_list(&der);
	ft_del_simple_list(&pem);
}

int des_showing(t_rsa_args *args, t_rsa_output *out)
{
	t_des_args des_args;

	ft_bzero(&des_args, sizeof(t_des_args));
	des_args.type = DES_COMMAND;
	des_args.algo = CBC;
	des_args.salt = out->salt_vector;
	des_args.flag_d = 1;
	if (args->pass_in)
		des_args.pass_in_ascii = buffered_file_reader(args->pass_in);
	else
		des_args.pass_in_ascii = get_pass_stdin();
	if (!des_args.pass_in_ascii || !des_args.pass_in_ascii->content)
		return (FALSE);
	des_args.key_vector = init_key_vector(&des_args);
	pbkfd(&des_args, &des_args.key_vector);
	des_args.key_vector.vector = take_uint64_from_uint8(des_args.salt->content);
	out->der = general_cipher(out->raw_key->content, out->raw_key->content_size, &des_args);
	free(des_args.key_vector.keys);
	ft_del_simple_list(&des_args.pass_in_ascii);
	return (TRUE);
}

int des_hiding(t_rsa_args *args, t_rsa_output *out)
{
	t_des_args des_args;
	t_list *ciphered;

	ft_bzero(&des_args, sizeof(t_des_args));
	des_args.type = DES_COMMAND;
	des_args.algo = CBC;
	des_args.salt = get_random_bytes();
	if (args->pass_out)
		des_args.pass_in_ascii = buffered_file_reader(args->pass_out);
	else
		des_args.pass_in_ascii = get_pass_stdin();
	if (!des_args.pass_in_ascii || !des_args.pass_in_ascii->content)
		exit(11);
	des_args.key_vector = init_key_vector(&des_args);
	pbkfd(&des_args, &des_args.key_vector);
	des_args.key_vector.vector = take_uint64_from_uint8(des_args.salt->content);
	ciphered = general_cipher(out->der->content, out->der->content_size, &des_args);
	ft_lstadd_back(&ciphered, des_args.salt);
	free(des_args.key_vector.keys);
	ft_del_simple_list(&out->der);
	out->der = ciphered;
	ft_del_simple_list(&des_args.pass_in_ascii);
	return (TRUE);
}