/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:41:13 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/25 21:27:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

int		check_input(struct stat input)
{
	/* refaire le check input */
	if (input.st_mode & S_IFDIR)
	{
		ft_putendl_fd("error: file is a directory", STDERR_FILENO);
		return (ERROR);
	}
	if (input.st_mode & S_IRUSR)
	{
		ft_putendl_fd("test", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int		setup_struct(t_binary *bin, const char *path, int fd, struct stat *stat)
{
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putendl_fd("error: wrong input", STDERR_FILENO);
		return (ERROR);
	}
	if ((fstat(fd, stat)) == -1)
	{
		ft_putendl_fd("error: fstat failed", STDERR_FILENO);
		return (ERROR);
	}
	if ((bin->ptr = mmap(0, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("error: can't allocate ressources to load given binary", STDERR_FILENO);
		return (ERROR);
 	}
	bin->offset = 0;
	bin->sym = NULL;
	bin->sect = NULL;
	return (SUCCESS);
}


int		clean_struct(t_binary *bin, struct stat stat)
{
	if (bin->ptr != NULL)
	{
		if (munmap(bin->ptr, stat.st_size) != 0)
		{
			ft_putendl_fd("error: can't deallocate given binary", STDERR_FILENO);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
