/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_rsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:07:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 20:09:32 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		free_rsa_args(t_rsa_args **args)
{
	if (*args)
	{
		ft_lstdel(&(*args)->bad_argums, &free_list);
		ft_lstdel(&(*args)->input_files, &free_list);
		ft_lstdel(&(*args)->output_files, &free_list);
		ft_lstdel(&(*args)->in_key, &free_list);
		ft_lstdel(&(*args)->in_form, &free_list);
		ft_lstdel(&(*args)->out_form, &free_list);
		ft_lstdel(&(*args)->pass_in, &free_list);
		ft_lstdel(&(*args)->pass_out, &free_list);
		(*args)->bad_argums = NULL;
		(*args)->input_files = NULL;
		(*args)->output_files = NULL;
		(*args)->in_key = NULL;
		(*args)->in_form = NULL;
		(*args)->out_form = NULL;
		(*args)->pass_in = NULL;
		(*args)->pass_out = NULL;
		free(*args);
		(*args) = NULL;
	}
}

void		free_rsa_out(t_rsa_output *output)
{
	ft_lstdel(&output->der, &free_list);
	ft_lstdel(&output->pem, &free_list);
	ft_lstdel(&output->salt_vector, &free_list);
	ft_lstdel(&output->raw_key, &free_list);
	ft_lstdel(&output->mem, &free_list);
	ft_lstdel(&output->output_stream, &free_list);
}