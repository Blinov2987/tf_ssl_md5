/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pub_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:36:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/20 18:38:38 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

t_list *get_pub_der_form(t_rsa_key *key)
{
	t_list *der;
	t_asn asn[2];
	t_list *final_der;

	ft_bzero(asn, (sizeof(t_asn) * 2));
	asn[0] = convert_key_to_asn(&key->modulus, sizeof(uint64_t));
	asn[1] = convert_key_to_asn(&key->public_exponent, sizeof(uint32_t));
	der = collect_mem_to_output(asn, 2);
	final_der = (t_list *)ft_safe_memalloc(sizeof(t_list), "pub_der");
	final_der->content_size = 20 + der->content_size;
	final_der->content = ft_safe_memalloc(final_der->content_size, "pub_der");
	ft_mem_copy(final_der->content, g_der_bit_string, 20);
	ft_mem_copy(&((uint8_t *)final_der->content)[20], der->content, der->content_size);
	free(der->content);
	free(der);
	return (final_der);
}