/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:52:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/12 19:52:55 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void 	error_unexpected_on_key_generation(void)
{
	ft_putendl_fd("ft_ssl: unexpected key generation error", 2);
}
