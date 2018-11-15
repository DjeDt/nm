/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:32:52 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:55:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_name(t_binary *bin, struct fat_arch *fat, uint32_t limit)
{
	uint32_t type;

	type = reverse_32(bin->endian, fat->cputype);
	if (limit == 1)
		ft_printf("%s:\n", bin->path);
	else if (type == CPU_TYPE_POWERPC || type == CPU_TYPE_X86 \
			|| type == CPU_TYPE_ARM64 || type == CPU_TYPE_ARM \
			|| type == CPU_SUBTYPE_ARM_V7S)
	{
		if (type == CPU_TYPE_POWERPC)
			ft_printf("\n%s (%s):\n", bin->path, "for architecture ppc");
		else if (type == CPU_TYPE_X86)
			ft_printf("\n%s (%s):\n", bin->path, "for architecture i386");
		else if (type == CPU_TYPE_ARM64)
			ft_printf("\n%s (%s):\n", bin->path, "for architecture arm64");
		else if (type == CPU_TYPE_ARM)
			ft_printf("\n%s (%s):\n", bin->path, "for architecture armv7");
		if (bin->opt & FLAG_MULT_FILE)
			bin->opt ^= FLAG_MULT_FILE;
	}
}

int		parse_fat_header_x32(t_binary *bin, uint32_t limit)
{
	int				ret;
	struct fat_arch *fat;
	t_binary		bin_cpy;

	if (!(fat = move_ptr(bin, bin->offset)))
		return (print_error("fat_arch error: abort,"));
	print_name(bin, fat, limit);
	ft_memcpy(&bin_cpy, bin, sizeof(*bin));
	if (bin_cpy.ptr == NULL)
		return (ERROR);
	bin_cpy.ptr = move_ptr(bin, reverse_32(bin->endian, fat->offset));
	if (bin_cpy.ptr == NULL)
		return (ERROR);
	bin_cpy.offset = 0;
	ret = handle_arch(&bin_cpy);
	return (ret);
}

int		search_for_cputype(t_binary *bin, uint32_t limit)
{
	uint32_t			count;
	unsigned long		tmp_off;
	struct fat_arch		*tmp;

	count = -1;
	tmp_off = bin->offset;
	while (++count < limit)
	{
		if (!(tmp = move_ptr(bin, tmp_off)))
			return (0);
		if (reverse_32(bin->endian, tmp->cputype) == CPU_TYPE_X86_64)
		{
			bin->offset = tmp_off;
			return (parse_fat_header_x32(bin, limit));
		}
		tmp_off += sizeof(struct fat_arch);
	}
	return (-1);
}

int		handle_fat(t_binary *bin)
{
	int					ret;
	uint32_t			count;
	uint32_t			limit;
	struct fat_header	*fat_header;

	count = -1;
	ret = SUCCESS;
	if (!(fat_header = (struct fat_header*)move_ptr(bin, bin->offset)))
		return (print_error("fat_header error: abort."));
	limit = reverse_32(bin->endian, fat_header->nfat_arch);
	bin->offset += sizeof(*fat_header);
	if ((ret = search_for_cputype(bin, limit)) != -1)
		return (ret);
	while (++count < limit)
	{
		if ((ret = parse_fat_header_x32(bin, limit)) != SUCCESS)
			return (ret);
		bin->offset += sizeof(struct fat_arch);
	}
	return (ret);
}
