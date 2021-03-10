/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:48:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/10 21:54:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include "libft.h"

# define I 0
# define O 1
# define S 2
# define K 3
# define P 4
# define V 5

typedef struct		s_cmd_type
{
	uint8_t			type;
	uint8_t			algo;
}					t_cmd_type;

typedef struct		s_key_vector
{
	uint64_t		*keys;
	uint64_t		vector;
}					t_key_vector;

typedef struct		s_base64_flags
{
	uint8_t			type;
	uint8_t			algo;
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
	uint8_t			type;
	uint8_t			algo;
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
	t_list			*key_in_hex;
	t_list			*pass_in_ascii;
	t_list			*vector;
	t_list			*salt;
	t_key_vector	key_vector;
}					t_des_args;

typedef struct		s_args
{
	uint8_t			type;
	uint8_t			algo;
	t_list			*bad_argums;
	t_list			*filenames;
	t_list			*strings;
	char			flag_p;
	char			flag_q;
	char			flag_r;
	char			flag_s;
}					t_args;

typedef struct		s_rsa_args
{
	uint8_t			type;
	uint8_t			algo;
	t_list			*bad_argums;
	t_list			*input_files;
	t_list			*output_files;
	t_list			*in_key;
	t_list			*in_form;
	t_list			*out_form;
	t_list			*pass_in;
	t_list			*pass_out;
	char			inform;
	char			outform;
	char			in;
	char			out;
	char			passin;
	char			passout;
	char			des;
	char			text;
	char			noout;
	char			modulus;
	char			check;
	char			pubin;
	char			pubout;
	char			encrypt;
	char			decrypt;
	char			inkey;
	char			hexdump;
}					t_rsa_args;

int					is_argums(char *av);
void				decrease_string_size(t_list *list);
int					contains_char_sym(char *str, char to_count);

t_args				*take_hash_args(int ac, char **av);
t_base64_args		*take_base64_args(int ac, char **av);
t_des_args			*take_des_args(int ac, char **av);
t_rsa_args			*take_rsa_args(int ac, char **av);
int					take_command(char *command, t_args *args);
int					validate_args(t_args **args);
int					validate_args_base64(t_base64_args **args);
int					validate_args_des(t_des_args **args);
int					validate_args_rsa(t_rsa_args **args);
int					is_hex_string(char *str, size_t len);
int					validate_hex(t_des_args *args);
void				free_args(t_args **args);
void				free_des_args(t_des_args **args);
void				find_args(char *str, t_args *args);
void				add_to_args_list(char **av, int *cur_position,
					t_list **list);
void				pars_args_des(int ac, char **av,
					int *cur_position, t_des_args *args);

void				fill_hash_cmd(t_cmd_type *cmd, char *command);
void				fill_cipher_cmd(t_cmd_type *cmd, char *command);
void				fill_rsa_cmd(t_cmd_type *cmd, char *command);

#endif
