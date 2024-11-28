/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:24:25 by aboumall          #+#    #+#             */
/*   Updated: 2024/11/26 16:09:33 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF
# define LIBFTPRINTF

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
#include "../libft/libft.h"

static char    *flags = "-0.# +";

typedef struct s_flags {
        int minus;
        int plus;
        int zero;
        int space;
        int hash;
        int padding;
        int precision;
        char specifier;
} t_flags;

#endif