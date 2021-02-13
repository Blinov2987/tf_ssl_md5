/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:12:08 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 18:21:34 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_list	*get_random_bytes(void)
{
	int			i;
	t_list		*rnd;
	int			fd;
	uint8_t 	byte;

	i = -1;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 3)
		return (NULL);
	rnd = ft_safe_memalloc(sizeof(t_list), "get_random_bytes");
	rnd->content = ft_safe_memalloc(8, "get_random_bytes");
	rnd->content_size = 8;
	while (++i < 8)
	{
		read(fd, &byte, 1);
		((uint8_t *)rnd->content)[i] = byte;
	}
	close(fd);
	return (rnd);
}

uint8_t 	hex_char_to_byte(uint8_t *str)
{
	uint8_t byte;
	int 	i;

	i = -1;
	byte = 0;
	while (++i < 2)
	{
		if (str[i] >= '0' && str[i] <= '9')
			byte = byte * 16 + (str[i] - '0');
		if (str[i] >= 'a' && str[i] <= 'f')
			byte = byte * 16 + (str[i] - 'a') + 10;
		if (str[i] >= 'A' && str[i] <= 'F')
			byte = byte * 16 + (str[i] - 'A') + 10;
	}
	return (byte);
}

static void 	fill_key_vector_des(t_des_args *args,
		t_key_vector *key_vector, t_list *hash)
{
	key_vector->keys[0] = take_uint64_from_uint8(hash->content);
	if (!args->vector)
		key_vector->vector = take_uint64_from_uint8(&((uint8_t *)hash->content)[8]);
	else
		key_vector->vector = take_uint64_from_uint8(args->vector->content);
}

static void 	fill_key_vector_des3(t_des_args *args,
		t_key_vector *key_vector, t_list *hash, t_list *hash2)
{
	key_vector->keys[0] = take_uint64_from_uint8(hash->content);
	key_vector->keys[1] = take_uint64_from_uint8(&((uint8_t *)hash->content)[8]);
	key_vector->keys[2] = take_uint64_from_uint8(hash2->content);
	if (!args->vector)
		key_vector->vector = take_uint64_from_uint8(&((uint8_t *)hash2->content)[8]);
	else
		key_vector->vector = take_uint64_from_uint8(args->vector->content);
}

void 	pbkfd(t_des_args *args, t_key_vector *key_vector)
{
	uint8_t *buf;
	uint8_t *buf2;
	size_t  size;
	t_list	*result;
	t_list	*result2;

	size = args->pass_in_ascii->content_size - 1 + 8;
	buf = ft_safe_memalloc(size, "pbkfd");
	buf2 = ft_safe_memalloc(size + 16, "pbkfd");
	ft_bzero(buf, size);
	ft_bzero(buf2, size + 16);
	ft_mem_copy(buf, args->pass_in_ascii->content, args->pass_in_ascii->content_size - 1);
	ft_mem_copy(&buf[args->pass_in_ascii->content_size - 1], args->salt->content, 8);
	result = md5(buf, size);
	ft_mem_copy(buf2, result->content, 16);
	ft_mem_copy(&buf2[16], buf, size);
	result2 = md5(buf2, size + 16);
	if (args->type == DES_COMMAND)
		fill_key_vector_des(args, key_vector, result);
	else
		fill_key_vector_des3(args, key_vector, result, result2);
	ft_lstdel(&result, &free_list);
	ft_lstdel(&result2, &free_list);
	free(buf);
	free(buf2);
}