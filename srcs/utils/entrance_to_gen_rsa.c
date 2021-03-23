/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_gen_rsa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:59:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/23 21:59:48 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		entrance_to_gen_rsa(t_rsa_args *args)
{
	t_rsa_output	output;
	t_rsa_key key;

	ft_bzero(&output, sizeof(t_crypt_output));
	if (args->type == GEN_RSA) {
		key = gen_rand_rsa(65537);
		rsa_private_pem_des_writer(&key, args);
		int i = 0;
		i++;
	}
}
