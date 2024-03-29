/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 19:01:19 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/25 20:05:05 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_OUTPUT_H
# define FT_SSL_DES_OUTPUT_H

typedef struct	s_crypt_output
{
	t_list		*pointers_to_free;
	t_list		*mem;
	t_list		*output_stream;
}				t_crypt_output;

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

void			free_crypt_output(t_crypt_output *output);

#endif
