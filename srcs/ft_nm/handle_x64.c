/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:08:36 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/12 20:31:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	parse_segment_x64(t_binary *bin, struct stat stat)
{
	uint32_t					count;
	uint32_t					limit;
	struct section_64			*section;
	struct segment_command_64	*segment;

	count = -1;
	if (!(segment = move_ptr(bin, stat, bin->offset)))
	{
		ft_printf_fd(STDERR_FILENO, "segment error: abort.\n");
		return (ERROR);
	}
	bin->offset += sizeof(*segment);
	limit = reverse_32(bin->endian, segment->nsects);
	while (++count < limit)
	{
		if (!(section = move_ptr(bin, stat, bin->offset)))
		{
			ft_printf_fd(STDERR_FILENO, "section error: abort.\n");
			return (-1);
		}
		push_section_chunk_x64(bin->endian, section, &bin->sect);
		bin->offset += sizeof(*section);
	}
	return (SUCCESS);
}

static int	parse_load_command_x64(t_binary *bin, struct stat stat)
{
	uint32_t				count;
	uint32_t				limit;
	struct nlist_64			*list;
	struct symtab_command	*symtab;

	count = -1;
	if (!(symtab = move_ptr(bin, stat, bin->offset)))
	{
		ft_printf_fd(STDERR_FILENO, "symtab_command error: abort.\n");
//		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_ST_STR));
	}
	bin->offset = reverse_32(bin->endian, symtab->symoff);
	limit = reverse_32(bin->endian, symtab->nsyms);
	while (++count < limit)
	{
		if (!(list = move_ptr(bin, stat, bin->offset)))
		{
			ft_printf_fd(STDERR_FILENO, "nlist error: abort.\n");
//			return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_NL_STR));
		}
		if (!(list->n_type & N_STAB))
		{
			if (parse_symbol_x64(symtab, list, bin, stat) != SUCCESS)
				return (ERROR);
		}
		bin->offset += sizeof(*list);
	}
	return (SUCCESS);
}

static int	parse_mach_header_x64(t_binary *bin, \
								struct stat stat, struct mach_header_64 *header)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct load_command	*load_command;

	ret = SUCCESS;
	count = -1;
	limit = reverse_64(bin->endian, header->ncmds);
	while (++count < limit && ret == SUCCESS)
	{
		if (!(load_command = move_ptr(bin, stat, bin->offset)))
		{
			ft_printf_fd(STDERR_FILENO, "load_command error. abort.\n");
			return (ERROR);
		}
		if (reverse_32(bin->endian, load_command->cmd) == LC_SEGMENT_64)
		{
			ret = parse_segment_x64(bin, stat);
		}
		else if (reverse_32(bin->endian, load_command->cmd) == LC_SYMTAB)
			return (parse_load_command_x64(bin, stat));
		else
			bin->offset += reverse_32(bin->endian, load_command->cmdsize);
	}
	return (ret);
}

int			handle_x64(t_binary *bin, struct stat stat)
{
	int						ret;
	struct mach_header_64	*header;

	if (!(header = move_ptr(bin, stat, bin->offset)))
		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_HDR_STR));
	bin->offset = sizeof(*header);
	ret = parse_mach_header_x64(bin, stat, header);
	if (ret == SUCCESS)
		print_symbol_x64(bin);
	free_sect(&bin->sect);
	free_sym(&bin->sym);
	return (ret);
}
