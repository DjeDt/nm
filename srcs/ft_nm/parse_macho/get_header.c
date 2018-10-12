/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:36:33 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/12 19:40:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned int	get_magic_number(void *data_file)
{
	unsigned int magic_number;

	magic_number = 0;
	if (data_file != NULL)
	{
		magic_number = *(unsigned int *)data_file;
		return (magic_number);
	}
	return (ERROR);
}

struct mach_header_64	*get_header_64(void *data_file)
{
	struct mach_header_64 *header;

	if (data_file != NULL)
	{
		header = (struct mach_header_64*)data_file;
		return (header);
	}
	return (NULL);
}

struct mach_header	*get_header_32(void *data_file)
{
	struct mach_header *header;

	header = NULL;
	if (data_file != NULL)
	{
		header = (struct mach_header*)data_file;
		return (header);
	}
	return (NULL);
}

struct load_command	*get_load_command_64(struct mach_header_64 *header)
{
	struct load_command	*load_command;

	load_command = NULL;
	if (header != NULL)
	{
//		load_command = (struct load_command*)&header[1];
		load_command = (struct load_command*)((char*)header + sizeof(*header));
		return (load_command);
	}
	return (NULL);
}

struct load_command	*get_load_command_32(struct mach_header *header)
{
	struct load_command	*load_command;

	load_command = NULL;
	if (header != NULL)
	{
		load_command = (struct load_command*)((char*)header + sizeof(*header));
		return (load_command);
	}
	return (NULL);
}

struct load_command	*next_load_command(struct load_command *load_command)
{
	if (load_command != NULL)
		load_command = (struct load_command*)((char*)load_command + load_command->cmdsize);
	return (load_command);
}

struct symtab_command	*get_symbol_table_64(struct load_command *load_command)
{
	struct symtab_command	*symbols;

	symbols = NULL;
	if (load_command != NULL)
	{
		symbols = (struct symtab_command*)load_command;
		return (symbols);
	}
	return (NULL);
}

struct nlist_64			*get_elem_list_64(struct mach_header_64 *header, struct symtab_command *symbols)
{
	struct nlist_64	*el;

	el = NULL;
	if (header != NULL && symbols != NULL)
	{
		el = (struct nlist_64*)((char*)header + symbols->symoff);
		return (el);
	}
	return (NULL);
}

char				   *get_symbol_name_64(struct mach_header_64 *header, struct symtab_command *symbols)
{
	char	*str;

	str = NULL;
	if (header != NULL && symbols != NULL)
	{
		str = (char*)header + symbols->stroff;
		return (str);
	}
	return (NULL);
}

struct segment_command_64	*get_segment_64(struct load_command *load_command)
{
	struct segment_command_64	*segment;

	segment = NULL;
	if (load_command != NULL)
	{
		segment = (struct segment_command_64*)((char*)load_command);
		return (segment);
	}
	return (NULL);
}

struct section_64			*get_section_64(struct segment_command_64 *segment)
{
	struct section_64	*section;

	section = NULL;
	if (segment != NULL)
	{
		section = (struct section_64*)((char*)segment + sizeof(*segment));
		return (section);
	}
	return (NULL);
}

struct section_64			*get_next_section_64(struct section_64 *section)
{
	if (section != NULL)
		section = (struct section_64*)((char*)section + sizeof(*section));
	return (section);
}

void						parse_symbol_elem(struct nlist_64 el)
{
	if ((el.n_type & N_TYPE) == N_SECT)
		ft_putstr("?");
	else if ((el.n_type & N_TYPE) == N_UNDF)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				ft_putchar('U');
			else
				ft_putchar('u');
		}
		else
		{
			if (el.n_type & N_EXT)
				ft_putchar('C');
			else
				ft_putchar('c');
		}
	}
	else if ((el.n_type & N_TYPE) == N_ABS)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				ft_putchar('A');
			else
				ft_putchar('a');
		}
	}
	else if ((el.n_type & N_TYPE) == N_INDR)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				ft_putchar('I');
			else
				ft_putchar('i');
		}
	}
	else
		ft_putchar('X');
}
