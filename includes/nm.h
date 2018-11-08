/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 21:04:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "libft.h"
# include "printf.h"

# include <ar.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>

typedef struct			s_section
{
	uint32_t			offset;
	uint32_t			size;
	uint64_t			addr;
	void				*segname;
	void				*sectname;
	struct s_section	*next;
}						t_section;

typedef struct			s_symbol
{
	uint8_t				type;
	uint32_t			fileoff;
	uint64_t			value;
	void				*name;
	struct s_symbol		*next;
}						t_symbol;

typedef struct			s_binary
{
	int					endian;
	unsigned long		opt;
	unsigned long		offset;
	char				*ptr;
	char				*path;
	t_symbol			*sym;
	t_section			*sect;
}						t_binary;

/*
** Return define
*/
# define ERROR 1
# define FLAG_ERROR 2
# define SUCCESS 0

/*
** Endian define
*/
# define LTL_END 1
# define BIG_END 0

/*
**  Options define
**	U : uppercase
**	L : lowercase
**	P : print
*/
# define FLAG_UA (1 << 0)
# define FLAG_LN (1 << 1)
# define FLAG_LP (1 << 2)
# define FLAG_LR (1 << 3)
# define FLAG_LU (1 << 4)
# define FLAG_UU (1 << 5)
# define FLAG_LM (1 << 6)
# define FLAG_LX (1 << 7)
# define FLAG_LJ (1 << 8)
# define FLAG_LT (1 << 9)
# define FLAG_NO_FILE (1 << 10)
# define FLAG_MULT_FILE (1 << 11)
# define FLAG_ENDIAN (1 << 12)

/*
** Errors define
*/
# define IS_DIR	1
# define ERR_DIR_STR "Is a directory."

# define NOT_ALLOWED 2
# define ERR_DIR_NA "Permission denied."

# define FSTAT_ERR 3
# define FSTAT_ERR_STR "fstat failed, abort."

# define MMAP_ERR 4
# define MMAP_ERR_STR "mmap error: can't allocate ressources to load given binary."

# define MUNMAP_ERR 5
# define MUNMAPP_ERR_STR "error: can't deallocate given binary"

# define FLAG_UKW 6
# define FLAG_UKW_STR "Unknown command line argument"
# define FLAG_UKW_STR2 "Try ./ft_nm -h"

# define DOUBLE_FLAG_ERR 7
# define DOUBLE_FLAG_ERR_STR "may only occur zero or one times!"

# define NM_USAGE "USAGE: ./ft_nm [options] <input_files>\nOPTIONS: [...]\n"

/*
** main struct
*/
int						setup_struct(t_binary *fileinfo, struct stat *stat);
int						clean_struct(t_binary *fileinfo, struct stat stat);
int						handle_arch(t_binary *bin, struct stat stat);

/*
** x64
*/
int						handle_x64(t_binary *bin, struct stat stat);
int						parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, t_binary *bin, struct stat stat);
void					push_section_chunk_x64(int endian, struct section_64 *chunk, t_section **section);

/*
** x32
*/
int						handle_x32(t_binary *bin, struct stat stat);
int						parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, t_binary *bin, struct stat stat);
void					push_section_chunk_x32(int endian, struct section *chunk, t_section **section);

/*
** library
*/
int						handle_library(t_binary *bin, struct stat stat);

/*
**
*/
int						handle_fat(t_binary *bin, struct stat stat);

/*
** utils
*/
uint32_t				reverse(int32_t x);
char					resolve_symbol_type(uint8_t n_type, uint8_t n_sect, uint8_t n_value, t_binary *bin);
int						handle_error(const char *input, int type, const char *error);
int						search_for_flags(t_binary *bin, char **av, int count);
void					free_sect(t_section **section);
void					free_sym(t_symbol **symbol);

/*
** Endianness and offset
*/
void					*move_ptr(t_binary *bin, struct stat stat, uint32_t size);
uint16_t        		reverse_16(int endian, uint16_t x);
uint32_t        		reverse_32(int endian, uint32_t x);
uint64_t        		reverse_64(int endian, uint64_t x);

#endif
