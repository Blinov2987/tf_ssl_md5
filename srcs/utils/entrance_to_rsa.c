/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:54:33 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/20 11:38:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		entrance_to_rsa(t_rsa_args *args)
{
	t_rsa_output	output;
	t_rsa_key key;

	ft_bzero(&output, sizeof(t_crypt_output));
	if (args->type == GEN_RSA) {
	    key = gen_rsa(args, &output);
		rsa_pem_writer(&key, args);
		int i = 0;
		i++;
	}
}