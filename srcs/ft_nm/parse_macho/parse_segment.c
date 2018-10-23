/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 21:02:46 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/23 19:33:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
	(void)offset;
	(void)ptr;
	struct segment_command_64 *test;
	(void)test;
	/* test = (struct segment_command_64*)(ptr + offset); */
	/* if (test == segment) */
	/* 	printf("offset is ok\n"); */
	/* else */
	/* 	printf("noffset is not good %p vs %p\n", segment, test); */
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
