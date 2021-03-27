/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:54:33 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 18:03:15 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void		rsa_printer(t_rsa_args *args, t_rsa_output *output)
{
	int fd;

	fd = get_out_fd(args);
	if (args->text)
		key_text_print(args, output, fd);
	if (args->modulus)
		modulus_print(output, fd);
	if (args->check)
	{
		if (rsa_priv_checker(&output->key))
			ft_putendl_fd("RSA key ok", fd);
		else
			return ;
	}
	if (!args->noout)
	{
		if (!args->pubout && !args->pubin)
			get_pem_priv_form(args, output);
		else
			get_pem_pub_form(args, output);
		ft_putendl_fd("writing RSA key", 2);
		rsa_pem_writer(args, output, fd);
	}
	if (fd > 1)
		close(fd);
}

int				get_key_from_user(t_rsa_args *args, t_rsa_output *output)
{
	if (args->in_key)
		output->raw_key = buffered_file_reader(args->in_key);
	else
		output->raw_key = buffered_reader(1);
	if (!(read_pem_form(output->raw_key, output)))
		return (FALSE);
	if (!output->raw_key)
	{
		ft_putendl_fd("unable to load Key", 2);
		return (FALSE);
	}
	if (!raw_key_convert_to_rsa_key(args, output))
		return (FALSE);
	return (TRUE);
}

void			entrance_to_rsa(t_rsa_args *args)
{
	t_rsa_output	output;

	ft_bzero(&output, sizeof(t_rsa_output));
	if (!get_key_from_user(args, &output))
	{
		free_rsa_out(&output);
		return ;
	}
	if ((args->pubin && args->check) || (args->check
	&& !output.is_private_key_found))
	{
		ft_putendl_fd("Only private keys can be checked", 2);
		return ;
	}
	if (output.is_private_key_found && args->pubin)
	{
		ft_putendl_fd("unable to load Public Key", 2);
		return ;
	}
	ft_del_simple_list(&output.der);
	rsa_printer(args, &output);
	free_rsa_out(&output);
}
