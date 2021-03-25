/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_args_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:16:12 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/23 21:24:02 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void		set_additional_flag_rsa(int flag, t_rsa_args *args)
{
	if (flag == 11)
		args->modulus++;
	if (flag == 12)
		args->check++;
	if (flag == 13)
		args->pubin++;
	if (flag == 14)
		args->pubout++;
}

static void		set_flag_rsa(int flag, t_rsa_args *args)
{
	if (flag == 0)
		args->inform++;
	if (flag == 1)
		args->outform++;
	if (flag == 2 || flag == 3)
		args->in++;
	if (flag == 4)
		args->passin++;
	if (flag == 5 || flag == 6)
		args->out++;
	if (flag == 7)
		args->passout++;
	if (flag == 8)
		args->des++;
	if (flag == 9)
		args->text++;
	if (flag == 10)
		args->noout++;
	set_additional_flag_rsa(flag, args);
}

int				contains_rsa_arg(const char *args_table[],
		size_t table_size, char *str)
{
	size_t i;

	i = 0;
	while (i < table_size)
	{
		if (!ft_strcmp(args_table[i], str))
			return (i);
		i++;
	}
	return (-1);
}

static void		find_args_rsa(char *str, t_rsa_args *args)
{
	int flag;

	flag = contains_rsa_arg(g_rsa_flags, 15, str);
	if (flag >= 0)
		set_flag_rsa(flag, args);
	else
	{
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(str, ft_strlen(str) + 1));
	}
}

void			save_rsa_state(uint8_t saved_args[], t_rsa_args *args)
{
	saved_args[IN] = args->in;
	saved_args[OUT] = args->out;
	saved_args[PUBIN] = args->pubin;
	saved_args[PUBOUT] = args->pubout;
	saved_args[OUTFORM] = args->outform;
	saved_args[PASSOUT] = args->passout;
	saved_args[DES_RSA] = args->des;
	saved_args[TEXT] = args->text;
	saved_args[NOOUT] = args->noout;
	saved_args[MODULUS] = args->modulus;
	saved_args[CHECK] = args->check;
	saved_args[INFORM] = args->inform;
	saved_args[PASSIN] = args->outform;
}

void			pars_args_rsa(int ac, char **av,
		int *cur_position, t_rsa_args *args)
{
	uint8_t saved_args[13];

	save_rsa_state(saved_args, args);
	if (is_argums(av[*cur_position]))
	{
		find_args_rsa(&av[*cur_position][1], args);
		if ((saved_args[INFORM] < args->inform) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->in_form);
		else if ((saved_args[OUTFORM] < args->outform) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->out_form);
		else if ((saved_args[IN] < args->in) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->input_files);
		else if ((saved_args[OUT] < args->out) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->output_files);
		else if ((saved_args[PASSIN] < args->passin) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->pass_in);
		else if ((saved_args[PASSOUT] < args->passout) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->pass_out);
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_position],
						ft_strlen(av[*cur_position]) + 1));
}

t_rsa_args	*take_rsa_args(int ac, char **av)
{
	int			i;
	t_rsa_args	*args;

	args = ft_safe_memalloc(sizeof(t_rsa_args), "take_rsa_args");
	i = 1;
	while (++i < ac)
		pars_args_rsa(ac, av, &i, args);
	return (args);
}