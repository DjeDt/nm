/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_section_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:00:49 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 18:27:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm_32.h"

void print_sect_32(struct section *section)
{
	printf("scetname = %s\n segname = %s\nsize = %u\n", \
		   section->sectname,			   \
		   section->segname,
		   section->size);
}

char				search_specific_section_32(t_segment *seg_list, uint8_t offset)
{
	uint8_t			count;
	struct section	*section;

	section = NULL;
	while (seg_list != NULL)
	{
		count = 0;
		section = get_section_32(seg_list->segment);
		while (++count < seg_list->segment->nsects)
		{
			if (count == offset)
			{
				if (ft_strcmp(section->sectname, "__text") == 0)
					return ('T');
				else if (ft_strcmp(section->sectname, "__data") == 0)
					return ('D');
				else if (ft_strcmp(section->sectname, "__bss") == 0)
					return('B');
			}
			count++;
			section = get_next_section_32(section);
		}
		seg_list = seg_list->next;
	}
	return ('S');
}

struct section			*get_next_section_32(struct section *section)
{
	if (section != NULL)
	{
		section = (struct section*)((char*)section + sizeof(*section));
		return (section);
	}
	return (NULL);
}

struct section			*get_section_32(struct segment_command *segment)
{
	struct section	*section;

	section = NULL;
	if (segment != NULL)
	{
		section = (struct section*)((char*)segment + sizeof(*segment));
		return (section);
	}
	return (NULL);
}
