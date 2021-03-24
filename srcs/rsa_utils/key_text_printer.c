/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_text_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:59:16 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 21:33:00 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void 			modulus_print(t_rsa_output *out, int fd)
{
	ft_sprintf(fd, "Modulus=%llX\n", out->key.modulus);
}

static void 	pub_printer(t_rsa_output *out, int fd)
{
	ft_putendl_fd("Private-Key: (64 bit)", fd);
	ft_sprintf(fd, "Modulus: %llu (%#llx)\n",
			out->key.modulus, out->key.modulus);
	ft_sprintf(fd, "Exponent: %llu (%#llx)\n",
			out->key.public_exponent, out->key.public_exponent);
}

static void 	priv_printer(t_rsa_output *out, int fd)
{
	ft_putendl_fd("Private-Key: (64 bit)", fd);
	ft_sprintf(fd, "Modulus: %llu (%#llx)\n", out->key.modulus,
			out->key.modulus);
	ft_sprintf(fd, "publicExponent: %llu (%#llx)\n", out->key.public_exponent,
			out->key.public_exponent);
	ft_sprintf(fd, "privateExponent: %llu (%#llx)\n", out->key.private_exponent,
			out->key.private_exponent);
	ft_sprintf(fd, "prime1: %llu (%#llx)\n", out->key.prime1, out->key.prime1);
	ft_sprintf(fd, "prime2: %llu (%#llx)\n", out->key.prime2, out->key.prime2);
	ft_sprintf(fd, "exponent1: %llu (%#llx)\n", out->key.exponent1,
			out->key.exponent1);
	ft_sprintf(fd, "exponent2: %llu (%#llx)\n", out->key.exponent2,
			out->key.exponent2);
	ft_sprintf(fd, "coefficient: %llu (%#llx)\n", out->key.coefficient,
			out->key.coefficient);
}

void 	key_text_print(t_rsa_args *args, t_rsa_output *out, int fd)
{
	if (args->pubin)
		pub_printer(out, fd);
	else
		priv_printer(out, fd);
}