/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:09:54 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/06 18:23:48 by ddinaut          ###   ########.fr       */
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

void print_opt(unsigned long int i)
{
	if (i & FLAG_UA)
		ft_printf("%c is set\n", 'A');
	if (i & FLAG_LN)
		ft_printf("%c is set\n", 'n');
	if (i & FLAG_LO)
		ft_printf("%c is set\n", 'o');
	if (i & FLAG_LP)
		ft_printf("%c is set\n", 'p');
	if (i & FLAG_LR)
		ft_printf("%c is set\n", 'r');
	if (i & FLAG_LU)
		ft_printf("%c is set\n", 'u');
	if (i & FLAG_UU)
		ft_printf("%c is set\n", 'U');
	if (i & FLAG_LM)
		ft_printf("%c is set\n", 'm');
	if (i & FLAG_LX)
		ft_printf("%c is set\n", 'x');
	if (i & FLAG_LJ)
		ft_printf("%c is set\n", 'j');
	if (i & FLAG_LT)
		ft_printf("%c is set\n", 't');
}
