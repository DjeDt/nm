/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:33:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/07 12:18:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_symbol_x32(t_binary *bin)
{
	t_symbol *tmp;

	tmp = bin->sym;
	if (bin->opt & FLAG_MULT_FILE)
		ft_printf("\n%s:\n", bin->path);
	while (tmp != NULL)
	{
		if (tmp->type != 'U')
			ft_printf("%08lx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%8s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}

static void	parse_segment_x32(t_binary *bin, unsigned int lc_offset)
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

static void	parse_load_command_x32(t_binary *bin, unsigned int lc_offset)
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

int			handle_x32(t_binary *bin)
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
	print_symbol_x32(bin);
	free_sect(&bin->sect);
	free_sym(&bin->sym);
	return (SUCCESS);
}
