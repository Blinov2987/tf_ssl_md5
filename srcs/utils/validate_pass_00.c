/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pass_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:46:39 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/03 18:46:39 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_hex_char(char c)
{
	if (c >= '0' && c <= '9'
		|| c >= 'A' && c <= 'F'
		|| c >= 'a' && c <= 'f')
		return (TRUE);
	return (FALSE);
}

int 	is_hex_string(char *str, size_t len)
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

int		is_correct_pass(t_list *pass)
{

}
