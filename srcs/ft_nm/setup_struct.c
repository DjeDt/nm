/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:41:13 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 15:01:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

void	free_sect(t_section **section)
{
	t_section	**tmp;
	t_section	*nxt;

	tmp = section;
	nxt = NULL;
	while (*tmp != NULL)
	{
		nxt = (*section)->next;
		free(*tmp);
		(*tmp) = nxt;
	}
	/* tmp = (*section); */
	/* while (tmp != NULL) */
	/* { */
	/* 	nxt = tmp->next; */
	/* 	free(tmp); */
	/* 	tmp = nxt; */
	/* } */
}

void	free_sym(t_symbol **symbol)
{
	t_symbol	**tmp;
	t_symbol	*nxt;

	tmp = symbol;
	nxt = NULL;
	while ((*tmp) != NULL)
	{
		nxt = (*tmp)->next;
		free(*tmp);
		(*tmp) = nxt;
	}
	/* tmp = (*symbol); */
	/* while (tmp != NULL) */
	/* { */
	/* 	nxt = tmp->next; */
	/* 	free(tmp); */
	/* 	tmp = nxt; */
	/* } */
}

void	setup_struct_value(t_binary *bin)
{
	bin->offset = 0;
	bin->sym = NULL;
	bin->sect = NULL;
}

int		setup_struct(t_binary *bin, const char *path, int fd, struct stat *stat)
{
	if ((fd = open(path, O_RDONLY)) == -1)
		return (handle_error(path, NOT_ALLOWED, ERR_DIR_NA));
	if ((fstat(fd, stat)) == -1)
		return (handle_error(path, FSTAT_ERR, FSTAT_ERR_STR));
	if (stat->st_mode & S_IFDIR)
		return (handle_error(path, IS_DIR, ERR_DIR_STR));
	if ((bin->ptr = mmap(0, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error(path, MMAP_ERR, MMAP_ERR_STR));
	close(fd);
	setup_struct_value(bin);
	return (SUCCESS);
}

int		clean_struct(t_binary *bin, const char *path, struct stat stat)
{
	if (bin->ptr != NULL)
	{
		if (munmap(bin->ptr, stat.st_size) != 0)
			handle_error(path, MUNMAP_ERR, MUNMAPP_ERR_STR);
	}
	if (bin->sym)
		free_sym(&bin->sym);
	if (bin->sect != NULL)
		free_sect(&bin->sect);
	sleep(15);
	return (SUCCESS);
}
