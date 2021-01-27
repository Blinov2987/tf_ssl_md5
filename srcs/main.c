/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:55:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:28:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int ac, char **av)
{
	t_args *args;

	args = take_args(ac, av);
	if (validate_args(&args, ac))
		entrance_to_hash(args);
	free_args(&args);
	return (0);
}
