/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_args_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:33:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/29 22:50:51 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	set_flag_base64(char f, t_base64_args *args)
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

static void	find_args_base64(char *str, t_base64_args *args)
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

void	pars_args(int ac, char **av, int *cur_position, t_base64_args *args)
{
	uint8_t input_files_count;
	uint8_t output_files_count;

	input_files_count = args->flag_i;
	output_files_count = args->flag_o;
	if (is_argums(av[*cur_position]))
	{
		find_args_base64(&av[*cur_position][1], args);
		if ((input_files_count < args->flag_i) && *cur_position < (ac - 1))
		{
			(*cur_position)++;
			ft_lstadd_back(&args->input_files,
					ft_lstnew(av[*cur_position],
							ft_strlen(av[*cur_position]) + 1));
		}
		else if ((output_files_count < args->flag_o) && *cur_position < (ac - 1))
		{
			(*cur_position)++;
			ft_lstadd_back(&args->output_files,
					ft_lstnew(av[*cur_position],
							ft_strlen(av[*cur_position]) + 1));
		}
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_position], ft_strlen(av[*cur_position]) + 1));
}

t_base64_args	*take_base64_args(int ac, char **av)
{
	int				i;
	t_base64_args 	*args;

	args = ft_safe_memalloc(sizeof(t_base64_args), "take_base64_args");
	i = 1;
	while (++i < ac)
		pars_args(ac, av, &i, args);
	return (args);
}

int		validate_args_base64(t_base64_args **args)
{
	if (!(*args))
		return (FAIL);
	if ((*args)->flag_p > 1 || (*args)->flag_q > 1 || (*args)->flag_r > 1 ||
		(*args)->bad_argums)
	{
		if ((*args)->flag_p > 1 || (*args)->flag_q > 1 ||
			(*args)->flag_r > 1)
			error_print_multiple_flags(*args);
		if ((*args)->bad_argums)
			error_print_bad_argums(*args);
		return (FAIL);
	}
	decrease_string_size((*args)->filenames);
	decrease_string_size((*args)->strings);
	return (SUCCESS);
}