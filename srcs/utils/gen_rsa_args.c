/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:08:04 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/23 21:56:22 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		set_flag_rsa(char f, t_rsa_args *args)
{
	if (f == 'i')
		args->in++;
	if (f == 'o')
		args->out++;
}

static void		find_args_rsa(char *str, t_rsa_args *args)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (contains_char_sym("io", str[i]))
			set_flag_rsa(str[i], args);
		else
		{
			ft_lstadd_back(&args->bad_argums,
					ft_lstnew(str, ft_strlen(str) + 1));
			break ;
		}
	}
}

void			pars_args_gen_rsa(int ac, char **av,
		int *cur_pos, t_rsa_args *args)
{
	uint8_t input_files_count;
	uint8_t output_files_count;

	input_files_count = args->in;
	output_files_count = args->out;
	if (is_argums(av[*cur_pos]))
	{
		find_args_rsa(&av[*cur_pos][1], args);
		if ((input_files_count < args->in) && *cur_pos < (ac - 1))
			add_to_args_list(av, cur_pos, &args->input_files);
		else if ((output_files_count < args->out) && *cur_pos < (ac - 1))
			add_to_args_list(av, cur_pos, &args->output_files);
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_pos],
						ft_strlen(av[*cur_pos]) + 1));
}

t_rsa_args	*take_gen_rsa_args(int ac, char **av)
{
	int				i;
	t_rsa_args	*args;

	args = ft_safe_memalloc(sizeof(t_rsa_args), "take_gen_rsa_args");
	i = 1;
	while (++i < ac)
		pars_args_gen_rsa(ac, av, &i, args);
	return (args);
}

int				validate_args_rsa(t_rsa_args **args)
{
	if (!(*args))
		return (FAIL);
	if ((*args)->bad_argums)
	{
		error_print_bad_argums((t_args *)*args);
		return (FAIL);
	}
	if ((*args)->inform && ft_strcmp("PEM", (*args)->in_form->content))
	{
		write(2, "ft_ssl: incorrect inform value\n", 31);
		return (FAIL);
	}
	if ((*args)->outform && ft_strcmp("PEM", (*args)->out_form->content))
	{
		write(2, "ft_ssl: incorrect outform value\n", 32);
		return (FAIL);
	}
	return (SUCCESS);
}