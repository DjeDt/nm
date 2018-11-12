/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:07:49 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 11:51:47 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	push_symbol_chunk(unsigned long opt, t_symbol *new, t_symbol **symbol)
{
	if (!new)
		return ;
	if (opt & FLAG_LP)
		no_sort(new, symbol);
	else if (opt & FLAG_LN && opt & FLAG_LR)
		rev_sort_numericaly(new, symbol);
	else if (opt & FLAG_LN)
		sort_numericaly(new, symbol);
	else if (opt & FLAG_LR)
		rev_alpha_sort(new, symbol);
	else
		alpha_sort(new, symbol);
}

static void	*resolve_symbol_name(t_binary *bin, struct stat stat, uint32_t stroff, uint32_t n_strx)
{
	void		*name;
	uint32_t	roff;
	uint32_t	rstrx;

	rstrx = reverse_32(bin->endian, n_strx);
	roff = reverse_32(bin->endian, stroff);
	name = move_ptr(bin, stat, rstrx + roff);
	return (name);
}

int		parse_symbol_x32(struct symtab_command *symtab, struct nlist *list, t_binary *bin, struct stat stat)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return (ERROR);
	new->type = resolve_symbol_type(list->n_type, list->n_sect, list->n_value, bin);
	new->fileoff = bin->offset;
	new->value = reverse_32(bin->endian, list->n_value);
	new->name = resolve_symbol_name(bin, stat, symtab->stroff, list->n_un.n_strx);
	new->next = NULL;
	if (new->name == NULL)
		return (ERROR);
	push_symbol_chunk(bin->opt, new, &bin->sym);
	return (SUCCESS);
}

int		parse_symbol_x64(struct symtab_command *symtab, struct nlist_64 *list, t_binary *bin, struct stat stat)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return (ERROR);
	new->type = resolve_symbol_type(list->n_type, list->n_sect, list->n_value, bin);
	new->fileoff = bin->offset;
	new->value = reverse_64(bin->endian, list->n_value);
	new->name = resolve_symbol_name(bin, stat, symtab->stroff, list->n_un.n_strx);
	new->next = NULL;
	if (new->name == NULL)
		return (ERROR);
	push_symbol_chunk(bin->opt, new, &bin->sym);
	return (SUCCESS);
}
