/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_args_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:16:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/10 21:54:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void		set_flag_rsa(char f, t_rsa_args *args)
{
//	if (f == 'd')
//		args->flag_d++;
//	if (f == 'e')
//		args->flag_e++;
//	if (f == 'i')
//		args->flag_i++;
//	if (f == 'o')
//		args->flag_o++;
//	if (f == 'a')
//		args->flag_a++;
//	if (f == 'k')
//		args->flag_k++;
//	if (f == 'p')
//		args->flag_p++;
//	if (f == 's')
//		args->flag_s++;
//	if (f == 'v')
//		args->flag_v++;
}

static void		find_args_rsa(char *str, t_rsa_args *args)
{
//	int i;
//
//	i = -1;
//	while (str[++i])
//	{
//		if (contains_char_sym(rsa_FLAGS, str[i]))
//			set_flag_rsa(str[i], args);
//		else
//		{
//			ft_lstadd_back(&args->bad_argums,
//					ft_lstnew(str, ft_strlen(str) + 1));
//			break ;
//		}
//	}
}

void			pars_args_rsa(int ac, char **av,
		int *cur_position, t_rsa_args *args)
{
//	uint8_t saved_args[6];
//
//	save_args_state(saved_args, args);
//	if (is_argums(av[*cur_position]))
//	{
//		find_args_rsa(&av[*cur_position][1], args);
//		if ((saved_args[I] < args->flag_i) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->input_files);
//		else if ((saved_args[O] < args->flag_o) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->output_files);
//		else if ((saved_args[S] < args->flag_s) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->salt);
//		else if ((saved_args[K] < args->flag_k) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->key_in_hex);
//		else if ((saved_args[P] < args->flag_p) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->pass_in_ascii);
//		else if ((saved_args[V] < args->flag_v) && *cur_position < (ac - 1))
//			add_to_args_list(av, cur_position, &args->vector);
//	}
//	else
//		ft_lstadd_back(&args->bad_argums,
//				ft_lstnew(av[*cur_position],
//						ft_strlen(av[*cur_position]) + 1));
}

int				validate_args_rsa(t_rsa_args **args)
{
//	if (!(*args))
//		return (FAIL);
//	if ((*args)->flag_d > 1 || (*args)->flag_e > 1 || (*args)->flag_o > 1
//		|| (*args)->flag_i > 1 || (*args)->flag_a > 1 || (*args)->flag_k > 1
//		|| (*args)->flag_p > 1 || (*args)->flag_s > 1 || (*args)->flag_v > 1
//		|| (*args)->bad_argums)
//	{
//		if ((*args)->bad_argums)
//			error_print_bad_argums((t_args *)*args);
//		else
//			error_print_multiple_flags_rsa(*args);
//		return (FAIL);
//	}
//	if ((*args)->flag_d && (*args)->flag_e)
//	{
//		error_decrypt_encrypt();
//		return (FAIL);
//	}
//	if ((!(*args)->key_in_hex && !(*args)->pass_in_ascii) ||
//		(!(*args)->key_in_hex && !(*args)->salt))
//	{
//		error_unexpected_on_key_generation();
//		return (FAIL);
//	}
	return (SUCCESS);
}

t_rsa_args	*take_rsa_args(int ac, char **av)
{
	int			i;
	t_rsa_args	*args;

	args = ft_safe_memalloc(sizeof(t_rsa_args), "take_rsa_args");
	i = 1;
//	while (++i < ac)
//		pars_args_rsa(ac, av, &i, args);
	return (args);
}