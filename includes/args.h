/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:48:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/30 19:34:59 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include "libft.h"

typedef struct		s_cmd_type
{
	uint8_t 		type;
	uint8_t 		algo;
}					t_cmd_type;

typedef struct		s_base64_flags
{
	uint8_t 		type;
	uint8_t 		algo;
	t_list			*bad_argums;
	t_list			*input_files;
	t_list			*output_files;
	char			flag_d;
	char			flag_e;
	char			flag_i;
	char			flag_o;
}					t_base64_args;

typedef struct		s_des_flags
{
	uint8_t 		type;
	uint8_t 		algo;
	t_list			*bad_argums;
	t_list			*input_files;
	t_list			*output_files;
	char			flag_a;
	char			flag_d;
	char			flag_e;
	char			flag_i;
	char			flag_k;
	char			flag_o;
	char			flag_p;
	char			flag_s;
	char			flag_v;
}					t_des_args;

typedef struct		s_args
{
	uint8_t 		type;
	uint8_t 		algo;
	t_list			*bad_argums;
	t_list			*filenames;
	t_list			*strings;
	char			flag_p;
	char			flag_q;
	char			flag_r;
	char			flag_s;
}					t_args;

int					is_argums(char *av);
void				decrease_string_size(t_list *list);
int					contains_char_sym(char *str, char to_count);

t_args				*take_hash_args(int ac, char **av);
t_base64_args 		*take_base64_args(int ac, char **av);
int					take_command(char *command, t_args *args);
int					validate_args(t_args **args);
int					validate_args_base64(t_base64_args **args);
void				free_args(t_args **args);
void				find_args(char *str, t_args *args);

void				fill_hash_cmd(t_cmd_type *cmd, char *command);
void				fill_cipher_cmd(t_cmd_type *cmd, char *command);

#endif
