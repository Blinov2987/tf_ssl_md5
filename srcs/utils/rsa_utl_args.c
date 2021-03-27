/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_utl_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:24:09 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/23 21:24:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static void		set_flag_rsa_utl(int flag, t_rsa_args *args)
{
	if (flag == 0 || flag == 1)
		args->in++;
	if (flag == 2 || flag == 3)
		args->out++;
	if (flag == 4)
		args->pubin++;
	if (flag == 5)
		args->inkey++;
	if (flag == 6)
		args->encrypt++;
	if (flag == 7)
		args->decrypt++;
	if (flag == 8)
		args->hexdump++;
}

static void		find_args_rsa_utl(char *str, t_rsa_args *args)
{
	int flag;

	flag = contains_rsa_arg(g_rsa_utl_flags, 9, str);
	if (flag >= 0)
		set_flag_rsa_utl(flag, args);
	else
	{
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(str, ft_strlen(str) + 1));
	}
}

void			save_rsa_utl_state(uint8_t saved_args[], t_rsa_args *args)
{
	saved_args[IN] = args->in;
	saved_args[OUT] = args->out;
	saved_args[PUBIN] = args->pubin;
	saved_args[INKEY] = args->inkey;
	saved_args[ENCRYPT] = args->encrypt;
	saved_args[DECRYPT_UTL] = args->decrypt;
	saved_args[HEXDUMP] = args->hexdump;
}

void			pars_args_rsa_utl(int ac, char **av,
		int *cur_position, t_rsa_args *args)
{
	uint8_t saved_args[7];

	save_rsa_utl_state(saved_args, args);
	if (is_argums(av[*cur_position]))
	{
		find_args_rsa_utl(&av[*cur_position][1], args);
		if ((saved_args[IN] < args->in) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->input_files);
		else if ((saved_args[OUT] < args->out) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->output_files);
		else if ((saved_args[INKEY] < args->inkey) && *cur_position < (ac - 1))
			add_to_args_list(av, cur_position, &args->in_key);
	}
	else
		ft_lstadd_back(&args->bad_argums,
				ft_lstnew(av[*cur_position],
						ft_strlen(av[*cur_position]) + 1));
}

t_rsa_args		*take_rsa_utl_args(int ac, char **av)
{
	int			i;
	t_rsa_args	*args;

	args = ft_safe_memalloc(sizeof(t_rsa_args), "take_rsa_utl_args");
	i = 1;
	while (++i < ac)
		pars_args_rsa_utl(ac, av, &i, args);
	return (args);
}
