/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:48:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 19:27:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include "libft.h"

typedef struct		s_args
{
	char			flag_p;
	char			flag_q;
	char			flag_r;
	char			flag_s;
	uint8_t			is_md5;
	uint8_t			is_sha256;
	uint8_t			is_sha512;
	t_list			*bad_argums;
	t_list			*filenames;
	t_list			*strings;
}					t_args;

t_args				*take_args(int ac, char **av);
int					take_command(char *command, t_args *args);
int					validate_args(t_args **args, int ac);
void				free_args(t_args **args);
void				find_args(char *str, t_args *args);

#endif
