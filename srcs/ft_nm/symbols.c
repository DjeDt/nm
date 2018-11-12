/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:07:49 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 11:59:50 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	push_symbol_chunk(t_binary *bin, t_symbol *new, t_symbol **symbol)
{
	if (!new)
		return ;
	if (bin->opt & FLAG_LP)
		no_sort(new, symbol);
	else if (bin->opt & FLAG_LN && bin->opt & FLAG_LR)
		rev_sort_numericaly(new, symbol);
	else if (bin->opt & FLAG_LN)
		sort_numericaly(new, symbol);
	else if (bin->opt & FLAG_LR)
		rev_alpha_sort(new, symbol);
	else
		alpha_sort(new, symbol);
}

static void	*resolve_symbol_name(t_binary *bin, struct stat stat, \
								uint32_t stroff, uint32_t n_strx)
{
	void		*name;
	uint32_t	roff;
	uint32_t	rstrx;

	rstrx = reverse_32(bin->endian, n_strx);
	roff = reverse_32(bin->endian, stroff);
	name = move_ptr(bin, stat, rstrx + roff);
	return (name);
}

int			parse_symbol_x32(struct symtab_command *symtab, \
							struct nlist *lt, t_binary *bin, struct stat stat)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return (ERROR);
	new->type = resolve_symbol_type(lt->n_type, lt->n_sect, lt->n_value, bin);
	new->fileoff = bin->offset;
	new->value = reverse_32(bin->endian, lt->n_value);
	new->name = resolve_symbol_name(bin, stat, symtab->stroff, lt->n_un.n_strx);
	new->next = NULL;
	if (new->name == NULL)
		return (ERROR);
	push_symbol_chunk(bin, new, &bin->sym);
	return (SUCCESS);
}

int			parse_symbol_x64(struct symtab_command *symtab, \
							struct nlist_64 *lt, t_binary *bin, struct stat st)
{
	t_symbol *new;

	if (!(new = (t_symbol*)malloc(sizeof(char) * sizeof(t_symbol))))
		return (ERROR);
	new->type = resolve_symbol_type(lt->n_type, lt->n_sect, lt->n_value, bin);
	new->fileoff = bin->offset;
	new->value = reverse_64(bin->endian, lt->n_value);
	new->name = resolve_symbol_name(bin, st, symtab->stroff, lt->n_un.n_strx);
	new->next = NULL;
	if (new->name == NULL)
		return (ERROR);
	push_symbol_chunk(bin, new, &bin->sym);
	return (SUCCESS);
}
