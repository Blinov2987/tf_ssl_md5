/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_key_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 21:03:11 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/25 22:51:12 by gemerald         ###   ########.fr       */
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

void 	get_salt_from_raw(t_rsa_output *out)
{
	out->salt_vector = ft_safe_memalloc(sizeof(t_list), "get_salt");
	out->salt_vector->content = ft_safe_memalloc(16, "get_salt");
	out->salt_vector->content_size = 16;
	ft_mem_copy(out->salt_vector->content,
			&((uint8_t *)out->raw_key->content)[41], 16);
	get_8byte_from_ascii(out->salt_vector);
}

void 	cut_proc_type_on_raw(t_rsa_output *out)
{

}

int 	raw_key_convert_to_rsa_key(t_rsa_args *args, t_rsa_output *output)
{
	if ((!args->pubin && !output->raw_key->next)
	|| output->raw_key->content_size < 42)
		return priv_key_error();
	if (!ft_memcmp("Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC,",
			output->raw_key->content, 41))
	{
		if (output->raw_key->content_size < 70)
			return priv_key_error();
		get_salt_from_raw(output);
		cut_start_end(&output->raw_key, 59, 59);
		in_base64_prism(output->raw_key->content,
				&output->raw_key->content_size);
		output->raw_key = base64_dec(output->raw_key->content,
				output->raw_key->content_size);
		if (!output->raw_key->content_size)
			return priv_key_error();
		if (!des_showing(args, output))
			return priv_key_error();
		output->key = convert_der_to_priv_key(output->der);
		int i = 0;
		i++;
	}
}