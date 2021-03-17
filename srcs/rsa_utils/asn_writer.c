/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:15:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/17 22:27:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

t_asn convert_key_to_asn(void *mem, size_t size)
{
	uint64_t num;
	t_asn asn;

	ft_bzero(&asn, sizeof(asn));
	ft_bzero(asn.mem, 16);
	if (size == sizeof(uint64_t))
		num = (uint64_t)(*(uint64_t *)mem);
	else
		num = (uint64_t)(*(uint32_t *)mem);
	while (num)
	{
		asn.mem[asn.size] = num & 0xff;
		asn.size++;
		num >>= 8;
	}
	if (asn.mem[asn.size - 1] > 0x79)
		asn.size++;
	return (asn);
}

void* convert_asn_to_key(void *mem, size_t size)
{
	uint64_t num;
	uint8_t *byte;
	size_t over_flow_protect;

	num = 0;
	over_flow_protect = size;
	byte = mem;

	while (--size >= 0 && size < over_flow_protect)
	{
		num <<= 8;
		num = num | byte[size];
	}
	return &num;
}

t_list *get_der_form(t_rsa_key key)
{
	t_list *der;
	t_asn asn[9];

	uint64_t test;
	ft_bzero(asn, (sizeof(t_asn) * 9));
	asn[1] = convert_key_to_asn(&key.modulus, sizeof(uint64_t));
	asn[2] = convert_key_to_asn(&key.public_exponent, sizeof(uint32_t));
	test = *(uint64_t *)convert_asn_to_key(asn[2].mem, asn[2].size);
	asn[3] = convert_key_to_asn(&key.private_exponent, sizeof(uint64_t));
	asn[4] = convert_key_to_asn(&key.prime1, sizeof(uint32_t));
	asn[5] = convert_key_to_asn(&key.prime2, sizeof(uint32_t));
	asn[6] = convert_key_to_asn(&key.exponent1, sizeof(uint32_t));
	asn[7] = convert_key_to_asn(&key.exponent2, sizeof(uint32_t));
	asn[8] = convert_key_to_asn(&key.coefficient, sizeof(uint32_t));
	return der;
}
