/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:58:11 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/26 16:00:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	resolve_type_from_section(uint32_t n_sect, t_binary *bin)
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

char	resolve_symbol_type(uint8_t n_type, uint8_t n_sect, t_binary *bin)
{
	char	c;
	uint8_t	type;

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
