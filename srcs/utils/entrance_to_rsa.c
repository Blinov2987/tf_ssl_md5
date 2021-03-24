/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:54:33 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 21:44:48 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void rsa_printer(t_rsa_args *args, t_rsa_output *output)
{
	int fd;

	fd = get_out_fd(args);
	if (args->text)
		key_text_print(args, output, fd);
	if (args->modulus)
		modulus_print(output, fd);
	if (args->check)
		ft_putendl_fd("RSA key ok", fd);
	if (!args->noout)
	{
		ft_putendl_fd("writing RSA key", 2);
		rsa_pem_writer(args, output, fd);
	}
	if (fd > 1)
		close(fd);
}

void		entrance_to_rsa(t_rsa_args *args)
{
	t_rsa_output	output;

	if (args->pubin && args->check)
	{
		ft_putendl_fd("Only private keys can be checked", 2);
		return ;
	}
	ft_bzero(&output, sizeof(t_rsa_output));
	if (args->check)
	{

	}
	ft_bzero(&output, sizeof(t_rsa_output));
	free_rsa_out(&output);
}