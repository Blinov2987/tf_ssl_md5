/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:08:53 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/24 19:11:03 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

void		get_pem_priv_form(t_rsa_args *args, t_rsa_output *out)
{
	ft_lstadd_back(&out->pem, ft_lstnew(RSA_PRIV_START,
			ft_strlen(RSA_PRIV_START) + 1));
	out->der = get_priv_der_form(&out->key);
	if (args->des)
	{
		ft_lstadd_back(&out->pem, ft_lstnew(PROC_TYPE,
				ft_strlen(PROC_TYPE) + 1));
		ft_lstadd_back(&out->pem, ft_lstnew(DEK_INFO, ft_strlen(DEK_INFO) + 1));
		ft_lstadd_back(&out->pem, out->der->next);
		out->der = des_hiding(out->der);
	}
	ft_lstadd_back(&out->pem, base64_enc(out->der->content,out->der->content_size));
	ft_lstadd_back(&out->pem, ft_lstnew(RSA_PRIV_END,
			ft_strlen(RSA_PRIV_END) + 1));
}

void		get_pem_pub_form(t_rsa_args *args, t_rsa_output *out)
{
	ft_lstadd_back(&out->pem, ft_lstnew(RSA_PUB_START,
			ft_strlen(RSA_PUB_START) + 1));
	out->der = get_priv_der_form(&out->key);
	if (args->des)
	{
		ft_lstadd_back(&out->pem, ft_lstnew(PROC_TYPE,
				ft_strlen(PROC_TYPE) + 1));
		ft_lstadd_back(&out->pem, ft_lstnew(DEK_INFO, ft_strlen(DEK_INFO) + 1));
		ft_lstadd_back(&out->pem, out->der->next);
		out->der = des_hiding(out->der);
	}
	ft_lstadd_back(&out->pem, base64_enc(out->der->content,out->der->content_size));
	ft_lstadd_back(&out->pem, ft_lstnew(RSA_PUB_END,
			ft_strlen(RSA_PUB_END) + 1));
}