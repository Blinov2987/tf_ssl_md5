/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:10:03 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/27 20:55:39 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_argums(char *av)
{
	if (ft_strlen(av) < 2)
		return (FALSE);
	if (av[0] == '-')
		return (TRUE);
	return (FALSE);
}

void	pars_args(int ac, char **av, int *cur_position, t_args *args)
{
	uint8_t current_strings;

	current_strings = args->flag_s;
	if (is_argums(av[*cur_position]))
	{
		find_args(&av[*cur_position][1], args);
		if ((current_strings < args->flag_s) && *cur_position < (ac - 1))
		{
			(*cur_position)++;
			ft_lstadd_back(&args->strings,
					ft_lstnew(av[*cur_position],
						ft_strlen(av[*cur_position]) + 1));
		}
	}
	else
		ft_lstadd_back(&args->filenames,
				ft_lstnew(av[*cur_position], ft_strlen(av[*cur_position]) + 1));
}

t_args	*take_args(int ac, char **av)
{
	int		i;
	t_args	*args;

	if (!(args = ft_safe_memalloc(sizeof(t_args), "take_args")))
		return (NULL);
	if (ac < 2)
	{
		print_usage();
		free(args);
		return (NULL);
	}
	if (!take_command(av[1], args))
	{
		print_incorrect_command(av[1]);
		free(args);
		return (NULL);
	}
	i = 1;
	while (++i < ac)
	{
		pars_args(ac, av, &i, args);
	}
	return (args);
}

void	decrease_string_size(t_list *list)
{
	t_list *tmp;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		if (tmp->content_size)
			tmp->content_size -= 1;
		tmp = tmp->next;
	}
}

int		validate_args(t_args **args)
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
