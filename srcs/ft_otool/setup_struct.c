/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:41:13 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 15:55:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		setup_struct(t_binary *bin, struct stat *stat)
{
	int fd;

	if ((fd = open(bin->path, O_RDONLY)) == -1)
		return (print_error("error: open failed. abort."));
	if ((fstat(fd, stat)) == -1)
		return (print_error("error: fstat failed. abort."));
	if (stat->st_mode & S_IFDIR)
		return (print_error("error: it's a directory."));
	if (stat->st_size < 1)
		return (ERROR);
	if ((bin->ptr = mmap(\
			0, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (print_error("errpr: mmap failed. abort."));
	close(fd);
	bin->end = (bin->ptr + stat->st_size);
	return (SUCCESS);
}

int		clean_struct(t_binary *bin, struct stat stat)
{
	if (bin->ptr != NULL)
	{
		if (munmap(bin->ptr, stat.st_size) != 0)
			return (print_error("error: can't free the file :(."));
	}
	return (SUCCESS);
}
