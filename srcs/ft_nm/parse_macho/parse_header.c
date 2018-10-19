/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:36:33 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/18 18:31:00 by ddinaut          ###   ########.fr       */
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

char						parse_symbol_elem2(uint8_t type)
{
	char c;

	/*

OK	  U (undefined)
OK	  A (absolute)
	  T (text section symbol)
	  D (data section symbol)
	  B (bss section symbol)
	  C (common symbol)
	  - (for debugger symbol table entries; see -a below)
	  S (symbol in a section other than those above)
	  I  (indirect  symbol)

	  Tips:
	  If the symbol is local (non-external), the symbol's type is instead represented by the corresponding lowercase letter.
	  u in a dynamic shared library indicates a undefined reference to a private  external  in  another  module  in  the  same library.

	*/
	c = '?';
	if ((type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((type & N_TYPE) == N_SECT)
	{
		/*
		  Trouver la bonne section

		*/

		c = '.';
	}
	else if ((type & N_TYPE) == N_PBUD)
		c = 'U';
	else if ((type & N_TYPE) == N_INDR)
		c = 'I';
	if (!(type & N_EXT))
		c = ft_tolower(c);
	return (c);
}
char						parse_symbol_elem(struct nlist_64 el)
{
	char c;

	c = 0;
	if ((el.n_type & N_TYPE) == N_SECT)
		c = '{';
	else if ((el.n_type & N_TYPE) == N_UNDF)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				c = 'U';//ft_putchar('U');
			else
				c = 'u';//ft_putchar('u');
		}
		else
		{
			if (el.n_type & N_EXT)
				c = 'C';//ft_putchar('C');
			else
				c = 'c';//ft_putchar('c');
		}
	}
	else if ((el.n_type & N_TYPE) == N_ABS)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				c = 'A';//ft_putchar('A');
			else
				c = 'a';//ft_putchar('a');
		}
	}
	else if ((el.n_type & N_TYPE) == N_INDR)
	{
		if (el.n_value == 0)
		{
			if (el.n_type & N_EXT)
				c = 'I';//ft_putchar('I');
			else
				c = 'i';//ft_putchar('i');
		}
	}
	else
		c = 'i';//ft_putchar('X');
	return (c);
}
