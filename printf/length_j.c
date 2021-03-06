/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_j.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:42:55 by bchan             #+#    #+#             */
/*   Updated: 2018/02/19 12:57:56 by bchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*pull_intmax(t_print *form, va_list ap)
{
	intmax_t	arg;
	char		*result;

	arg = va_arg(ap, intmax_t);
	result = ft_max_itoa(arg);
	result = modify_string(form, result);
	return (result);
}

char	*pull_uintmax(t_print *form, va_list ap, char c)
{
	uintmax_t	arg;
	char		*result;
	int			i;

	arg = va_arg(ap, uintmax_t);
	if (c == 'u')
		result = ft_unsigned_itoa(arg);
	if (c == 'o')
		result = ft_octal_convert(arg);
	if (c == 'x')
		result = ft_hex_convert(arg);
	if (c == 'X')
	{
		i = 0;
		result = ft_hex_convert(arg);
		while (result[i])
		{
			result[i] = (char)ft_toupper(result[i]);
			i++;
		}
	}
	result = modify_string(form, result);
	return (result);
}

char	*pull_intmaxp(t_print *form, va_list ap)
{
	intmax_t		*arg;

	arg = va_arg(ap, intmax_t *);
	*arg = form->printed;
	return (ft_strdup(""));
}

char	*length_j(t_print *form, va_list ap, char c)
{
	if (c == 'd' || c == 'i')
		return (pull_intmax(form, ap));
	if (c == 'u' || c == 'o' || c == 'x' || c == 'X')
		return (pull_uintmax(form, ap, c));
	if (c == 'n')
		return (pull_intmaxp(form, ap));
	return (length_none(form, ap, c));
}
