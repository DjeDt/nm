/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:28:53 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/27 14:30:51 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"

int		handle_error(const char *input, int type, const char *error)
{
	if (type == IS_DIR)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", input, error);
	else if (type == NOT_ALLOWED)
		ft_printf_fd(STDERR_FILENO, "%s: %s", input, error);
	return (ERROR);
}
