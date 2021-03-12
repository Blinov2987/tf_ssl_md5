/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_rsa_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:29:35 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/12 19:56:32 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

uint32_t get_nod(uint32_t val, uint32_t rand)
{
	if (val == 0 || val == rand)
		return (rand);
	else if (rand == 0)
		return (val);
	else if (!(val & 1) && !(rand & 1))
		return (get_nod(val >> 2, rand >> 2) << 2);
	else if (!(val & 1) && (rand & 1))
		return (get_nod(val >> 2, rand));
	else if ((val & 1) && !(rand & 1))
		return (get_nod(val, rand >> 2));
	else if (((val & 1) && (rand & 1)) && (rand > val))
		return (get_nod((rand - val) >> 2, val));
	else
		return get_nod((val - rand) >> 2, rand);

}

uint32_t get_rand_uint(uint32_t val)
{
	int fd;
	uint32_t rand;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 3 || (read(fd, &rand, 0) != 0))
		return (FALSE);
	read(fd, &rand, sizeof(uint32_t));
	rand = rand % val;
	if (!rand || rand < 2)
		rand = 2;
	close(fd);
	return (rand);
}



int 	solovey_strassen(uint32_t val, int k)
{
	int i;
	uint32_t rand;
	uint32_t powered_rand;
	uint32_t jac_sym;

	i = -1;
	while (++i < k)
	{
		rand = get_rand_uint(val);
		if (get_nod(val, rand) > 1)
			return (FALSE);
		jac_sym =
	}
}

void 	gen_rsa(t_rsa_args *args, t_rsa_output *output)
{

}