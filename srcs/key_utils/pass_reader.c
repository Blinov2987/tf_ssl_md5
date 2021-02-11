/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:12:45 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/11 22:19:49 by gemerald         ###   ########.fr       */
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
			passbuf, 1024, RPP_ECHO_ON) == NULL)
		return (NULL);
	if (ft_strcmp(passbuf, confirmbuf))
		return (NULL);
	pass_phrase = ft_lstnew(passbuf, ft_strlen(passbuf) + 1);
	ft_bzero(passbuf, 1024);
	ft_bzero(confirmbuf, 1024);
	return (pass_phrase);
}

t_list *init_key_vector(t_des_args *args)
{
	t_key_vector key_vector;

	ft_bzero(&key_vector, sizeof(t_key_vector));
	if (!args->pass_in_ascii && !args->key_in_hex)
		args->pass_in_ascii = get_pass_stdin();
	return (NULL);
}