/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:46:43 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/22 19:35:21 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_data(void)
{
	t_sym *tmp;

	tmp = sym;
	while (tmp != NULL)
	{
		if (tmp->sym_value == 0)
			printf("%16s %c %s\n", "", tmp->sym_type, tmp->sym_name);
		else
			printf("%016lx %c %s\n", tmp->sym_value, tmp->sym_type, tmp->sym_name);
		tmp = tmp->next;
	}
}

void	push_chunk(t_sym *new, t_sym **head, int sort_func(const char *s1 ,const char *s2))
{
	t_sym *current;

	if (!new)
		return ;
	if ((*head) == NULL || sort_func((*head)->sym_name, new->sym_name) >= 0)
	{
		new->next = (*head);
		(*head) = new;
	}
	else
	{
		current = (*head);
		while (current->next != NULL && sort_func(current->next->sym_name, new->sym_name) < 0)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

t_sym	*new_chunk(void *sym_name, unsigned long sym_value, char type)
{
	t_sym *ret;

	ret = (t_sym*)malloc(sizeof(t_sym));
	if (!ret)
		return (NULL);
	ret->sym_type = type;
	ret->sym_name = sym_name;
	ret->sym_value = sym_value;
	ret->next = NULL;
	return (ret);
}

int		handle_specific_64(t_binary *fileinfo)
{
	ft_putendl("specific 64 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}

void	browse_symtab(struct symtab_command *symtab, struct nlist_64 *el, char *str, t_binary *fileinfo)
{
	size_t	count;
	char	c;
	t_sym	*new;

	count = 0;
	while (count < symtab->nsyms)
	{
		c = '?';
//--------------
		/*
		  OK    U (undefined)
		  OK    A (absolute)
		  OK	T (text section symbol)
		  OK	D (data section symbol)
		  OK	B (bss section symbol)
		  C (common symbol)
		  - (for debugger symbol table entries; see -a below)
		  OK	S (symbol in a section other than those above)
		  OK	I  (indirect  symbol)

		  Tips:
		  If the symbol is local (non-external), the symbol's type is instead represented by the corresponding lowercase letter.
		  u in a dynamic shared library indicates a undefined reference to a private  external  in  another  module  in  the  same library.
		*/
//		c = parse_symbol_elem2(el[count].n_type);

		uint8_t type = el[count].n_type;
		if ((type & N_TYPE) == N_UNDF)
			c = 'U';
		else if ((type & N_TYPE) == N_ABS)
			c = 'A';
		else if ((type & N_TYPE) == N_SECT)
		{

			struct mach_header_64		*header;
			header = get_header_64(fileinfo->ptr);

			struct load_command			*load_command;
			load_command = get_load_command_64(header, fileinfo);
			size_t count2 = 0;
			while (count2++ < header->ncmds)
			{
				if (load_command->cmd == LC_SEGMENT_64)
					break ;
				load_command = next_load_command(load_command, fileinfo);
			}
			struct segment_command_64	*segment;
			segment = (struct segment_command_64*)get_segment_64(load_command);

			struct section_64 *section;
			section = (struct section_64*)segment + el[count].n_sect;

			/* ft_putstr("section = "); */
			/* ft_putendl(section->sectname); */
			/* ft_putstr("segment = "); */
			/* ft_putendl(section->segname); */
			/* ft_putendl("---------"); */

			if (ft_strcmp(section->sectname, "__TEXT") == 0)
				c = 'T';
			else if (ft_strcmp(section->sectname, "__DATA") == 0)
					c = 'D';
			else if (ft_strcmp(section->sectname, "__BSS") == 0)
				c = 'B';
			else
				c = 'S';

			/* if (ft_strncmp(section->sectname, "__text", 6) == 0) */
			/* 	c = 'T'; */
			/* else if (ft_strncmp(section->sectname, "__data", 6) == 0) */
			/* 		c = 'D'; */
			/* else if (ft_strncmp(section->sectname, "__bss", 5) == 0) */
			/* 	c = 'B'; */
			/* else */
			/* 	c = 'S'; */
		}
		else if ((type & N_TYPE) == NO_SECT || el[count].n_sect == NO_SECT)
			ft_putendl("no sect");
		else if ((type & N_TYPE) == N_PBUD)
			c = 'U';
		else if ((type & N_TYPE) == N_INDR)
			c = 'I';
		if (!(type & N_EXT))
			c = ft_tolower(c);
//--------------

		if (el[count].n_value == 0)
			new = new_chunk(str + el[count].n_un.n_strx, 0, c);
		else
			new = new_chunk(str + el[count].n_un.n_strx, el[count].n_value, c);
		push_chunk(new, &sym, ft_strcmp);
		count++;
	}
}

void	print_symbol_64(struct load_command *load_command, struct mach_header_64 *header, t_binary *fileinfo)
{


	struct symtab_command	*symbol_tab;
	symbol_tab = get_symbol_table_64(load_command);

	struct nlist_64			*el;
	el = get_elem_list_64(header, symbol_tab);

	char					*str;
	str = get_symbol_offset_64(header, symbol_tab);

	browse_symtab(symbol_tab, el, str, fileinfo);
	return ;
}

int		handle_64(t_binary *fileinfo)
{
	unsigned int			count;
	struct mach_header_64	*header;
	struct load_command		*load_command;

	count = 0;
	fileinfo->offset = 0;
	header = get_header_64(fileinfo->ptr);
	load_command = get_load_command_64(header, fileinfo);
	while (count++ < header->ncmds)
	{
		/* if (load_command->cmd == LC_SEGMENT_64) */
		/* 	print_section_64(load_command, &fileinfo); */

		if (load_command->cmd == LC_SYMTAB)
		{
			print_symbol_64(load_command, header, fileinfo);
			break;
		}
		/* fileinfo->offset += load_command->cmdsize; */
		/* load_command = (void*)load_command + load_command->cmdsize; */
		load_command = next_load_command(load_command, fileinfo);
	}
	print_data();
	header = NULL;
	load_command = NULL;
	return (ERROR);
}
