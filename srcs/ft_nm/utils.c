/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:09:54 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 12:10:32 by ddinaut          ###   ########.fr       */
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
