/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:52:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/13 22:41:49 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	error_unexpected_on_key_generation(void)
{
	ft_putendl_fd("ft_ssl: unexpected key generation error", 2);
}

void	error_bad_vector(void)
{
	ft_putendl_fd("ft_ssl: bad vector", 2);
}

void	error_bad_hex(void)
{
	ft_putendl_fd("ft_ssl: non-hex digit", 2);
}

void	error_bad_salt(void)
{
	ft_putendl_fd("ft_ssl: bad salt on input", 2);
}
