/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:32:52 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/08 14:31:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

uint32_t reverse(int32_t x)
{
	uint8_t		data[4];

    ft_memcpy(&data, &x, sizeof(data));
	return ((uint32_t) data[3] << 0) | ((uint32_t) data[2] << 8)	\
		| ((uint32_t) data[1] << 16) | ((uint32_t) data[0] << 24);
}

uint32_t reverse2(int32_t x)
{
	uint8_t		data[4];

    ft_memcpy(&data, &x, sizeof(data));
	return ((uint32_t) data[0] << 0) | ((uint32_t) data[1] << 8)	\
		| ((uint32_t) data[2] << 16) | ((uint32_t) data[3] << 24);
}

int		handle_fat_endian(t_binary *bin, struct stat stat)
{
	struct fat_header	*fat;

	fat = (struct fat_header*)((void*)bin->ptr);
	(void)stat;
	return (0);
}

int		handle_fat(t_binary *bin, struct stat stat)
{
	(void)stat;
	uint32_t			x;
	struct fat_header	*fat;

	fat = (struct fat_header*)((void*)bin->ptr);
//	x = (uint32_t)move_offset_x32(bin, stat, fat->magic);
	x = 0;
	if (x == FAT_MAGIC)
		ft_putendl("32");//		handle_fat_x32();
	else if (x == FAT_MAGIC_64)
		ft_putendl("64");
	return (SUCCESS);
}
