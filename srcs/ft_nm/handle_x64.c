/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:08:36 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 15:39:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

void print_section(t_section *section)
{
	t_section *tmp;

	tmp = section;
	while (tmp != NULL)
	{
		ft_printf("segname = %s\nsectname = %s\naddr = %llu\noffset = %u\nsize = %u\n\n",
			   tmp->segname , \
			   tmp->sectname, \
			   tmp->addr, \
			   tmp->offset, \
			   tmp->size);
		tmp = tmp->next;
	}
}

void	print_symbol(t_symbol *symbol)
{
	t_symbol *tmp;

	tmp = symbol;
	while (tmp)
	{
		ft_printf("name: %s\ntype: %c\noffset: %u\nvalue: %llu\n",
			   tmp->name,\
			   tmp->type,\
			   tmp->fileoff,\
			   tmp->value);
		tmp = tmp->next;
	}
}

void	print_symbol_x64(t_symbol *symbol)
{
	t_symbol *tmp;

	tmp = symbol;
	while (tmp != NULL)
	{
		if (tmp->value != 0)
			ft_printf("%016llx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%16s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}

t_section	*create_section_chunk_x64(struct section_64 *section)
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

void		push_section_chunk_x64(struct section_64 *chunk, t_section **section)
{
	t_section *tmp;

	if (*section == NULL)
		(*section) = create_section_chunk_x64(chunk);
	else
	{
		tmp = (*section);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x64(chunk);
	}
}

void	parse_segment_x64(t_binary *bin, unsigned int lc_offset)
{
	uint32_t					count;
	unsigned int				seg_offset;
	struct section_64			*section;
	struct segment_command_64	*segment;

	count = -1;
	segment = (struct segment_command_64*)((char*)bin->ptr + lc_offset);
	seg_offset = lc_offset + sizeof(*segment);

	while (++count < segment->nsects)
	{
		section = (struct section_64*)((char*)bin->ptr + seg_offset);
		push_section_chunk_x64(section, &bin->sect);
		seg_offset += sizeof(*section);
	}
}

void	push_symbol_chunk(t_symbol *new, t_symbol **symbol)
{
	t_symbol *tmp;

	if (!new)
		return ;
	if ((*symbol) == NULL || ft_strcmp((*symbol)->name, new->name) >= 0)
	{
		new->next = (*symbol);
		(*symbol) = new;
	}
	else
	{
		tmp = (*symbol);
		while (tmp->next != NULL && ft_strcmp(tmp->next->name, new->name) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

//char	resolve_type_from_section(struct nlist_64 *list, t_binary *bin)
char	resolve_type_from_section(uint32_t n_sect, t_binary *bin)
{
	uint32_t	count;
	t_section	*sect;

	count = 0;
	sect = bin->sect;
	while (sect != NULL && ++count != n_sect)
		sect = sect->next;
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		return ('T');
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
		return ('D');
	else if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
		return ('B');
	return ('S');
}

//char	resolve_symbol_type(struct nlist_64 *list, t_binary *bin)
char	resolve_symbol_type(uint8_t n_type, uint8_t n_sect, t_binary *bin)
{
	char	c;
	uint8_t	type;

/*	c = '?';
	type = list->n_type & N_TYPE;
	if (list->n_type & N_STAB)
		c = '-';
	else if (type == N_UNDF)
		c = 'U';
	else if (type == N_ABS)
		c = 'A';
	else if (type == N_SECT)
		c = resolve_type_from_section(list, bin);
	else if (type == N_PBUD)
		type = 'U';
	else if (type == N_INDR)
		c = 'I';
	if (!(list->n_type & N_EXT) && (list->n_type != '?'))
		c = ft_tolower(c);
*/
	type = n_type & N_TYPE;
	if (n_type & N_STAB)
		c = '-';
	else if (type == N_UNDF)
		c = 'U';
	else if (type == N_ABS)
		c = 'A';
	else if (type == N_SECT)
		c = resolve_type_from_section(n_sect, bin);
	else if (type == N_PBUD)
		type = 'U';
	else if (type == N_INDR)
		c = 'I';
	if (!(n_type & N_EXT) && (c != '?')) /*c || ntype ? */
		c = ft_tolower(c);
	return(c);
}

void	parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, unsigned int offset, t_binary *bin)
{
	t_symbol *new;

	if (!(new = malloc((sizeof(char) * sizeof(t_symbol)))))
		return ;

	//	new->type = resolve_symbol_type(list, bin);
	new->type = resolve_symbol_type(list->n_type, list->n_sect, bin);
	new->fileoff = offset;
	new->value = list->n_value;
	new->name = bin->ptr + (symtab->stroff + list->n_un.n_strx);
	new->next = NULL;
	push_symbol_chunk(new, &bin->sym);
}

void	parse_load_command_x64(t_binary *bin, unsigned int lc_offset)
{
	uint32_t				count;
	unsigned int			sym_offset;
	struct nlist_64			*list;
	struct symtab_command	*symtab;

	count = -1;
	symtab = (struct symtab_command*)((char*)bin->ptr + lc_offset);
	sym_offset = symtab->symoff;
	while (++count < symtab->nsyms)
	{
		list = (struct nlist_64*)((char*)bin->ptr + sym_offset);
		if (!(list->n_type & N_STAB))
			parse_symbol_x64(symtab, list, sym_offset, bin);
		sym_offset += sizeof(*list);
	}
}

int		handle_x64(t_binary *bin)
{
	uint32_t				count;
	struct mach_header_64	*header;
	unsigned int			lc_offset;
	struct load_command		*load_command;

	count = -1;
	header = (struct mach_header_64*)bin->ptr;
	bin->offset = sizeof(*header);
	lc_offset = bin->offset;
	while (++count < header->ncmds)
	{
		load_command = (struct load_command*)((char*)bin->ptr + lc_offset);
		if (load_command->cmd == LC_SEGMENT_64)
			parse_segment_x64(bin, lc_offset);
		else if (load_command->cmd == LC_SYMTAB)
			parse_load_command_x64(bin, lc_offset);
		lc_offset += load_command->cmdsize;
	}
	print_symbol_x64(bin->sym);
//	print_section(bin->sect);
//	print_symbol(bin->sym);
	return (SUCCESS);
}
