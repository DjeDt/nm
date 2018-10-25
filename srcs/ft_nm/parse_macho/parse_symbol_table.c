/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 20:57:09 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/24 13:44:28 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

struct nlist_64			*get_elem_list_64(struct mach_header_64 *header, struct symtab_command *symbols)
{
	struct nlist_64	*el;

	el = NULL;
	if (header != NULL && symbols != NULL)
	{
		el = (void*)header + symbols->symoff;
		return (el);
	}
	return (NULL);
}

struct nlist_64			*next_elem_list_64(struct nlist_64 *el)
{
	if (el != NULL)
	{
		el = (void*)el + sizeof(*el);
		return (el);
	}
	return (NULL);
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

struct symtab_command	*get_symbol_table(struct load_command *load_command)
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

char					*get_symbol_offset_64(struct mach_header_64 *header, struct symtab_command *symbols)
{
	char	*str;

	str = NULL;
	if (header != NULL && symbols != NULL)
	{
		str = (void*)header + symbols->stroff;
		return (str);
	}
	return (NULL);
}
