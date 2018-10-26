/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:33:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 15:46:18 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		print_symbol_x32(t_symbol *symbol)
{
	t_symbol *tmp;

	tmp = symbol;
	while (tmp != NULL)
	{
		if (tmp->value != 0)
			ft_printf("%08llx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%8s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}

t_section	*create_section_chunk_x32(struct section *section)
{
	t_section *new;

	if (!(new = (t_section*)malloc(sizeof(char) * sizeof(t_section))))
		return (NULL);
	new->segname = section->segname;
	new->sectname = section->sectname;
	new->addr = section->addr;
	new->offset = section->offset;
	new->size = section->size;
	new->next = NULL;
	return (new);
}

void	push_section_chunk_x32(struct section *chunk, t_section **section)
{
	t_section *tmp;

	if (*section == NULL)
		(*section) = create_section_chunk_x32(chunk);
	else
	{
		tmp = (*section);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x32(chunk);
	}
}

void	parse_segment_x32(t_binary *bin, unsigned int lc_offset)
{
	uint32_t				count;
	unsigned int			seg_offset;
	struct section			*section;
	struct segment_command	*segment;

	count = -1;
	segment = (struct segment_command*)((char*)bin->ptr + lc_offset);
	seg_offset = lc_offset + sizeof(*segment);
	while (++count < segment->nsects)
	{
		section = (struct section*)((char*)bin->ptr + seg_offset);
		push_section_chunk_x32(section, &bin->sect);
		seg_offset += sizeof(*section);
	}
}

void	parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char*) * sizeof(t_symbol))))
		return ;
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	push_symbol_chunk(new, &bin->sym);
}

void	parse_load_command_x32(t_binary *bin, unsigned int lc_offset)
{
	uint32_t				count;
	unsigned int			sym_offset;
	struct nlist			*list;
	struct symtab_command	*symtab;

	count = -1;
	symtab = (struct symtab_command*)((char*)bin->ptr + lc_offset);
	sym_offset = symtab->symoff;
	while (++count < symtab->nsyms)
	{
		list = (struct nlist*)((char*)bin->ptr + sym_offset);
		if (!(list->n_type & N_STAB))
			parse_symbol_x32(symtab, list, sym_offset, bin);
		sym_offset += sizeof(*list);
	}
}

int		handle_x32(t_binary *bin)
{
	uint32_t			count;
	struct mach_header	*header;
	unsigned int		lc_offset;
	struct load_command	*load_command;

	count = -1;
	header = (struct mach_header*)bin->ptr;
	bin->offset = sizeof(*header);
	lc_offset = bin->offset;
	while (++count < header->ncmds)
	{
		load_command = (struct load_command*)((char*)bin->ptr + lc_offset);
		if (load_command->cmd == LC_SEGMENT)
			parse_segment_x32(bin, lc_offset);
		else if (load_command->cmd == LC_SYMTAB)
			parse_load_command_x32(bin, lc_offset);
		lc_offset += load_command->cmdsize;
	}
//	print_section(bin->sect);
	print_symbol_x32(bin->sym);
	return (SUCCESS);
}
