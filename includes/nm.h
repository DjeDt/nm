/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 16:12:34 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM
# define NM

# include "libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include "printf.h"

# define ERROR -1
# define SUCCESS 0

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
	unsigned int			offset;
	char					*ptr;
	t_symbol				*sym;
	t_section				*sect;
}							t_binary;

/* main struct */
int							setup_struct(t_binary *fileinfo, const char *path, int fd, struct stat *stat);
int							clean_struct(t_binary *fileinfo, struct stat stat);

/* x64 */
int							handle_x64(t_binary *bin);
void						parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, unsigned int offset, t_binary *bin);

/* x32 */
int							handle_x32(t_binary *bin);
void						parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, unsigned int offset, t_binary *bin);

/* utils */
char						resolve_symbol_type(uint8_t n_type, uint8_t n_sect, t_binary *bin);


#endif
