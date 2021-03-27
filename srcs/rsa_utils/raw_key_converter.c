/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_key_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 21:03:11 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:30:18 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "base64.h"

int		priv_key_error(void)
{
	ft_putendl_fd("unable to load Key", 2);
	return (FALSE);
}

void	get_salt_from_raw(t_rsa_output *out)
{
	out->salt_vector = ft_safe_memalloc(sizeof(t_list), "get_salt");
	out->salt_vector->content = ft_safe_memalloc(16, "get_salt");
	out->salt_vector->content_size = 16;
	ft_mem_copy(out->salt_vector->content,
			&((uint8_t *)out->raw_key->content)[41], 16);
	get_8byte_from_ascii(out->salt_vector);
}

int		verify_key_filling(t_rsa_output *out)
{
	if (out->is_private_key_found)
	{
		return (out->key.modulus && out->key.prime1 && out->key.prime2
		&& out->key.public_exponent && out->key.private_exponent
		&& out->key.exponent1 && out->key.exponent2 && out->key.coefficient);
	}
	else
		return (out->key.modulus && out->key.public_exponent);
}

void	decode_base64_key(t_rsa_output *output)
{
	t_list *raw;

	in_base64_prism(output->raw_key->content,
			&output->raw_key->content_size);
	raw = base64_dec(output->raw_key->content,
			output->raw_key->content_size);
	ft_del_simple_list(&output->raw_key);
	output->raw_key = raw;
}

int		raw_key_convert_to_rsa_key(t_rsa_args *args, t_rsa_output *output)
{
	if ((!args->pubin && !output->is_private_key_found)
	|| output->raw_key->content_size < 42)
		return (priv_key_error());
	if (!ft_memcmp(ENCR_KEY, output->raw_key->content, 41))
	{
		if (output->raw_key->content_size < 70)
			return (priv_key_error());
		get_salt_from_raw(output);
		cut_start_end(&output->raw_key, 59, 59);
	}
	decode_base64_key(output);
	if (!output->raw_key->content_size)
		return (priv_key_error());
	if (output->salt_vector && !des_showing(args, output))
		return (priv_key_error());
	else
		output->der = ft_lstnew(output->raw_key->content,
				output->raw_key->content_size);
	if (output->is_private_key_found)
		output->key = convert_der_to_priv_key(output->der);
	else
		output->key = convert_der_to_pub_key(output->der);
	return (verify_key_filling(output));
}
