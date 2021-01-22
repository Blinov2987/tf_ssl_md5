/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:24:37 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/22 19:26:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void entrance_to_hash(t_args *args)
{
	if (args->is_md5)
		md5_process(args);
	if (args->is_sha256)
		sha256_process(args);
}