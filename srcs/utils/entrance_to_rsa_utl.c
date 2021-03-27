/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa_utl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:59:53 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 08:26:58 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		entrance_to_rsa_utl(t_rsa_args *args)
{
	t_rsa_output	output;

	ft_bzero(&output, sizeof(t_rsa_output));
	if (!get_key_from_user(args, &output))
	{
		free_rsa_out(&output);
		return ;
	}
	if (args->decrypt && output.is_private_key_found)
	{
		ft_putendl_fd("A private key is needed for this operation", 2);
		free_rsa_out(&output);
		return ;
	}
}