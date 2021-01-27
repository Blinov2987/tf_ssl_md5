/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:33:18 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:38:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void	md5_round_shit_before_16(t_handler *hndl, int i)
{
	hndl->f = (hndl->b & hndl->c) | ((~hndl->b) & hndl->d);
	hndl->g = i;
}

void	md5_round_shit_before_32(t_handler *hndl, int i)
{
	hndl->f = (hndl->d & hndl->b) | ((~hndl->d) & hndl->c);
	hndl->g = (5 * i + 1) % 16;
}

void	md5_round_shit_before_48(t_handler *hndl, int i)
{
	hndl->f = hndl->b ^ hndl->c ^ hndl->d;
	hndl->g = (3 * i + 5) % 16;
}

void	md5_round_shit_before_64(t_handler *hndl, int i)
{
	hndl->f = hndl->c ^ (hndl->b | (~hndl->d));
	hndl->g = (7 * i) % 16;
}
