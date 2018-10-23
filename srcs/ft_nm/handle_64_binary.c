/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:46:43 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/23 19:46:36 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_specific_64(t_binary *fileinfo)
{
	ft_putendl("specific 64 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}

void	browse_symtab(t_symbol_64 symbol, t_segment_64 *seg_list, t_binary *fileinfo)
{
	char c;
	size_t count;
	t_sym *new;
	uint8_t type;

	count = 0;
	while (count < symbol.symtab->nsyms)
	{
		type = symbol.el[count].n_type;
		if ((type & N_TYPE) == N_UNDF)
			c = 'U';
		else if ((type & N_TYPE) == N_ABS)
			c = 'A';
		else if ((type & N_TYPE) == N_SECT)
			c = search_specific_section_64(seg_list, symbol.el[count].n_sect);
		else if ((type & N_TYPE) == N_PBUD)
			c = 'U';
		else if ((type & N_TYPE) == N_INDR)
			c = 'I';
		if (!(type & N_EXT))
			c = ft_tolower(c);
		if (symbol.el[count].n_value == 0)
			new = new_chunk(symbol.str + symbol.el[count].n_un.n_strx, 0, c);
		else
			new = new_chunk(symbol.str + symbol.el[count].n_un.n_strx, symbol.el[count].n_value, c);
		(void)fileinfo;
		push_chunk(new, &sym, ft_strcmp);
		count++;
	}
}

void	print_symbol_64(struct load_command *load_command, struct mach_header_64 *header, t_binary *fileinfo, t_segment_64 *seg_list)
{
	t_symbol_64		symbol;


	symbol.symtab = get_symbol_table_64(load_command);
	symbol.el = get_elem_list_64(header, symbol.symtab);
	symbol.str = get_symbol_offset_64(header, symbol.symtab);
	browse_symtab(symbol, seg_list, fileinfo);
}


t_segment_64	*create_new_segment_chunk(struct segment_command_64 *segment)
{
	t_segment_64 *new;

	new = (t_segment_64*)malloc(sizeof(char) * sizeof(struct s_segment_64));
	if (new == NULL)
		return (NULL);
	new->segment = segment;
	new->next = NULL;
	return (new);
}

void	push_this_segment(struct load_command *load_command, t_segment_64 **seg_list)
{
	t_segment_64				*tmp;
	struct segment_command_64	*segment;

	segment = get_segment_64(load_command);
	if (*seg_list == NULL)
		(*seg_list) = create_new_segment_chunk(segment);
	else
	{
		tmp = (*seg_list);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_new_segment_chunk(segment);
	}
}

int		handle_64(t_binary *fileinfo)
{
	unsigned int			count;
	struct mach_header_64	*header;
	struct load_command		*load_command;
	t_segment_64			*seg_list;

	count = 0;
	seg_list = NULL;
	header = get_header_64(fileinfo->ptr);
	load_command = get_load_command_64(header, fileinfo);
	while (count++ < header->ncmds)
	{
		if (load_command->cmd == LC_SEGMENT_64)
			push_this_segment(load_command, &seg_list);
		if (load_command->cmd == LC_SYMTAB)
		{
			print_symbol_64(load_command, header, fileinfo, seg_list);
			break;
		}
		load_command = next_load_command(load_command, fileinfo);
	}
	print_data();
	header = NULL;
	load_command = NULL;
	return (SUCCESS);
}
