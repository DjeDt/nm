
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:46:43 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/12 19:40:38 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_filetype_64(struct mach_header_64 *header)
{
	if (header->filetype == MH_OBJECT)
		ft_putendl("1: relocatable object file");
	if (header->filetype == MH_EXECUTE)
		ft_putendl("2: demand paged executable file");
	if (header->filetype == MH_FVMLIB)
		ft_putendl("3: fixed VM shared library file");
	if (header->filetype == MH_CORE)
		ft_putendl("4: core file");
	if (header->filetype == MH_PRELOAD)
		ft_putendl("5: preloaded executable file");
	if (header->filetype == MH_DYLIB)
		ft_putendl("6: dynamically bound shared library");
	if (header->filetype == MH_DYLINKER)
		ft_putendl("7: dynamic link editor");
	if (header->filetype == MH_BUNDLE)
		ft_putendl("8: dynamically bound bundle file");
	if (header->filetype == MH_DYLIB_STUB)
		ft_putendl("9: shared library stub for static");
	if (header->filetype == MH_DSYM)
		ft_putendl("10: companion file with only debug");
	if (header->filetype == MH_KEXT_BUNDLE)
		ft_putendl("11: x86_64 kexts");
	ft_putchar('\n');
}

int		handle_specific_64(t_binary fileinfo)
{
	ft_putendl("specific 64 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}

void	print_symbol_64(struct load_command *load_command, struct mach_header_64 *header, t_binary fileinfo)
{
	char					*str;
	uint32_t				count;
	struct nlist_64			*el;	// elem_list
	struct symtab_command	*symbol;

	count = -1;

	symbol = get_symbol_table_64(load_command);
	if (symbol == NULL)
	{
		ft_putendl_fd("error, can't found symbol table", STDERR_FILENO);
		return ;
	}
	el = get_elem_list_64(header, symbol);
	if (el == NULL)
	{
		ft_putendl_fd("error, can't found elem list", STDERR_FILENO);
		return ;
	}
	str = get_symbol_name_64(header, symbol);
	(void)fileinfo;
	while (++count < symbol->nsyms)
	{
		parse_symbol_elem(el[count]);
		ft_putchar(' ');

		ft_putendl("next symbol");
		// valeur du symbole (offset)
//		ft_puthex(el[count].n_value);
//		printf("%016llx %s\n", el[count].n_value, str + el[count].n_un.n_strx);
 		// nom du symbole
//		ft_putendl(str + el[count].n_un.n_strx);
	}
}

void	print_section_64(struct load_command *load_command)
{
	unsigned int				count;
	struct segment_command_64	*segment;
	struct section_64			*section;

	count = 0;
	segment = get_segment_64(load_command);
	if (segment == NULL)
		return ;
	ft_putstr("segment name: "); ft_putendl(segment->segname);
	section = get_section_64(segment);
	while (section != NULL && ++count < segment->nsects)
	{
		printf("\tsection -> %p -> %s | %s\n", &section->addr, section->sectname, section->segname);
		section = get_next_section_64(section);
	}
	return ;
}

int		handle_64(t_binary fileinfo)
{
	unsigned int			count;
	struct mach_header_64	*header;
	struct load_command		*load_command;

	count = 0;
	header = get_header_64(fileinfo.ptr);
	if (header == NULL)
	{
		ft_putendl_fd("error: can't found binary header, abort", STDERR_FILENO);
		return (ERROR);
	}

	load_command = get_load_command_64(header);
	if (load_command == NULL)
	{
		ft_putendl_fd("error: can't found header metadata, abort", STDERR_FILENO);
		return (ERROR);
	}

	while (count++ < header->ncmds)
	{
		if (load_command->cmd == LC_SEGMENT_64)
			print_section_64(load_command);
		if (load_command->cmd == LC_SYMTAB)
		{
			print_symbol_64(load_command, header, fileinfo);
			return (SUCCESS);
		}
		load_command = next_load_command(load_command);
	}
	header = NULL;
	load_command = NULL;
	return (ERROR);
}
