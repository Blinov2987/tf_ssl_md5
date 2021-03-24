/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_gen_rsa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:59:20 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 20:14:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		entrance_to_gen_rsa(t_rsa_args *args)
{
	t_rsa_output	output;
	int				fd;

	fd = get_out_fd(args);
	ft_bzero(&output, sizeof(t_rsa_output));
	output.key = gen_rand_rsa(65537);
	get_pem_priv_form(args, &output);
	rsa_pem_writer(args, &output, fd);
	if (fd > 2)
		close(fd);
	free_rsa_out(&output);
}
