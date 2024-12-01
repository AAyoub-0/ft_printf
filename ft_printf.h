/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayoub <aayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:24:25 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/01 18:03:31 by aayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

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

int		ft_printf(const char *format, ...);

#endif