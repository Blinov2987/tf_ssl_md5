/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:17:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/23 10:10:30 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_NM_H
# define NM_NM_H

# include "libft.h"
# include "errors.h"
# include "printf.h"
# include "args.h"
# include "handler_info.h"
# include "constants.h"

typedef struct s_mem_zone
{
	void *mem;
	size_t size;
} t_mem_zone;

void *ft_safe_memalloc(size_t size, char *function_name);
void    ft_mem_copy(void *dest, void *src, size_t size);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list *buffered_reader(int fd);
t_list *buffered_file_reader(t_args *args);

t_list  *take_stdin(t_args *args, t_list *stream, t_list *(*hash_function)(void *, size_t));

t_list *md5(void *to_hash_mem, size_t to_hash_size);

void entrance_to_hash(t_args *args);

void sha256_process(t_args *args);

void md5_process(t_args *args);

#endif
