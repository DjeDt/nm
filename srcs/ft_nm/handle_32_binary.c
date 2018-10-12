/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:56:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/08 18:21:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

int		handle_specific_32(t_binary fileinfo)
{
	ft_putendl("specific 32 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}

int		handle_32(t_binary fileinfo)
{
	ft_putendl("32 bits binary");
	(void)fileinfo;
	return (SUCCESS);
}
