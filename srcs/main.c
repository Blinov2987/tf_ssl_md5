/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:55:55 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/21 21:29:08 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int main(int ac, char **av)
{
	t_args *args;

	args = take_args(ac, av);
	validate_args(&args, ac);
	free_args(&args);
	return (0);
}
