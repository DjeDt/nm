/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:08:36 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 23:04:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

void print_section(t_section *section)
{
	t_section *tmp;

	tmp = section;
	while (tmp != NULL)
	{
		printf("segname = %s\nsectname = %s\naddr = %llu\noffset = %u\nsize = %u\n\n",
			   tmp->segname , \
			   tmp->sectname, \
			   tmp->addr, \
			   tmp->offset, \
			   tmp->size);
		tmp = tmp->next;
	}
}

t_section	*create_section_chunk(struct section_64 *section)
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

void		push_section_chunk(struct section_64 *chunk, t_section **section)
{
	t_section *tmp;

	if (*section == NULL)
		(*section) = create_section_chunk(chunk);
	else
	{
		tmp = (*section);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk(chunk);
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
		push_section_chunk(section, &bin->sect);
		seg_offset += sizeof(*section);
	}
}

/* t_symbol	*create_symbol_chunk(struct nlist_64 *symbol, uint32_t sym_offset) */
/* { */
/* 	t_symbol *new; */

/* 	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol)))) */
/* 		return (NULL); */
/* 	new->sect = symbol->n_sect; */
/* 	new->type = symbol->n_type; */
/* 	new->fileoff = sym_offset; */
/* 	new->value = symbol->n_value; */
/* 	new->next = NULL; */
/* 	return (new); */
/* } */

/* void	push_symbol_chunk(struct nlist_64 *chunk, t_symbol **symbol, uint32_t sym_offset) */
/* { */
/* 	t_symbol *tmp; */
/* 	t_symbol *new; */

/* 	if (!chunk) */
/* 		return ; */
/* 	new = create_symbol_chunk(chunk, sym_offset); */
/* 	if (*symbol == NULL || ft_strcmp((*symbol)->sym_name, new->sym_name)) */
/* 	{ */
/* 		new->next = (*symbol); */
/* 		(*symbol) = new; */
/* 	} */
/* 	else */
/* 	{ */
/* 		tmp = (*symbol); */
/* 		while (tmp->next != NULL && ft_strcmp(tmp->next->sym_name, new->sym_name) < 0) */
/* 			tmp = tmp->next; */
/* 		new->next = tmp->next; */
/* 		tmp->next = new; */
/* 	} */
/* } */

char	resolve_type_from_section(struct nlist_64 *list, t_binary *bin)
{
	int count;
	t_section *sect;

	count = 0;
	sect = bin->sect;
	while (sect != NULL && ++count != list->n_sect)
		sect = sect->next;

	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		return ('t');
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
		return ('D');
	else if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
		return ('B');
	return ('S');
}

char	resolve_symbol_type(struct nlist_64 *list, unsigned int sym_offset, t_binary *bin)
{
	char	c;
	uint8_t	type;

	c = '?';
	(void)sym_offset;
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
	if (!(list->n_type & N_EXT) && list->n_type != '?')
		c = ft_tolower(c);
	return(c);
}

void	parse_symbol_x64(struct nlist_64 *list, unsigned int sym_offset, t_binary *bin)
{
	t_symbol *new;

	ft_putendl("test");
	if (!(new = malloc((sizeof(char) * sizeof(t_symbol)))))
		return ;
	new->type = resolve_symbol_type(list, sym_offset, bin);
	new->name = bin->ptr + sym_offset;
	printf("%c %s\n", new->type, new->name);

}

void	parse_load_command_x64(t_binary *bin, unsigned int lc_offset)
{
	uint32_t				count;
	unsigned int			sym_offset;
	struct nlist_64			*list;
	struct symtab_command	*symtab;

	count = -1;
	symtab = (struct symtab_command*)((char*)bin->ptr + lc_offset);
	sym_offset = symtab->symoff + sizeof(*symtab);
	while (++count < symtab->nsyms)
	{
		if ((list->n_type & N_STAB) == 0)
		{
			list = (struct nlist_64*)((char*)bin->ptr + sym_offset);
			parse_symbol_x64(list, sym_offset, bin);
//			push_symbol_chunk(list, &bin->sym, sym_offset);
			sym_offset += sizeof(*list);
		}
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
	load_command = (struct load_command*)((char*)header + bin->offset);
	lc_offset = bin->offset;
	while (++count < header->ncmds)
	{
		load_command = (void*)bin->ptr + lc_offset;
//		load_command = (struct load_command*)((char*)bin->ptr + lc_offset);

		if (load_command->cmd == LC_SEGMENT_64)
			parse_segment_x64(bin, lc_offset);
		else if (load_command->cmd == LC_SYMTAB)
			parse_load_command_x64(bin, lc_offset);
		lc_offset += load_command->cmdsize;
	}
	print_section(bin->sect);
	return (SUCCESS);
}
