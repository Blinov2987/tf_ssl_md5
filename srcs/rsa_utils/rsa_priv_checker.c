/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_priv_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:18:39 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/21 15:29:42 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int		rsa_priv_equ(t_rsa_key key1, t_rsa_key key2)
{
	return (key1.private_exponent == key2.private_exponent
	&& key1.modulus == key2.modulus
	&& key1.exponent1 == key2.exponent1
	&& key1.exponent2 == key2.exponent2
	&& key1.coefficient == key2.coefficient);
}

int		rsa_priv_checker(t_rsa_key *key)
{
	t_rsa_key key2;

	key2 = gen_rsa_key_on_primes(key->prime1,
			key->prime2, key->public_exponent);
	if (!rsa_priv_equ(*key, key2))
		return (FALSE);
	return (TRUE);
}
