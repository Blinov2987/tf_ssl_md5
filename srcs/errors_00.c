/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:22:07 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/21 19:05:17 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	error_file_corrupt(char *file_name)
{
	ft_putstr_fd("ft_ssl: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": file corrupt.\n", 2);
	return (FALSE);
}

int	error_open_file(char *file_name, size_t size)
{
	ft_putstr_fd("ft_ssl: error: ", 2);
	ft_print_by_size(file_name, size, 2);
	ft_putstr_fd(": No such file or directory.\n", 2);
	return (FALSE);
}

int	error_bad_file_descriptor(char *file_name)
{
	ft_putstr_fd("ft_ssl: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Bad descriptor.\n", 2);
	return (FALSE);
}

int	error_read_file(char *file_name)
{
	ft_putstr_fd("ft_ssl: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Is a directory.\n", 2);
	return (FALSE);
}

int	error_recognize_file(char *file_name)
{
	ft_putstr_fd("ft_ssl: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": The file was not recognized as a valid object file.\n", 2);
	return (FALSE);
}
