/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:17:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/22 21:37:31 by gemerald         ###   ########.fr       */
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
void	ft_lstadd_back(t_list **alst, t_list *new);
t_mem_zone buffered_reader(int fd);

t_list  *take_stdin(t_args *args, uint32_t *(*hash_function)(void *, size_t));

void entrance_to_hash(t_args *args);

void sha256_process(t_args *args);

void md5_process(t_args *args);

#endif
