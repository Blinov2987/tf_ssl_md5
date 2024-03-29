/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:12:45 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:42 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <readpassphrase.h>

t_list			*get_pass_stdin(void)
{
	char	passbuf[1024];
	char	confirmbuf[1024];
	t_list	*pass_phrase;

	ft_bzero(passbuf, 1024);
	ft_bzero(confirmbuf, 1024);
	if (readpassphrase("enter des encryption password:",
			passbuf, 1024, RPP_REQUIRE_TTY) == NULL)
		return (NULL);
	if (readpassphrase("Verifying - enter des encryption password:",
			confirmbuf, 1024, RPP_REQUIRE_TTY) == NULL)
		return (NULL);
	if (ft_strcmp(passbuf, confirmbuf))
	{
		pass_validation_error();
		return (NULL);
	}
	pass_phrase = ft_lstnew(passbuf, ft_strlen(passbuf) + 1);
	ft_bzero(passbuf, 1024);
	ft_bzero(confirmbuf, 1024);
	return (pass_phrase);
}

void			get_keys_from_hex(t_list *hex, uint64_t *dest)
{
	uint8_t	buf[48];
	uint8_t	raw[24];
	int		i;
	int		buf_ind;

	ft_bzero(buf, 48);
	ft_bzero(raw, 24);
	ft_mem_copy(buf, hex->content, hex->content_size % 49);
	i = -1;
	buf_ind = 0;
	while (++i < 24)
	{
		raw[i] = hex_char_to_byte(&buf[buf_ind]);
		buf_ind += 2;
	}
	dest[0] = take_uint64_from_uint8(&raw[0]);
	dest[1] = take_uint64_from_uint8(&raw[8]);
	dest[2] = take_uint64_from_uint8(&raw[16]);
}

void			prepare_keys(t_des_args *args, t_key_vector *key_vector)
{
	if (args->key_in_hex)
		get_keys_from_hex(args->key_in_hex, key_vector->keys);
	if (args->vector)
		key_vector->vector = take_uint64_from_uint8(args->vector->content);
}

t_key_vector	init_key_vector(t_des_args *args)
{
	t_key_vector key_vector;

	ft_bzero(&key_vector, sizeof(t_key_vector));
	key_vector.keys = ft_safe_memalloc(sizeof(uint64_t) * 3, "init_key_vector");
	prepare_keys(args, &key_vector);
	return (key_vector);
}
