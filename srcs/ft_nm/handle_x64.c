/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:08:36 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:39:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	parse_segment_x64(t_binary *bin)
{
	uint32_t					count;
	uint32_t					limit;
	struct section_64			*section;
	struct segment_command_64	*segment;

	count = -1;
	if (!(segment = move_ptr(bin, bin->offset)))
		return (print_error("segment_command error: abort."));
	bin->offset += sizeof(*segment);
	limit = reverse_32(bin->endian, segment->nsects);
	while (++count < limit)
	{
		if (!(section = move_ptr(bin, bin->offset)))
			print_error("section_64 error: abort.");
		push_section_chunk_x64(bin->endian, section, &bin->sect);
		bin->offset += sizeof(*section);
	}
	return (SUCCESS);
}

static int	parse_load_command_x64(t_binary *bin)
{
	uint32_t				count;
	uint32_t				limit;
	struct nlist_64			*list;
	struct symtab_command	*symtab;

	count = -1;
	if (!(symtab = move_ptr(bin, bin->offset)))
		return (print_error("symtab_comment error: abort."));
	bin->offset = reverse_32(bin->endian, symtab->symoff);
	limit = reverse_32(bin->endian, symtab->nsyms);
	while (++count < limit)
	{
		if (!(list = move_ptr(bin, bin->offset)))
			return (print_error("nlist_64 error: abort."));
		if (!(list->n_type & N_STAB))
		{
			if (parse_symbol_x64(symtab, list, bin) != SUCCESS)
				return (ERROR);
		}
		bin->offset += sizeof(*list);
	}
	return (SUCCESS);
}

static int	parse_mach_header_x64(t_binary *bin, struct mach_header_64 *header)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct load_command	*load_command;

	ret = SUCCESS;
	count = -1;
	limit = reverse_64(bin->endian, header->ncmds);
	while (++count < limit)
	{
		if (!(load_command = move_ptr(bin, bin->offset)))
			return (print_error("load_command error: abort."));
		if (reverse_32(bin->endian, load_command->cmd) == LC_SEGMENT_64)
			ret = parse_segment_x64(bin);
		else if (reverse_32(bin->endian, load_command->cmd) == LC_SYMTAB)
			return (parse_load_command_x64(bin));
		else
			bin->offset += reverse_32(bin->endian, load_command->cmdsize);
	}
	return (ret);
}

int			handle_x64(t_binary *bin)
{
	int						ret;
	struct mach_header_64	*header;

	if (!(header = move_ptr(bin, bin->offset)))
		return (print_error("mach_header error: abort."));
	bin->offset += sizeof(*header);
	ret = parse_mach_header_x64(bin, header);
	if (ret == SUCCESS)
		print_symbol_x64(bin);
	free_sect(&bin->sect);
	free_sym(&bin->sym);
	return (ret);
}
