/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_args_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:33:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/27 11:13:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		set_flag_base64(char f, t_base64_args *args)
{
	if (f == 'd')
		args->flag_d++;
	if (f == 'e')
		args->flag_e++;
	if (f == 'i')
		args->flag_i++;
	if (f == 'o')
		args->flag_o++;
}

static void		find_args_base64(char *str, t_base64_args *args)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (contains_char_sym(BASE64_FLAGS, str[i]))
			set_flag_base64(str[i], args);
		else
		{
			ft_lstadd_back(&args->bad_argums,
					ft_lstnew(str, ft_strlen(str) + 1));
			break ;
		}
	}
}

void			pars_args_base64(int ac, char **av,
				int *cur_pos, t_base64_args *args)
{
	uint8_t input_files_count;
	uint8_t output_files_count;

	input_files_count = args->flag_i;
	output_files_count = args->flag_o;
	if (is_argums(av[*cur_pos]))
	{
		find_args_base64(&av[*cur_pos][1], args);
		if ((input_files_count < args->flag_i) && *cur_pos < (ac - 1))
			add_to_args_list(av, cur_pos, &args->input_files);
		else if ((output_files_count < args->flag_o) && *cur_pos < (ac - 1))
			add_to_args_list(av, cur_pos, &args->output_files);
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_pos],
						ft_strlen(av[*cur_pos]) + 1));
}

t_base64_args	*take_base64_args(int ac, char **av)
{
	int				i;
	t_base64_args	*args;

	args = ft_safe_memalloc(sizeof(t_base64_args), "take_base64_args");
	i = 1;
	while (++i < ac)
		pars_args_base64(ac, av, &i, args);
	return (args);
}

int				validate_args_base64(t_base64_args **args)
{
	if (!(*args))
		return (FAIL);
	if ((*args)->flag_d > 1 || (*args)->flag_e > 1 || (*args)->flag_o > 1 ||
		(*args)->bad_argums || (*args)->flag_i > 1)
	{
		if ((*args)->flag_d > 1 || (*args)->flag_e > 1 ||
			(*args)->flag_o > 1 || (*args)->flag_i > 1)
			error_print_multiple_flags_base64(*args);
		if ((*args)->bad_argums)
			error_print_bad_argums((t_args *)*args);
		return (FAIL);
	}
	if ((*args)->flag_d && (*args)->flag_e)
	{
		error_decrypt_encrypt();
		return (FAIL);
	}
	return (SUCCESS);
}
