/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:53:17 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:59:43 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_32
# define NM_32

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

typedef struct				s_sym
{
	char					sym_type;
	void					*sym_name;
	unsigned long			sym_value;
	struct s_sym			*next;
}							t_sym;

typedef struct				s_symbol
{
	struct symtab_command	*symtab;
	struct nlist			*el;
	char					*str;
}							t_symbol;

typedef struct					s_segment
{
	struct segment_command		*segment;
	struct s_segment			*next;
}								t_segment;

typedef struct				t_binary
{
	int						fd;
	unsigned int			offset;
	char					*ptr;
	struct stat				input;
}							t_binary;

# define HEX "0123456789abcdef"

t_sym *sym;


/* utils */
void						ft_puthex(unsigned long l);
int							check_offset();

/* lib */
unsigned int				get_magic_number(void *data_file);
struct mach_header			*get_header_32(void *data_file);
struct segment_command		*get_segment_32(struct load_command *load_command);
t_segment					*create_new_segment_chunk_32(struct segment_command *segment);
void						push_this_segment_32(struct load_command *load_command, t_segment **seg_list);
struct load_command			*get_load_command_32(struct mach_header *header);
struct load_command			*next_load_command(struct load_command *load_command, t_binary *fileinfo);
struct symtab_command		*get_symbol_table(struct load_command *load_command);
struct nlist				*get_elem_list_32(struct mach_header *header, struct symtab_command *symbols);
char						*get_symbol_offset_32(struct mach_header *header, struct symtab_command *symbols);
struct section				*get_section_32(struct segment_command *segment);
struct section				*get_next_section_32(struct section *section);
char						search_specific_section_32(t_segment *segment, uint8_t offset);

/*
** list func
*/
void						print_data_32(void);
void						push_chunk(t_sym *new, t_sym **head, int sort_func(const char *s1 ,const char *s2));
t_sym						*new_chunk(void *sym_name, unsigned long sym_value, char type);

#endif
