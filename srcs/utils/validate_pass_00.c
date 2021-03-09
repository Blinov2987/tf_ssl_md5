/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pass_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:46:39 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 22:42:43 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_hex_char(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'F')
		|| (c >= 'a' && c <= 'f'))
		return (TRUE);
	return (FALSE);
}

int		is_hex_string(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (!is_hex_char(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		validate_hex(t_des_args *args)
{
	if ((args->key_in_hex && !is_hex_string(args->key_in_hex->content,
			args->key_in_hex->content_size - 1))
		|| (args->salt && !is_hex_string(args->salt->content,
			args->salt->content_size - 1))
		|| (args->vector && !is_hex_string(args->vector->content,
			args->vector->content_size - 1)))
	{
		error_bad_hex();
		return (FALSE);
	}
	return (TRUE);
}
