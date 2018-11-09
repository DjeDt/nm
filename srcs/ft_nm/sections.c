/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:08:09 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/09 19:09:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_section	*create_section_chunk_x32(int endian, struct section *sect)
{
	t_section *new;

	if (!(new = (t_section*)malloc(sizeof(char) * sizeof(t_section))))
		return (NULL);
	new->segname = sect->segname;
	new->sectname = sect->sectname;
	new->addr = reverse_32(endian, sect->addr);
	new->offset = reverse_32(endian, sect->offset);
	new->size = reverse_32(endian, sect->size);
	new->next = NULL;
	return (new);
}

static t_section	*create_section_chunk_x64(int endian, \
											struct section_64 *sect)
{
	t_section *new;

	if (!(new = (t_section*)malloc(sizeof(char) * sizeof(t_section))))
		return (NULL);
	new->segname = sect->segname;
	new->sectname = sect->sectname;
	new->addr = reverse_64(endian, sect->addr);
	new->offset = reverse_32(endian, sect->offset);
	new->size = reverse_64(endian, sect->size);
	new->next = NULL;
	return (new);
}

void				push_section_chunk_x32(int endian, \
										struct section *chunk, t_section **sect)
{
	t_section *tmp;

	if (*sect == NULL)
		(*sect) = create_section_chunk_x32(endian, chunk);
	else
	{
		tmp = (*sect);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x32(endian, chunk);
	}
}

void				push_section_chunk_x64(\
	int endian, struct section_64 *chunk, t_section **sect)
{
	t_section *tmp;

	if (*sect == NULL)
		(*sect) = create_section_chunk_x64(endian, chunk);
	else
	{
		tmp = (*sect);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_section_chunk_x64(endian, chunk);
	}
}
