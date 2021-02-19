/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:51:38 by gemerald          #+#    #+#             */
/*   Updated: 2021/01/29 18:59:11 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_CONSTANTS_H
# define NM_CONSTANTS_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAIL 0
# define HASHING_COMMAND 1
# define MD5 1
# define SHA256 2
# define SHA512 3
# define BASE64_COMMAND 2
# define DES_COMMAND 3
# define DES3_COMMAND 4
# define ECB 1
# define CBC 2
# define PCBC 3
# define OFB 4
# define CFB 5
# define CTR 6

# define HASHING_FLAGS "pqrs"
# define BASE64_FLAGS "deio"
# define DES_FLAGS "adeikopsv"
# define USAGE_STRING "usage: ft_ssl command [command opts] [command args]"
# define STD_COMMANDS "Standard commands:\n"
# define DIGEST_COMMANDS "Message Digest commands:\nmd5\nsha256\nsha512\n"
# define CIPHER_COMMANDS "Cipher commands:\nbase64"

#endif
