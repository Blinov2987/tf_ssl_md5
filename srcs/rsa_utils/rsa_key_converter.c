/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_key_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:55:35 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 17:31:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

uint64_t	get_field(uint8_t *mem, size_t size)
{
	uint64_t	result;
	uint8_t		part[16];
	size_t		border;
	size_t		i;
	size_t		j;

	result = 0;
	ft_bzero(part, 16);
	border = mem[1];
	if (mem[0] != 2 || border > 16)
		return (0);
	i = 2;
	j = border;
	while (i < (2 + border) && i < size)
	{
		part[--j] = mem[i];
		i++;
	}
	result = *(uint64_t *)part;
	return (result);
}

void		fill_rsa_priv_key(uint64_t nums[], t_rsa_key *key)
{
	key->version = nums[0];
	key->modulus = nums[1];
	key->public_exponent = nums[2];
	key->private_exponent = nums[3];
	key->prime1 = nums[4];
	key->prime2 = nums[5];
	key->exponent1 = nums[6];
	key->exponent2 = nums[7];
	key->coefficient = nums[8];
}

void		fill_rsa_pub_key(uint64_t nums[], t_rsa_key *key)
{
	key->modulus = nums[0];
	key->public_exponent = nums[1];
}

t_rsa_key	convert_der_to_pub_key(t_list *der)
{
	t_rsa_key	key;
	uint64_t	nums[2];
	uint8_t		*mem;

	ft_bzero(&key, sizeof(t_rsa_key));
	ft_bzero(nums, sizeof(uint64_t) * 2);
	mem = (uint8_t *)der->content;
	if (!rsa_pub_checker(der))
		return (key);
	nums[0] = get_field(&mem[22], der->content_size);
	nums[1] = get_field(&mem[24 + mem[23]], der->content_size);
	fill_rsa_pub_key(nums, &key);
	return (key);
}

t_rsa_key	convert_der_to_priv_key(t_list *der)
{
	t_rsa_key	key;
	uint8_t		*mem;
	int			i;
	size_t		cur_ind;
	uint64_t	nums[9];

	ft_bzero(&key, sizeof(t_rsa_key));
	ft_bzero(nums, sizeof(uint64_t) * 9);
	mem = (uint8_t *)der->content;
	if (mem[0] != 0x30 || mem[1] != der->content_size - 2)
		return (key);
	i = -1;
	cur_ind = 2;
	while (++i < 9 && cur_ind < der->content_size)
	{
		nums[i] = get_field(&mem[cur_ind], der->content_size);
		cur_ind += (mem[cur_ind + 1] + 2);
	}
	fill_rsa_priv_key(nums, &key);
	return (key);
}
