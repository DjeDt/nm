/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:58:11 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 20:49:09 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char		resolve_type_from_section(uint32_t n_sect, t_binary *bin)
{
	uint32_t	count;
	uint32_t	rsect;
	t_section	*sect;

	count = 0;
	sect = bin->sect;
	rsect = reverse_32(bin->endian, n_sect);
	while (sect != NULL && ++count < rsect)
		sect = sect->next;
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		return ('T');
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
		return ('D');
	else if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
		return ('B');
	return ('S');
}

char			resolve_symbol_type(uint8_t n_type, uint8_t n_sect, uint8_t n_val, t_binary *bin)
{
	char	c;
	uint8_t	type;

	c = '?';
	type = n_type & N_TYPE;
	if (n_type & N_STAB)
		c = '-';
	else if (type == N_UNDF || type == N_PBUD)
	{
		c = 'U';
		if (type == N_UNDF && n_val > 0)
			c = 'C';
	}
	else if (type == N_ABS)
		c = 'A';
	else if (type == N_SECT)
		c = resolve_type_from_section(n_sect, bin);
	else if (type == N_INDR)
		c = 'I';
	if (!(n_type & N_EXT) && (c != '?'))
		c = ft_tolower(c);
	return (c);
}
