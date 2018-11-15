/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:28:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/11/15 14:41:57 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		print_error(char *error)
{
	if (error != NULL)
		ft_printf_fd(STDERR_FILENO, "%s\n", error);
	return (ERROR);
}
