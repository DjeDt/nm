/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:29:19 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 16:23:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	setup_struct_value(t_binary *bin, char *path)
{
	bin->endian = 0;
	bin->offset = 0;
	bin->ptr = NULL;
	bin->end = NULL;
	bin->path = path;
}

int		handle_arch(t_binary *bin)
{
	int				ret;
	unsigned int	magic;

	ret = SUCCESS;
	bin->endian = FALSE;
	magic = *(unsigned int*)bin->ptr;
	if (magic == MH_CIGAM_64 || magic == MH_CIGAM || magic == FAT_CIGAM)
		bin->endian = TRUE;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		ret = handle_x64(bin);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		ret = handle_x32(bin);
	else
		ret = print_error("error: unknow architecture. abort.");
	return (ret);
}

int		ft_otool(t_binary *bin, char *path)
{
	int			ret;
	struct stat	stat;

	setup_struct_value(bin, path);
	if (setup_struct(bin, &stat) != SUCCESS)
		return (ERROR);
	ret = handle_arch(bin);
	clean_struct(bin, stat);
	return (ret);
}

int		main(int ac, char **av)
{
	int			count;
	t_binary	bin;

	count = 1;
	while (count < ac)
	{
		if (ft_otool(&bin, av[count]) != SUCCESS)
			return (ERROR);
		count++;
	}
	return (SUCCESS);
}
