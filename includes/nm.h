/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/12 19:13:00 by ddinaut          ###   ########.fr       */
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

# define ERROR -1
# define SUCCESS 0

/* typedef struct				s_metadata */
/* { */

/* }							t_metadata; */

typedef struct				s_info
{
	struct mach_header_64	*header;
	struct load_command		*load_command;
}							t_info;

typedef struct				t_binary
{
	int						fd;
	char					*ptr;
	struct stat				input;
}							t_binary;

# define HEX "0123456789abcdef"

/* main struct */
int							setup_struct(t_binary *fileinfo, const char *path);
int							clean_struct(t_binary *fileinfo);

/* handle 64 */
int							handle_64(t_binary fileinfo);
int							handle_specific_64(t_binary fileinfo);

/* handle 32 */
int							handle_32(t_binary fileinfo);
int							handle_specific_32(t_binary fileinfo);

/* utils */
void						ft_puthex(unsigned long l);

/* lib */
unsigned int				get_magic_number(void *data_file);
struct mach_header			*get_header_32(void *data_file);
struct mach_header_64		*get_header_64(void *data_file);
struct load_command			*get_load_command_64(struct mach_header_64 *header);
struct load_command			*get_load_command_32(struct mach_header *header);
struct load_command			*next_load_command(struct load_command *load_command);
struct symtab_command		*get_symbol_table_64(struct load_command *load_command);
struct nlist_64				*get_elem_list_64(struct mach_header_64 *header, struct symtab_command *symbols);
char						*get_symbol_name_64(struct mach_header_64 *header, struct symtab_command *symbols);
struct segment_command_64	*get_segment_64(struct load_command *load_command);
struct section_64			*get_section_64(struct segment_command_64 *segment);
struct section_64			*get_next_section_64(struct section_64 *section);

void                        parse_symbol_elem(struct nlist_64 el);

#endif
