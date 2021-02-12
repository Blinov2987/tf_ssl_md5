/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:12:45 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/12 20:35:36 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <readpassphrase.h>

t_list *get_pass_stdin(void)
{
	char	passbuf[1024];
	char	confirmbuf[1024];
	t_list	*pass_phrase;

//RPP_REQUIRE_TTY
	ft_bzero(passbuf, 1024);
	ft_bzero(confirmbuf, 1024);
	if (readpassphrase("enter des encryption password:",
			passbuf, 1024, RPP_ECHO_ON) == NULL)
		return (NULL);
	if (readpassphrase("Verifying - enter des encryption password:",
			confirmbuf, 1024, RPP_ECHO_ON) == NULL)
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

void 		fill_random_values(t_des_args *args)
{
	if (!args->pass_in_ascii && !args->key_in_hex)
		args->pass_in_ascii = get_pass_stdin();
	if (!args->key_in_hex && !args->salt)
		args->salt = get_random_bytes();
	if (!args->vector)
		args->vector = get_random_bytes();
}

t_key_vector init_key_vector(t_des_args *args)
{
	t_key_vector key_vector;

	ft_bzero(&key_vector, sizeof(t_key_vector));
	return (key_vector);
}