/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:17:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:27:29 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "errors.h"
# include "printf.h"
# include "args.h"
# include "constants.h"

typedef struct	s_output_streams
{
	t_list		*stdin_stream;
	t_list		*stdin_hash;
	t_list		*string_stream;
	t_list		*string_hash;
	t_list		*filenames;
	t_list		*file_stream;
	t_list		*file_hash;
}				t_output;

void			*ft_safe_memalloc(size_t size, char *function_name);
void			ft_mem_copy(void *dest, void *src, size_t size);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*buffered_reader(int fd);
t_list			*buffered_file_reader(t_args *args);

void			print_hex(uint8_t *mem, size_t size, int fd);
void			print_algo(t_args *args);
void			print_stdin(t_args *args, t_output *output);
void			print_strings_and_files(t_args *args, t_output *output);

uint32_t		rotate_left(uint32_t left, uint32_t right);
t_list			*append_mem_len(void *to_hash_mem,
					size_t to_hash_size, size_t mod_len);
void			fill_chunk_512(uint32_t *chunk, uint8_t *mem);
void			take_byte_from_int(uint8_t *mem, uint32_t val);
uint32_t		take_int_from_byte(uint8_t *mem);
uint64_t		swap64(uint64_t val);

void			entrance_to_hash(t_args *args);
t_list			*sha256(void *mem, size_t size);
t_list			*md5(void *to_hash_mem, size_t to_hash_size);
t_list			*sha512(void *to_hash_mem, size_t to_hash_size);

void			print_output(t_args *args, t_output *output);
void			ft_print_by_size(char *str, size_t size, int fd);
void			print_silent_files(t_list *tmp, t_list *stream);

void			free_output(t_output *output);

#endif
