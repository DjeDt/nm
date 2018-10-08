/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:28:45 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/08 18:57:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM
# define NM

# include "libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>

# define ERROR -1
# define SUCCESS 0

typedef struct	t_binary
{
	int			fd;
	char		*ptr;
	struct stat	input;
}				t_binary;

# define HEX "0123456789abcdef"

/* main struct */
int		setup_struct(t_binary *fileinfo, const char *path);
int		clean_struct(t_binary *fileinfo);

/* handle 64 */
int     handle_64(t_binary fileinfo);
int     handle_specific_64(t_binary fileinfo);

/* handle 32 */
int     handle_32(t_binary fileinfo);
int     handle_specific_32(t_binary fileinfo);

/* utils */
void	ft_puthex(unsigned long l);

#endif
