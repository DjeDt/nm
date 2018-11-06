/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:41:13 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/06 18:33:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	free_sect(t_section **section)
{
	t_section	*of;
	t_section	*tmp;

	of = (*section);
	while (of != NULL)
	{
		tmp = of->next;
		free(of);
		of = tmp;
	}
	(*section) = NULL;
}

void	free_sym(t_symbol **symbol)
{
	t_symbol	*of;
	t_symbol	*tmp;

	of = (*symbol);
	while (of != NULL)
	{
		tmp = of->next;
		free(of);
		of = tmp;
	}
	(*symbol) = NULL;
}

int		setup_struct(t_binary *bin, struct stat *stat)
{
	int fd;

	if ((fd = open(bin->path, O_RDONLY)) == -1)
		return (handle_error(bin->path, NOT_ALLOWED, ERR_DIR_NA));
	if ((fstat(fd, stat)) == -1)
		return (handle_error(bin->path, FSTAT_ERR, FSTAT_ERR_STR));
	if (stat->st_mode & S_IFDIR)
		return (handle_error(bin->path, IS_DIR, ERR_DIR_STR));
	if (stat->st_size < 1)
		return (ERROR);
	if ((bin->ptr = mmap(0, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error(bin->path, MMAP_ERR, MMAP_ERR_STR));
	close(fd);
	return (SUCCESS);
}

int		clean_struct(t_binary *bin, struct stat stat)
{
	if (bin->ptr != NULL)
	{
		if (munmap(bin->ptr, stat.st_size) != 0)
			handle_error(bin->path, MUNMAP_ERR, MUNMAPP_ERR_STR);
	}
	return (SUCCESS);
}
