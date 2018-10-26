/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 15:43:30 by ddinaut          ###   ########.fr       */
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

/* typedef struct				s_sym */
/* { */
/* 	char					sym_type; */
/* 	void					*sym_name; */
/* 	unsigned long			sym_value; */
/* 	struct s_sym			*next; */
/* }							t_sym; */

/* typedef struct				s_symbol_64 */
/* { */
/* 	struct symtab_command	*symtab; */
/* 	struct nlist_64			*el; */
/* 	char					*str; */
/* }							t_symbol_64; */

/* typedef struct				s_segment_64 */
/* { */
/* 	struct segment_command_64		*segment; */
/* 	struct s_segment_64		*next; */
/* }							t_segment_64; */


/* typedef struct				s_segment */
/* { */
/* 	void					*segment; */
/* 	struct s_segment		*next; */
/* }							t_segment; */

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

# define HEX "0123456789abcdef"

//t_sym *sym;

/* main struct */
/* int							setup_struct(t_binary *fileinfo, const char *path); */
/* int							clean_struct(t_binary *fileinfo); */
int							setup_struct(t_binary *fileinfo, const char *path, int fd, struct stat *stat);
int							clean_struct(t_binary *fileinfo, struct stat stat);

/* handle 64 */
/* int							handle_64(t_binary *fileinfo); */
/* int							handle_specific_64(t_binary *fileinfo); */

/* /\* handle 32 *\/ */
/* int							handle_32(t_binary *fileinfo); */
/* int							handle_specific_32(t_binary *fileinfo); */

/* /\* utils *\/ */
/* void						ft_puthex(unsigned long l); */
/* int							check_offset(); */


/* lib */
/* unsigned int				get_magic_number(void *data_file); */
/* struct mach_header			*get_header_32(void *data_file); */
/* struct mach_header_64		*get_header_64(void *data_file); */

/* struct load_command			*get_load_command_64(struct mach_header_64 *header, t_binary *fileinfo); */
/* struct load_command			*get_load_command_32(struct mach_header *header); */
/* struct load_command			*next_load_command(struct load_command *load_command, t_binary *fileinfo); */

/* struct symtab_command		*get_symbol_table(struct load_command *load_command); */
/* struct nlist_64				*get_elem_list_64(struct mach_header_64 *header, struct symtab_command *symbols); */
/* struct nlist_64				*next_elem_list_64(struct nlist_64 *el); */
/* char						*get_symbol_offset_64(struct mach_header_64 *header, struct symtab_command *symbols); */

/* struct segment_command_64	*get_segment_64(struct load_command *load_command); */
/* struct segment_command_64	*get_specific_segment_64(struct load_command *lc, const char *needle); */
/* void						print_segment_64_info(struct segment_command_64 *segment, void *ptr, unsigned int count); */

/* struct section_64			*get_section_64(struct segment_command_64 *segment); */
/* struct section_64			*get_next_section_64(struct section_64 *section); */
/* struct section_64			*get_specific_section_64(struct segment_command_64 *segment, const char *needle); */
/* char                        search_specific_section_64(t_segment_64 *segment, uint8_t offset); */

/* void                        print_section_64_info(struct section_64 *section, unsigned int *offset, t_binary *fileinfo); */

/* char                        parse_symbol_elem(struct nlist_64 el); */
/* char                        parse_symbol_elem2(uint8_t type); */

/* /\* */
/* ** list func */
/* *\/ */
/* void						print_data_64(void); */
/* void						push_chunk(t_sym *new, t_sym **head, int sort_func(const char *s1 ,const char *s2)); */
/* t_sym						*new_chunk(void *sym_name, unsigned long sym_value, char type); */

/* -------------------------*/
/* x64 */
int		handle_x64(t_binary *bin);
//void	print_section(t_section *section);

/* x32 */
int		handle_x32(t_binary *bin);

/* utils */
char	resolve_symbol_type(uint8_t n_type, uint8_t n_sect, t_binary *bin);
void    push_symbol_chunk(t_symbol *new, t_symbol **symbol);


#endif
