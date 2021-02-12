/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:50:22 by gemerald          #+#    #+#             */
/*   Updated: 2021/02/12 19:52:45 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	set_flag_des(char f, t_des_args *args)
{
	if (f == 'd')
		args->flag_d++;
	if (f == 'e')
		args->flag_e++;
	if (f == 'i')
		args->flag_i++;
	if (f == 'o')
		args->flag_o++;
	if (f == 'a')
		args->flag_a++;
	if (f == 'k')
		args->flag_k++;
	if (f == 'p')
		args->flag_p++;
	if (f == 's')
		args->flag_s++;
	if (f == 'v')
		args->flag_v++;
}

static void	find_args_des(char *str, t_des_args *args)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (contains_char_sym(DES_FLAGS, str[i]))
			set_flag_des(str[i], args);
		else
		{
			ft_lstadd_back(&args->bad_argums,
					ft_lstnew(str, ft_strlen(str) + 1));
			break ;
		}
	}
}

void 	add_to_args_list(char **av, int *cur_position, t_list **list)
{
	(*cur_position)++;
	ft_lstadd_back(list,
			ft_lstnew(av[*cur_position],
					ft_strlen(av[*cur_position]) + 1));
}

void 	save_args_state(uint8_t saved_args[], t_des_args *args)
{
	saved_args[I] = args->flag_i;
	saved_args[O] = args->flag_o;
	saved_args[S] = args->flag_s;
	saved_args[K] = args->flag_k;
	saved_args[P] = args->flag_p;
	saved_args[V] = args->flag_v;
}

void	pars_args_des(int ac, char **av, int *cur_position, t_des_args *args)
{
	uint8_t saved_args[6];

	save_args_state(saved_args, args);
	if (is_argums(av[*cur_position]))
	{
		find_args_des(&av[*cur_position][1], args);
		if ((saved_args[I] < args->flag_i) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->input_files);
		else if ((saved_args[O] < args->flag_o) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->output_files);
		else if ((saved_args[S] < args->flag_s) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->salt);
		else if ((saved_args[K] < args->flag_k) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->key_in_hex);
		else if ((saved_args[P] < args->flag_p) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->pass_in_ascii);
		else if ((saved_args[V] < args->flag_v) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->vector);
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_position], ft_strlen(av[*cur_position]) + 1));
}

t_des_args	*take_des_args(int ac, char **av)
{
	int				i;
	t_des_args 	*args;

	args = ft_safe_memalloc(sizeof(t_des_args), "take_base64_args");
	i = 1;
	while (++i < ac)
		pars_args_des(ac, av, &i, args);
	return (args);
}

int		validate_args_des(t_des_args **args)
{
	if (!(*args))
		return (FAIL);
	if ((*args)->flag_d > 1 || (*args)->flag_e > 1 ||
		(*args)->flag_o > 1 || (*args)->flag_i > 1 ||
		(*args)->flag_a > 1 || (*args)->flag_k > 1 ||
		(*args)->flag_p > 1 || (*args)->flag_s > 1 ||
		(*args)->flag_v > 1 || (*args)->bad_argums)
	{
		if ((*args)->bad_argums)
			error_print_bad_argums((t_args *)*args);
		else
			error_print_multiple_flags_des(*args);
		return (FAIL);
	}
	if ((*args)->flag_d && (*args)->flag_e)
	{
		error_decrypt_encrypt();
		return (FAIL);
	}
	if ((!(*args)->key_in_hex && !(*args)->pass_in_ascii) ||
		(!(*args)->key_in_hex && !(*args)->salt) || !(*args)->vector)
	{
		error_unexpected_on_key_generation();
		return (FAIL);
	}
	return (SUCCESS);
}
