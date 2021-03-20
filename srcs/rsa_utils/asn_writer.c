/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:15:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/20 14:40:13 by gemerald         ###   ########.fr       */
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

//void* convert_asn_to_key(void *mem, size_t size)
//{
//	uint64_t num;
//	uint8_t *byte;
//	size_t over_flow_protect;
//
//	num = 0;
//	over_flow_protect = size;
//	byte = mem;
//
//	while (--size >= 0 && size < over_flow_protect)
//	{
//		num <<= 8;
//		num = num | byte[size];
//	}
//	return &num;
//}



size_t get_sequence_size(t_asn asn[], size_t asn_size)
{
	size_t size;
	int i = -1;

	size = 2;
	while (++i < asn_size && asn[i].size)
	{
		size += asn[i].size;
		size += 2;
	}
	return (size);
}

void 	fill_der_chunk(uint8_t *mem, t_asn asn)
{
	int asn_i;
	size_t mem_i;

	mem_i = 2;
	asn_i = asn.size;
	mem[0] = 2;
	mem[1] = asn.size;
	if (asn.size == 50)
		ft_putchar('\n');
	while (--asn_i >= 0)
	{
		mem[mem_i] = asn.mem[asn_i];
		mem_i++;
	}
}

t_list *collect_mem_to_output(t_asn asn[], size_t asn_size)
{
	t_list *mem;
	size_t size;
	uint8_t *mem_ptr;
	size_t asn_i;
	size_t mem_i;

	asn_i = 0;
	size = get_sequence_size(asn, asn_size);
	mem = (t_list *)ft_safe_memalloc(sizeof(t_list), "collect_mem");
	mem->content_size = size;
	mem->content = ft_safe_memalloc(sizeof(uint8_t) * size, "collect_mem");
	mem_ptr = (uint8_t *)mem->content;
	mem_ptr[0] = 0x30;
	mem_ptr[1] = size - 2;
	mem_i = 2;
	while (mem_i < size)
	{
		fill_der_chunk(&mem_ptr[mem_i], asn[asn_i]);
		mem_i += (asn[asn_i].size + 2);
		asn_i++;
	}
	return (mem);
}

t_list *get_priv_der_form(t_rsa_key *key)
{
	t_list *der;
	t_asn asn[9];

	ft_bzero(asn, (sizeof(t_asn) * 9));
	asn[0].size = 1;
	ft_bzero(asn[0].mem, 16);
	asn[1] = convert_key_to_asn(&key->modulus, sizeof(uint64_t));
	asn[2] = convert_key_to_asn(&key->public_exponent, sizeof(uint32_t));
//	test = *(uint64_t *)convert_asn_to_key(asn[2].mem, asn[2].size);
	asn[3] = convert_key_to_asn(&key->private_exponent, sizeof(uint64_t));
	asn[4] = convert_key_to_asn(&key->prime1, sizeof(uint32_t));
	asn[5] = convert_key_to_asn(&key->prime2, sizeof(uint32_t));
	asn[6] = convert_key_to_asn(&key->exponent1, sizeof(uint32_t));
	asn[7] = convert_key_to_asn(&key->exponent2, sizeof(uint32_t));
	asn[8] = convert_key_to_asn(&key->coefficient, sizeof(uint32_t));
	der = collect_mem_to_output(asn, 9);
	return (der);
}