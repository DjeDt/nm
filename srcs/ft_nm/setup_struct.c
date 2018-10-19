/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:41:13 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/15 18:37:02 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

int		check_input(struct stat input)
{
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
	else if (1)
		;
	else
		;
	return (SUCCESS);
}

int		setup_struct(t_binary *fileinfo, const char *path)
{
	if ((fileinfo->fd = open(path, O_RDONLY)) == -1)
	{
		ft_putendl_fd("error: wrong input", STDERR_FILENO);
		return (ERROR);
	}
	if ((fstat(fileinfo->fd, &fileinfo->input)) == -1)
	{
		ft_putendl_fd("error: fstat failed", STDERR_FILENO);
		return (ERROR);
	}
	/* if (check_input(fileinfo->input) == ERROR) */
	/* 	return (ERROR); */
	if ((fileinfo->ptr = mmap(0, fileinfo->input.st_size, PROT_READ, MAP_PRIVATE, fileinfo->fd, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("error: can't allocate ressources to load given binary", STDERR_FILENO);
		return (ERROR);
 	}
	fileinfo->offset = 0;
	return (SUCCESS);
}


int		clean_struct(t_binary *fileinfo)
{
	if (fileinfo->fd)
		close(fileinfo->fd);
	if (fileinfo->ptr)
	{
		if (munmap(fileinfo->ptr, fileinfo->input.st_size) != 0)
		{
			ft_putendl_fd("error: can't deallocate given binary", STDERR_FILENO);
			return (ERROR);
		}
	}
	return (SUCCESS);
}
