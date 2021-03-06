/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:44:29 by bchan             #+#    #+#             */
/*   Updated: 2018/02/21 13:12:40 by bchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*wchar_dup(wchar_t chr)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strnew(4);
	if (chr < 0x80)
		tmp[0] = chr;
	else
	{
		if (chr < 0x800)
			tmp[i++] = ((chr & (0x1f << 6)) >> 6) | 0xC0;
		else
		{
			if (chr < 0x10000)
				tmp[i++] = ((chr >> 12) & 0xf) | 0xE0;
			else
			{
				tmp[i++] = ((chr >> 18) & 7) | 0xF0;
				tmp[i++] = ((chr >> 12) & 0x3f) | 0x80;
			}
			tmp[i++] = ((chr >> 6) & 0x3f) | 0x80;
		}
		tmp[i++] = (chr & 0x3f) | 0x80;
	}
	return (tmp);
}

char	*wstr_dup(wchar_t *str)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	while (*str)
	{
		temp = wchar_dup(*str);
		ft_strpstr(&result, temp);
		ft_strdel(&temp);
		str++;
	}
	return (result);
}

char	*pull_mod(t_print *form)
{
	char *result;

	result = ft_strdup("%");
	result = modify_string(form, result);
	return (result);
}

char	*pull_double(t_print *form, va_list ap, char c)
{
	double	arg;
	char	*result;

	arg = va_arg(ap, double);
	if (c == 'a' || c == 'A')
		result = ft_dtoa(arg, 0, 2L);
	else
		result = ft_dtoa(arg, 0, 10L);
	result = modify_string(form, result);
	return (result);
}

char	*length_none(t_print *form, va_list ap, char c)
{
	if (c == 'd' || c == 'i' || c == 'c')
		return (pull_int(form, ap, c));
	if (c == 'u' || c == 'o' || c == 'x' || c == 'X')
		return (pull_un_int(form, ap, c));
	if (c == 's')
		return (pull_string(form, ap));
	if (c == 'p')
		return (pull_voidp(form, ap));
	if (c == 'n')
		return (pull_intp(form, ap));
	if (c == 'D' || c == 'U' || c == 'O' || c == 'C' || c == 'S')
		return (length_l(form, ap, c));
	if (c == '%')
		return (pull_mod(form));
	if (c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g' || c == 'G')
		return (pull_double(form, ap, c));
	return (NULL);
}
