/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:56:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 19:06:49 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm_32.h"

int		handle_specific_32(t_binary fileinfo)
{
	ft_putendl("specific 32 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}

void browse_symtab_32(t_symbol symbol, t_segment *seg_list, t_binary *fileinfo)
{
	char c;
	size_t count;
	t_sym *new;
	uint8_t type;

	count = -1;
	while (++count < symbol.symtab->nsyms)
	{
		(void)fileinfo;
		type = symbol.el[count].n_type;
		if ((type & N_TYPE) == N_UNDF)
			c = 'U';
		else if ((type & N_TYPE) == N_ABS)
			c = 'A';
		else if ((type & N_TYPE) == N_SECT)
			c = search_specific_section_32(seg_list, symbol.el[count].n_sect);
		else if ((type & N_TYPE) == N_PBUD)
			c = 'U';
		else if ((type & N_TYPE) == N_INDR)
			c = 'I';
		if (!(type & N_EXT))
			c = ft_tolower(c);
//		printf("symbol name = %s\n", symbol.str + symbol.el[count].n_un.n_strx);
//		if (c != '?' || ft_strlen(symbol.str + symbol.el[count].n_un.n_strx) != 0)
//		{
			if (symbol.el[count].n_value == 0)
				new = new_chunk(symbol.str + symbol.el[count].n_un.n_strx, 0, c);
			else
				new = new_chunk(symbol.str + symbol.el[count].n_un.n_strx, symbol.el[count].n_value, c);
			push_chunk(new, &sym, ft_strcmp);
//		}
	}
//	printf("entry : %zu\n", count);
}

void print_symbol_32(struct load_command *load_command, struct mach_header *header, t_binary *fileinfo, t_segment *seg_list)
{
	t_symbol symbol;

	symbol.symtab = get_symbol_table(load_command);
	symbol.el = get_elem_list_32(header, symbol.symtab);
	symbol.str = get_symbol_offset_32(header, symbol.symtab);


	browse_symtab_32(symbol, seg_list, fileinfo);
}


t_segment    *create_new_segment_chunk_32(struct segment_command *segment)
{
	t_segment *new;

	new = (t_segment*)malloc(sizeof(char) * sizeof(struct s_segment));
	if (new == NULL)
		return (NULL);
	new->segment = segment;
	new->next = NULL;
	return (new);
}

void    push_this_segment_32(struct load_command *load_command, t_segment **seg_list)
{
	t_segment                *tmp;
	struct segment_command   *segment;

	segment = get_segment_32(load_command);
	if (*seg_list == NULL)
		(*seg_list) = create_new_segment_chunk_32(segment);
	else
	{
		tmp = (*seg_list);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_new_segment_chunk_32(segment);
	}
}

int		handle_32(t_binary *fileinfo)
{
	uint32_t			count;
	struct mach_header	*header;
	struct load_command *load_command;
	t_segment			*seg_list;

	count = 0;
	seg_list = NULL;
	header = get_header_32(fileinfo->ptr);
	load_command = get_load_command_32(header);
	while (count++ < header->ncmds)
	{
		load_command = next_load_command(load_command, fileinfo);
		if (load_command->cmd == LC_SEGMENT)
			push_this_segment_32(load_command, &seg_list);
		else if (load_command->cmd == LC_SYMTAB)
		{
			print_symbol_32(load_command, header, fileinfo, seg_list);
			break ;
		}
	}
	print_data_32();
	return (SUCCESS);
}
