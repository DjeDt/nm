/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 21:02:46 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/16 12:07:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/* struct segment_command_64	*get_specific_segment_64(struct load_command *lc, unsigned int limit, const char *needle) */
/* { */
/* 	unsigned int				count; */
/* 	unsigned int				limit; */
/* 	struct load_command			*load_command; */
/* 	struct segment_command_64	*segment; */

/* 	count = 0; */
/* 	segment = NULL; */
/* 	if (lc != NULL) */
/* 	{ */
/* 		load_command = lc; */
/* 		segment = get_segment_64(load_command); */
/* 		while (load_command && count++ < limit) */
/* 		{ */
/* 			if (ft_strcmp(segment->segname, needle) == 0) */
/* 				return (segment); */
/* 			load_command = next_load_command(load_command); */
/* 		} */
/* 	} */
/* 	return (NULL); */
/* } */

void						print_segment_64_info(struct segment_command_64 *segment, void *ptr, unsigned int offset)
{
	if (segment != NULL)
	{
/*
		printf("--- Segment info:\ncmd: %u\ncmdsize: %u\nsegname: %s\nvmaddr (segment addr): %llu\nvmsize (memory size): %llu\nfileoff (offset from file): %llu\nnsect (nb section) : %u\n",
			   segment->cmd,
			   segment->cmdsize,
			   segment->segname,
			   segment->vmaddr,
			   segment->vmsize,
			   segment->fileoff,
			   segment->nsects);
*/
		printf("--- SEGMENT:\nname : %s\noffset: %llu\nseg size: %llu\n\n", segment->segname, segment->fileoff, segment->vmsize);
	}
	struct segment_command_64 *test;
	test = (struct segment_command_64*)(ptr + offset);
	if (test == segment)
		printf("offset is ok\n");
	else
		printf("noffset is not good %p vs %p\n", segment, test);
	printf("\n");
}

struct segment_command_64	*get_segment_64(struct load_command *load_command)
{
	struct segment_command_64	*segment;

	segment = NULL;
	if (load_command != NULL)
	{
		segment = (struct segment_command_64*)((char*)load_command);
		return (segment);
	}
	return (NULL);
}
