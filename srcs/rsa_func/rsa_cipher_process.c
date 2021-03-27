/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_cipher_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:37:06 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 08:51:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void	prepare_mem(t_list *mem)
{
	uint8_t *new_mem;

	new_mem = ft_safe_memalloc(8, "prepare_mem");
	ft_mem_copy(new_mem, mem->content, mem->content_size);
	mem->content_size = 8;
	free(mem->content);
	mem->content = new_mem;
}

t_list	*rsa_enc(t_list *mem, t_rsa_key *key)
{
	uint64_t in;
	uint64_t proc;
	t_list	*res;

	in = take_uint64_from_uint8(mem->content);
	proc = get_pow_remainder(in, key->public_exponent, key->modulus);
	res = ft_safe_memalloc((sizeof(t_list)), "rsa_enc");
	res->content = ft_safe_memalloc(8, "rsa_enc");
	take_byte_from_int_sha512(res->content, proc);
	return (res);
}

t_list	*rsa_dec(t_list *mem, t_rsa_key *key)
{
	uint64_t in;
	uint64_t proc;
	t_list	*res;

	in = take_uint64_from_uint8(mem->content);
	proc = get_pow_remainder(in, key->private_exponent, key->modulus);
	res = ft_safe_memalloc((sizeof(t_list)), "rsa_enc");
	res->content = ft_safe_memalloc(8, "rsa_enc");
	take_byte_from_int_sha512(res->content, proc);
	return (res);
}

void	rsa_process(t_rsa_args *args, t_rsa_output *out)
{

}
