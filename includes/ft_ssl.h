/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <gemerald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:17:46 by gemerald          #+#    #+#             */
/*   Updated: 2021/03/27 18:20:50 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "errors.h"
# include "printf.h"
# include "args.h"
# include "constants.h"
# include "output.h"

typedef struct	s_rsa_key
{
	uint32_t	version;
	uint64_t	modulus;
	uint32_t	public_exponent;
	uint64_t	private_exponent;
	uint32_t	prime1;
	uint32_t	prime2;
	uint32_t	exponent1;
	uint32_t	exponent2;
	uint32_t	coefficient;
}				t_rsa_key;

typedef struct	s_ext_euclid
{
	int64_t		y;
	int64_t		q;
	int64_t		r;
	int64_t		x1;
	int64_t		x2;
	int64_t		y1;
	int64_t		y2;

}				t_ext_euclid;

typedef struct	s_asn
{
	uint8_t		mem[16];
	uint8_t		size;
}				t_asn;

typedef struct	s_rsa_output
{
	t_list		*der;
	t_list		*pem;
	t_list		*salt_vector;
	t_list		*raw_key;
	t_list		*mem;
	t_list		*output_stream;
	uint8_t		is_private_key_found;
	t_rsa_key	key;
}				t_rsa_output;

t_rsa_key		gen_rsa_key_on_primes(uint32_t prime1,
					uint32_t prime2, uint32_t pub_e);
t_list			*get_priv_der_form(t_rsa_key *key);
t_list			*get_pub_der_form(t_rsa_key *key);
t_asn			convert_key_to_asn(void *mem, size_t size);
t_list			*collect_mem_to_output(t_asn asn[], size_t asn_size);
t_rsa_key		gen_rand_rsa(uint32_t pub_e);
int				rsa_priv_checker(t_rsa_key *key);
int				miller_rabin(uint32_t val, int k, uint8_t is_silent);
void			rsa_key_stream_write(int fd, t_list *key_der);
void			rsa_private_pem_des_writer(t_rsa_key *key, t_rsa_args *args);
int				contains_rsa_arg(const char *args_table[],
				size_t table_size, char *str);
int				get_out_fd(t_rsa_args *args);
int				cut_start_end(t_list **pem, size_t diff, size_t off);
int				rsa_priv_checker(t_rsa_key *key);
t_rsa_key		convert_der_to_pub_key(t_list *der);
int				rsa_pub_checker(t_list *pub_key);

void			*ft_safe_memalloc(size_t size, char *function_name);
void			ft_mem_copy(void *dest, void *src, size_t size);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*buffered_reader(int fd);
t_list			*buffered_file_reader(t_list *filenames);
uint8_t			hex_char_to_byte(uint8_t *str);
void			pbkfd(t_des_args *args, t_key_vector *key_vector);

void			split_by_commands(int ac, char **av);

void			print_hex(uint8_t *mem, size_t size, int fd);
void			print_algo(t_args *args);
void			print_stdin(t_args *args, t_output *output);
void			print_strings_and_files(t_args *args, t_output *output);
void			print_output_cipher(t_base64_args *args, t_output *output);

uint32_t		rotate_left(uint32_t left, uint32_t right);
t_list			*append_mem_len(void *to_hash_mem,
					size_t to_hash_size, size_t mod_len);
void			fill_chunk_512(uint32_t *chunk, uint8_t *mem);
void			take_byte_from_int(uint8_t *mem, uint32_t val);
uint32_t		take_int_from_byte(uint8_t *mem);
uint64_t		ft_swap64(uint64_t val);
uint64_t		take_uint64_from_uint8(uint8_t *mem);
void			take_byte_from_int_sha512(uint8_t *mem, uint64_t val);
void			convert64t_mem(uint8_t *dest, uint64_t *mem,
					size_t size_in_byte);

void			entrance_to_hash(t_args *args);
t_list			*sha256(void *mem, size_t size);
t_list			*md5(void *to_hash_mem, size_t to_hash_size);
t_list			*sha512(void *to_hash_mem, size_t to_hash_size);

void			entrance_to_base64(t_base64_args *args);

t_list			*base64_enc(void *mem, size_t size);
t_list			*base64_dec(void *mem, size_t size);

uint64_t		pure_des_encrypt(uint64_t mem, uint64_t keys[]);
uint64_t		pure_des_decrypt(uint64_t mem, uint64_t keys[]);
uint64_t		pure_des3_ede_encrypt(uint64_t mem, uint64_t keys[]);
uint64_t		pure_des3_ede_decrypt(uint64_t mem, uint64_t keys[]);

void			des_ecb(uint64_t *mem, size_t size, t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			des_cbc_enc(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));
void			des_cbc_dec(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			des_pcbc_enc(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));
void			des_pcbc_dec(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			des_cfb_enc(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));
void			des_cfb_dec(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			des_ofb_enc(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));
void			des_ofb_dec(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			des_ctr_enc(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));
void			des_ctr_dec(uint64_t *mem, size_t size,
				t_key_vector *key_vector,
				uint64_t (*cipher)(uint64_t, uint64_t *));

void			entrance_to_des(t_des_args *args);
t_list			*general_cipher(void *mem, size_t size, t_des_args *args);
t_list			*get_pass_stdin(void);
t_key_vector	init_key_vector(t_des_args *args);
t_list			*get_random_bytes(void);
void			fill_random_values(t_des_args *args);
void			get_salt_from_content(t_des_args *args, t_crypt_output *output);

void			split_on_rsa(t_cmd_type cmd, int ac, char **av);
void			entrance_to_rsa(t_rsa_args *args);
void			entrance_to_rsa_utl(t_rsa_args *args);
void			entrance_to_gen_rsa(t_rsa_args *args);

void			print_output(t_args *args, t_output *output);
void			ft_print_by_size(char *str, size_t size, int fd);
void			print_silent_files(t_list *tmp, t_list *stream);
void			print_output_des(t_des_args *args, t_crypt_output *output);
void			print_base64_stdout(int fd, uint8_t *mem, size_t size);

void			free_output(t_output *output);
void			free_list(void *mem, size_t size);
void			ft_del_simple_list(t_list **begin);
void			print_hex_dump(t_list *mem, int fd);
void			get_pem_priv_form(t_rsa_args *args, t_rsa_output *out);
void			get_pem_pub_form(t_rsa_args *args, t_rsa_output *out);
void			rsa_pem_writer(t_rsa_args *args, t_rsa_output *out, int fd);
void			rsa_public_pem_writer(t_rsa_args *args, t_rsa_output *out);
void			free_rsa_out(t_rsa_output *output);
void			free_rsa_args(t_rsa_args **args);
void			key_text_print(t_rsa_args *args, t_rsa_output *out, int fd);
void			modulus_print(t_rsa_output *out, int fd);
int				raw_key_convert_to_rsa_key(t_rsa_args *args,
				t_rsa_output *output);
void			get_8byte_from_ascii(t_list *ascii);
int				des_showing(t_rsa_args *args, t_rsa_output *out);
t_rsa_key		convert_der_to_priv_key(t_list *der);
int				read_pem_form(t_list *pem, t_rsa_output *out);
int				des_hiding(t_rsa_args *args, t_rsa_output *out);
int				get_key_from_user(t_rsa_args *args, t_rsa_output *output);
uint64_t		get_pow_remainder(uint64_t x, uint64_t pow, uint64_t mod);
int				rsa_process(t_rsa_args *args, t_rsa_output *out);

#endif
