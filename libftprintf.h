/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:24:25 by aboumall          #+#    #+#             */
/*   Updated: 2024/11/28 17:45:10 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF
# define LIBFTPRINTF

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

static char	*flags = "-0.# +";

typedef struct s_flags
{
	int		minus;
	int		plus;
	int		zero;
	int		space;
	int		hash;
	int		padding;
	int		precision;
	char	specifier;
}			t_flags;

#endif