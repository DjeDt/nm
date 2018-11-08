/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:08:36 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 21:03:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_symbol_x64(t_binary *bin)
{
	t_symbol *tmp;

	tmp = bin->sym;
	if (bin->opt & FLAG_MULT_FILE)
		ft_printf("\n%s:\n", bin->path);
	while (tmp != NULL)
	{
		if (tmp->type != 'U')
			ft_printf("%016llx %c %s\n", tmp->value, tmp->type, tmp->name);
		else
			ft_printf("%16s %c %s\n", "", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}

static int	parse_segment_x64(t_binary *bin, struct stat stat)
{
	uint32_t					count;
	uint32_t					limit;
	struct section_64			*section;
	struct segment_command_64	*segment;

	count = -1;
	if (!(segment = (struct segment_command_64*)move_ptr(bin, stat, bin->offset)))
		return (ERROR);
	bin->offset += sizeof(*segment);
	limit = reverse_32(bin->endian, segment->nsects);
	while (++count < limit)
	{
		if (!(section = (struct section_64*)move_ptr(bin, stat, bin->offset)))
			return (ERROR);
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
	if (!(symtab = (struct symtab_command*)move_ptr(bin, stat, bin->offset)))
		return (ERROR);
	bin->offset = reverse_32(bin->endian, symtab->symoff);
	limit = reverse_32(bin->endian, symtab->nsyms);
	while (++count < limit)
	{
		if ((list = (struct nlist_64*)move_ptr(bin, stat, bin->offset)) == NULL)
			return (ERROR);
		if (!(list->n_type & N_STAB))
		{
			if (parse_symbol_x64(symtab, list, bin, stat) != SUCCESS)
				return (ERROR);
		}
		bin->offset += sizeof(*list);
	}
	return (SUCCESS);
}

static int	parse_mach_header_x64(t_binary *bin, struct stat stat, struct mach_header_64 *header)
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
		if (!(load_command = (struct load_command*)move_ptr(bin, stat, bin->offset)))
			return (ERROR);
		if (load_command->cmd == LC_SEGMENT_64)
			ret = parse_segment_x64(bin, stat);
		else if (load_command->cmd == LC_SYMTAB)
			ret = parse_load_command_x64(bin, stat);
		else
			bin->offset += reverse_32(bin->endian, load_command->cmdsize);
		if (ret != SUCCESS)
			return (ret);
	}
	return (SUCCESS);
}

int			handle_x64(t_binary *bin, struct stat stat)
{
	int						ret;
	struct mach_header_64	*header;

	header = move_ptr(bin, stat, bin->offset);
	if (header == NULL)
		return (ERROR);
	bin->offset = sizeof(*header);
	ret = parse_mach_header_x64(bin, stat, header);
	if (ret == SUCCESS)
		print_symbol_x64(bin);
	free_sect(&bin->sect);
	free_sym(&bin->sym);
	return (ret);
}
