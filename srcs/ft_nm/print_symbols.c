/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:48:02 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 15:50:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_symbol_x32(t_binary *bin)
{
	t_symbol *tmp;

	tmp = bin->sym;
	if (bin->opt & FLAG_MULT_FILE)
		ft_printf("\n%s:\n", bin->path);
	while (tmp != NULL)
	{
		if (tmp->type != 'U')
			ft_printf("%08lx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%8s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}

void	print_symbol_x64(t_binary *bin)
{
	t_symbol *tmp;

	tmp = bin->sym;
	if (bin->opt & FLAG_MULT_FILE)
		ft_printf("\n%s:\n", bin->path);
	while (tmp != NULL)
	{
		if (tmp->type != 'U')
			ft_printf("%016lx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%16s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}

}
