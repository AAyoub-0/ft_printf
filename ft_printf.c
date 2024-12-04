/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:22 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/04 13:40:09 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t  num_len_base(long long num, int base_len)
{
        size_t  size;

        size = 0;
        if (num < 0)
        {
                size++;
                num = -num;
        }
        while (num > 0)
        {
                num = num / base_len;
                size++; 
        }
        return (size);
}

int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == ' '
		|| c == '+');
}

void	trait_flags(const char **str, t_flags *flags)
{
	set_flags(flags);
	while (is_flag(*(*str)))
	{
		if (*(*str) == '-')
			flags->minus = 1;
		if (*(*str) == '0')
			flags->zero = 1;
		if (*(*str) == '.')
			flags->precision = 1;
		if (*(*str) == '#')
			flags->hash = 1;
		if (*(*str) == ' ')
			flags->space = 1;
		if (*(*str) == '+')
			flags->plus = 1;
		(*str)++;
	}
	if (ft_isdigit(*(*str)))
		flags->padding = get_number(str);
	if (*(*str) == '.' && flags->precision == -1)
	{
		(*str)++;
		flags->precision = get_number(str);
	}
	flags->specifier = *(*str);
}

int     print_flags(t_flags flags, va_list args)
{
        if (flags.specifier == '%')
                return (print_nchar('%', 1));
        if (flags.specifier == 'c')
                return (print_nchar((char)va_arg(args, int), 1));
        if (flags.specifier == 's')
                return (print_flags_str(flags, args));
        if (flags.specifier == 'd' || flags.specifier == 'i')
                return (print_flags_snbase(flags, va_arg(args, int), "0123456789"));
        if (flags.specifier == 'u')
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789"));
        if (flags.specifier == 'x')
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789abcdef"));
        if (flags.specifier == 'X')
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789ABCDEF"));
        if (flags.specifier == 'p')
                return (print_flags_unbase(flags, (unsigned long)va_arg(args, void *), "0123456789abcdef"));
        return (0);
}

int     ft_printf(const char *format, ...)
{
        va_list args;
        t_flags flags;
        int     printed;

        va_start(args, format);
        printed = 0;
        while (*format)
        {
                if (*format == '%')
                {
                        format++;
                        trait_flags(&format, &flags);
                        printed += print_flags(flags, args);
                }
                else
                        printed += write(1, format, 1);
                format++;
        }
        va_end(args);
        return (printed);
}

// int main()
// {
//         int     ft_result;
//         int     result;
//         // char    world[] = "World"; 
//         // char    w = 'w';
//         // int     psn = 255;
//         // int     nsn = -255;
//         // unsigned int    pun = -255;
//         // unsigned int    sun = INT_MAX;

//         // puts("--------- Char test ----------\n");
//         // result = printf("Hello %corld\n", w);
//         // ft_result = ft_printf("Hello %corld\n", w);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- String test ----------\n");
//         // result = printf("Hello %s\n", world);
//         // ft_result = ft_printf("Hello %s\n", world);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Int test ----------\n");
//         // result = printf("Hello %d\n", INT_MIN);
//         // ft_result = ft_printf("Hello %d\n", INT_MIN);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %d\n", nsn);
//         // ft_result = ft_printf("Hello %d\n", nsn);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %u\n", pun);
//         // ft_result = ft_printf("Hello %u\n", pun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %u\n", sun);
//         // ft_result = ft_printf("Hello %u\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Hex test ----------\n");
//         // result = printf("Hello %x\n", sun);
//         // ft_result = ft_printf("Hello %x\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Pointers test ----------\n");
//         // result = printf("Hello %p<end\n", &sun);
//         // ft_result = ft_printf("Hello %p<end\n", &sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Pointers test ----------\n");
//         // result = printf("Hello %p<end\n", (void *)LONG_MAX);
//         // ft_result = ft_printf("Hello %p<end\n", LONG_MAX);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %10.5d<end\n", sun);
//         // ft_result = ft_printf("Hello %10.5d<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-10.5d<end\n", sun);
//         // ft_result = ft_printf("Hello %-10.5d<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %10.5u<end\n", sun);
//         // ft_result = ft_printf("Hello %10.5u<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-10.5u<end\n", sun);
//         // ft_result = ft_printf("Hello %-10.5u<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-#50.5x<end\n", sun);
//         // ft_result = ft_printf("Hello %-#50.5x<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with invalid specifier ----------\n");
//         // result = printf("Hello %50-.5i<end\n", sun);
//         // ft_result = ft_printf("Hello %50-.5i<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         return (0);
// }