/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:50:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/21 21:10:18 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_FILE_INFO_H
# define NM_FILE_INFO_H

typedef struct s_output		t_output;

typedef struct				s_file
{
	char					*name;
	int						fd;
	size_t					size;
	void					*start;
}							t_file;

struct						s_output
{
	char				*name;
	char                *command_type;
	char                *hash;
};

void						free_file(t_file **file);

#endif
