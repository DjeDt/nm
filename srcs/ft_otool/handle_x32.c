/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:21:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/16 19:07:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	print_section_x32(t_binary *bin, struct section *section)
{
	uint64_t	count;
	uint64_t	count2;
	uint64_t	limit;
	char		*data;

	count = 0;
	limit = reverse_32(bin->endian, section->size);
	if (!(data = move_ptr(bin, reverse_32(bin->endian, section->offset))))
		return (print_error("no data section found: abort."));
	if (!(bin->opt & PRINT_NAME))
		ft_printf("%s:\n", bin->path);
	ft_printf("Contents of (%s,%s) section\n", section->segname, section->sectname);
	while (count < limit)
	{
		count2 = 0;
		ft_printf("%08llx\t", reverse_32(bin->endian, section->addr) + count);
		while (count < limit && count2 < 16)
			print_hexa(data, &count, &count2, bin);
		ft_putchar('\n');
	}
	return (SUCCESS);
}

static int	parse_segment_x32(t_binary *bin)
{
	uint32_t				count;
	uint32_t				limit;
	struct section			*section;
	struct segment_command	*segment;

	count = -1;
	if (!(segment = move_ptr(bin, bin->offset)))
		return (print_error("segment_command error: abort."));
	bin->offset += sizeof(*segment);
	limit = reverse_32(bin->endian, segment->nsects);
	while (++count < limit)
	{
		if (!(section = move_ptr(bin, bin->offset)))
			return (print_error("section error: abort."));
		if (ft_strcmp(section->segname, "__TEXT") == 0 && ft_strcmp(section->sectname, "__text") == 0)
			return (print_section_x32(bin, section));
		bin->offset += sizeof(*section);
	}
	return (NOPE);
}

static int	parse_mach_header_x32(t_binary *bin, struct mach_header *header)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct load_command	*load_command;

	ret = NOPE;
	count = -1;
	limit = reverse_32(bin->endian, header->ncmds);
	while (++count < limit && ret == NOPE)
	{
		if (!(load_command = move_ptr(bin, bin->offset)))
			return (print_error("load_command error: abort."));
		if (reverse_32(bin->endian, load_command->cmd) == LC_SEGMENT)
			ret = parse_segment_x32(bin);
		else
			bin->offset += reverse_32(bin->endian, load_command->cmdsize);
	}
	return (ret);
}

int			handle_x32(t_binary *bin)
{
	int					ret;
	struct mach_header	*header;

	if (!(header = move_ptr(bin, bin->offset)))
		return (print_error("mach_header error: abort."));
	bin->offset += sizeof(*header);
	ret = parse_mach_header_x32(bin, header);
	return (ret);
}
