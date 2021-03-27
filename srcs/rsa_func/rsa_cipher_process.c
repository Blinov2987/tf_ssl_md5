/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_cipher_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:37:06 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:18:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void	prepare_mem(t_list *mem)
{
	uint8_t	*new_mem;
	size_t	off;

	new_mem = ft_safe_memalloc(8, "prepare_mem");
	off = 8 - mem->content_size;
	ft_mem_copy(&new_mem[off], mem->content, mem->content_size);
	mem->content_size = 8;
	free(mem->content);
	mem->content = new_mem;
}

t_list	*rsa_enc(t_list *mem, t_rsa_key *key)
{
	uint64_t	in;
	uint64_t	proc;
	t_list		*res;

	in = take_uint64_from_uint8(mem->content);
	proc = mod_power_rem(in, key->public_exponent, key->modulus);
	res = ft_safe_memalloc((sizeof(t_list)), "rsa_enc");
	res->content = ft_safe_memalloc(8, "rsa_enc");
	res->content_size = 8;
	take_byte_from_int_sha512(res->content, proc);
	return (res);
}

t_list	*rsa_dec(t_list *mem, t_rsa_key *key)
{
	uint64_t	in;
	uint64_t	proc;
	t_list		*res;

	in = take_uint64_from_uint8(mem->content);
	proc = mod_power_rem(in, key->private_exponent, key->modulus);
	res = ft_safe_memalloc((sizeof(t_list)), "rsa_enc");
	res->content = ft_safe_memalloc(8, "rsa_enc");
	res->content_size = 8;
	take_byte_from_int_sha512(res->content, proc);
	return (res);
}

int		size_error(void)
{
	ft_putendl_fd("data greater than mod len or can't be read", 2);
	return (FALSE);
}

int		rsa_process(t_rsa_args *args, t_rsa_output *out)
{
	if (args->input_files)
		out->mem = buffered_file_reader(args->input_files);
	else
		out->mem = buffered_reader(1);
	if (out->mem->content_size > 8 || !out->mem->content)
		return (size_error());
	prepare_mem(out->mem);
	if (args->decrypt)
		out->output_stream = rsa_dec(out->mem, &out->key);
	else
		out->output_stream = rsa_enc(out->mem, &out->key);
	return (TRUE);
}
