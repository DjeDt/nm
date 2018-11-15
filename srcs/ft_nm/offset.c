/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:27:57 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:14:27 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint16_t		reverse_16(int endian, uint16_t x)
{
	uint16_t y;

	y = x;
	if (endian == TRUE)
		return ((y << 8) | ((y >> 8) & 0xFF));
	return (y);
}

uint32_t		reverse_32(int endian, uint32_t x)
{
	uint32_t y;

	y = x;
	if (endian == TRUE)
	{
		y = ((y << 8) & 0xFF00FF00) | ((y >> 8) & 0xFF00FF);
		return (y << 16) | (y >> 16);
	}
	return (y);
}

uint64_t		reverse_64(int endian, uint64_t x)
{
	uint64_t y;

	y = x;
	if (endian == TRUE)
	{
		y = ((y << 8) & 0xFF00FF00FF00FF00U) \
			| ((y >> 8) & 0x00FF00FF00FF00FFU);
		y = ((y << 16) & 0xFFFF0000FFFF0000U) \
			| ((y >> 16) & 0x0000FFFF0000FFFFU);
		return ((y << 32) | (y >> 32));
	}
	return (y);
}

void			*move_ptr(t_binary *bin, uint32_t size)
{
	if (bin->ptr + size > bin->end)
		return (NULL);
	return (bin->ptr + size);
}
