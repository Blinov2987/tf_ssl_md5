/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:35:45 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/30 19:18:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_ERRORS_H
# define NM_ERRORS_H

# include "args.h"

int		print_usage();
int		print_commands();
void	print_incorrect_command(char *command);
int		error_file_corrupt(char *file_name);
int		error_open_file(char *file_name);
int		error_bad_file_descriptor(char *file_name);
int		error_read_file(char *file_name);
int		error_recognize_file(char *file_name);
void	error_print_multiple_flags(t_args *args);
void	error_print_bad_argums(t_args *args);
void	error_safe_memalloc(char *funtion_name);
void	error_print_multiple_flags_base64(t_base64_args *args);
void	error_print_multiple_flags_des(t_des_args *args);
void 	error_decrypt_encrypt(void);
void 	pass_validation_error(void);
void 	error_unexpected_on_key_generation(void);
void 	error_bad_vector(void);
void 	error_bad_hex(void);
void	error_bad_salt(void);

#endif
