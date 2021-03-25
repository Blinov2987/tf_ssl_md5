/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrance_to_rsa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:54:33 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/25 21:02:58 by gemerald         ###   ########.fr       */
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

int		get_key_from_user(t_rsa_args *args, t_rsa_output *output)
{
	if (args->input_files)
		output->raw_key = buffered_file_reader(args->input_files);
	else
		output->raw_key = buffered_reader(1);
	output->raw_key = read_pem_form(output->raw_key);
	if (!output->raw_key)
	{
		ft_putendl_fd("unable to load Key", 2);
		return (FALSE);
	}
	if (!raw_key_convert_to_rsa_key(args, output))
		return (FALSE);
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
	if (get_key_from_user(args, &output))
	{
		free_rsa_out(&output);
		return ;
	}
	if (args->check)
	{

	}
	free_rsa_out(&output);
}