/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 20:44:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM
# define NM

# include "libft.h"
# include "printf.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>

typedef struct				s_section
{
	uint32_t				offset;
	uint32_t				size;
	uint64_t				addr;
	void					*segname;
	void					*sectname;
	struct s_section		*next;
}							t_section;

typedef struct				s_symbol
{
	uint8_t					type;
	uint32_t				fileoff;
	uint64_t				value;
	void					*name;
	struct s_symbol			*next;
}							t_symbol;


typedef struct				t_binary
{
	unsigned int			opt;
	unsigned int			offset;
	char					*ptr;
	char					*path;
	t_symbol				*sym;
	t_section				*sect;
}							t_binary;

/* Return define */
# define ERROR 1
# define SUCCESS 0

/* Options define */

# define FLAG_A (1 << 0)
# define FLAG_n (1 << 1)
# define FLAG_o (1 << 2)
# define FLAG_p (1 << 3)
# define FLAG_r (1 << 4)
# define FLAG_u (1 << 5)
# define FLAG_U (1 << 6)
# define FLAG_m (1 << 7)
# define FLAG_x (1 << 8)
# define FLAG_j (1 << 9)
# define FLAG_t (1 << 10)

/* Errors define */
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
# define FLAG_UKW_STR2 "Try nm -h\n"

# define NM_USAGE "USAGE: nm [options] <input_files>\nOPTIONS: [...]\n"

/* main struct */
int						setup_struct(t_binary *fileinfo, struct stat *stat);
int						clean_struct(t_binary *fileinfo, struct stat stat);

/* x64 */
int						handle_x64(t_binary *bin);
void					parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, unsigned int offset, t_binary *bin);
void					push_section_chunk_x64(struct section_64 *chunk, t_section **section);

/* x32 */
int						handle_x32(t_binary *bin);
void					parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, unsigned int offset, t_binary *bin);
void					push_section_chunk_x32(struct section *chunk, t_section **section);

/* utils */
char					resolve_symbol_type(uint8_t n_type, uint8_t n_sect, t_binary *bin);
int						handle_error(const char *input, int type, const char *error);
int						handle_flags(t_binary *bin, char **av, int *count);

#endif
