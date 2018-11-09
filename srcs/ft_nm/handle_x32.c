/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:33:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/09 11:14:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_symbol_x32(t_binary *bin)
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

static int	parse_segment_x32(t_binary *bin, struct stat stat)
{
	uint32_t				count;
	uint32_t				limit;
	struct section			*section;
	struct segment_command	*segment;

	count = -1;
	if (!(segment = (struct segment_command*)move_ptr(bin, stat, bin->offset)))
		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_SEG_STR));
	bin->offset += sizeof(*segment);
	limit = reverse_32(bin->endian, segment->nsects);
	while (++count < segment->nsects)
	{
		if (!(section = (struct section*)move_ptr(bin, stat, bin->offset)))
			return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_SECT_STR));
		push_section_chunk_x32(bin->endian, section, &bin->sect);
		bin->offset += sizeof(*section);
	}
	return (SUCCESS);
}

static int	parse_load_command_x32(t_binary *bin, struct stat stat)
{
	uint32_t				count;
	uint32_t				limit;
	struct nlist			*list;
	struct symtab_command	*symtab;

	count = -1;
	if (!(symtab = (struct symtab_command*)move_ptr(bin, stat, bin->offset)))
		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_ST_STR));
	bin->offset = reverse_32(bin->endian, symtab->symoff);
	limit = reverse_32(bin->endian, symtab->nsyms);
	while (++count < symtab->nsyms)
	{
		if (!(list = (struct nlist*)move_ptr(bin, stat, bin->offset)))
			return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_NL_STR));
		if (!(list->n_type & N_STAB))
		{
			if (parse_symbol_x32(symtab, list, bin, stat) != SUCCESS)
				return (ERROR);
		}
		bin->offset += sizeof(*list);
	}
	return (SUCCESS);
}

static int	parse_mach_header_x32(t_binary *bin, struct stat stat, struct mach_header *header)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct load_command	*load_command;

	ret = SUCCESS;
	count = -1;
	limit = reverse_32(bin->endian, header->ncmds);
	while (++count < limit)
	{
		if (!(load_command = move_ptr(bin, stat, bin->offset)))
			return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_LC_STR));
		if (load_command->cmd == LC_SEGMENT)
			ret = parse_segment_x32(bin, stat);
		else if (load_command->cmd == LC_SYMTAB)
		{
			parse_load_command_x32(bin, stat);
			break ;
		}
		else
			bin->offset += reverse_32(bin->endian, load_command->cmdsize);
		if (ret != SUCCESS)
			break ;
	}
	return (ret);
}

int			handle_x32(t_binary *bin, struct stat stat)
{
	int					ret;
	struct mach_header	*header;

	if (!(header = (struct mach_header*)move_ptr(bin, stat, bin->offset)))
		return (handle_error(bin->path, MISSING_PTR_ERR, MISSING_HDR_STR));
	bin->offset = sizeof(*header);
	ret = parse_mach_header_x32(bin, stat, header);
	if (ret == SUCCESS)
		print_symbol_x32(bin);
	free_sect(&bin->sect);
	free_sym(&bin->sym);
	return (ret);
}
