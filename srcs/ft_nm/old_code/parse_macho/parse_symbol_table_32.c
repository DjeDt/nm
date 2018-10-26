/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol_table_32.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:33:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 16:05:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_32.h"

struct nlist			*next_elem_list_32(struct nlist *el)
{
	if (el != NULL)
	{
		el = (void*)el + sizeof(*el);
		return (el);
	}
	return (NULL);
}

struct nlist			*get_elem_list_32(struct mach_header *header, struct symtab_command *symbols)
{
	struct nlist	*el;

	el = NULL;
	if (header != NULL && symbols != NULL)
	{
		el = (void*)header + symbols->symoff;
		return (el);
	}
	return (NULL);
}

char                 *get_symbol_offset_32(struct mach_header *header, struct symtab_command *symbols)
{
	char    *str;

	str = NULL;
	if (header != NULL && symbols != NULL)
	{
		str = (char*)header + symbols->stroff;
		return (str);
	}
	return (NULL);
}
