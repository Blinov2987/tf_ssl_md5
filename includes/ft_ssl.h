/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:17:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/21 21:08:09 by gemerald         ###   ########.fr       */
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

void *ft_safe_memalloc(size_t size, char *function_name);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif
