/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_args_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:08:51 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 18:08:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void		set_additional_flag_rsa(int flag, t_rsa_args *args)
{
	if (flag == 11)
		args->modulus++;
	if (flag == 12)
		args->check++;
	if (flag == 13)
		args->pubin++;
	if (flag == 14)
		args->pubout++;
}

void			set_flag_rsa(int flag, t_rsa_args *args)
{
	if (flag == 0)
		args->inform++;
	if (flag == 1)
		args->outform++;
	if (flag == 2 || flag == 3)
		args->in++;
	if (flag == 4)
		args->passin++;
	if (flag == 5 || flag == 6)
		args->out++;
	if (flag == 7)
		args->passout++;
	if (flag == 8)
		args->des++;
	if (flag == 9)
		args->text++;
	if (flag == 10)
		args->noout++;
	set_additional_flag_rsa(flag, args);
}
