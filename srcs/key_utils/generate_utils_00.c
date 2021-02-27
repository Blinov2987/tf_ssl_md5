/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_utils_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:39:14 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 10:41:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		get_8byte_from_ascii(t_list *ascii)
{
	uint8_t	raw[16];
	uint8_t	byte[8];
	int		i;
	int		raw_ind;

	i = -1;
	raw_ind = 0;
	ft_bzero(raw, 16);
	ft_bzero(byte, 8);
	ft_mem_copy(raw, ascii->content,
			ascii->content_size > 16 ? 16 : ascii->content_size);
	while (++i < 8)
	{
		byte[i] = hex_char_to_byte(&raw[raw_ind]);
		raw_ind += 2;
	}
	free(ascii->content);
	ascii->content = ft_safe_memalloc(8, "get_8byte_from_ascii");
	ft_mem_copy(ascii->content, byte, 8);
	ascii->content_size = 8;
}

void		fill_random_values(t_des_args *args)
{
	if (!args->pass_in_ascii && !args->key_in_hex)
		args->pass_in_ascii = get_pass_stdin();
	if (!args->key_in_hex && !args->salt)
		args->salt = get_random_bytes();
	else if (args->salt)
		get_8byte_from_ascii(args->salt);
	if (args->vector)
		get_8byte_from_ascii(args->vector);
}

t_list		*get_random_bytes(void)
{
	int		i;
	t_list	*rnd;
	int		fd;
	uint8_t	byte;

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

uint8_t		hex_char_to_byte(uint8_t *str)
{
	uint8_t	byte;
	int		i;

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
		if (!str[i])
			byte *= 16;
	}
	return (byte);
}
