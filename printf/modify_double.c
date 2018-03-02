/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:13:15 by bchan             #+#    #+#             */
/*   Updated: 2018/02/23 18:25:23 by bchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	truncate_dec(char *result, int n)
{
	int	i;

	i = 0;
	while (result[i] && result[i] != '.')
		i++;
	while (n-- >= 0)
		i++;
	round_up(result, i);
	result[i] = '\0';
}

void	swap(char *result, int i, int j)
{
	char c;

	c = result[i];
	result[i] = result[j];
	result[j] = c;
}

char	*add_exp(char *result, int count)
{
	char *temp;

	if (count >= 0)
	{
		ft_strpchar(&result, '+');
		if (count < 10)
			ft_strpchar(&result, '0');
		temp = ft_itoa(count);
		ft_strpstr(&result, temp);
	}
	else
	{
		ft_strpchar(&result, '-');
		if (count > -10)
			ft_strpchar(&result, '0');
		temp = ft_itoa(count * -1);
		ft_strpstr(&result, temp);
	}
	ft_strdel(&temp);
	return (result);
}

char	*sci_convert(char *str, int n)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (ft_atoi(str) == 0 && ft_atoi(&str[i + 1]) == 0)
		return (print_zero(str, n));
	while (i >= 3 || (*str != '-' && i >= 2))
	{
		swap(str, i, i - 1);
		count++;
		i--;
	}
	while ((*str == '0' || (*str == '-' && *(str + 1) == '0')) && str[i])
	{
		swap(str, i, i + 1);
		ft_memmove(&str[i - 1], &str[i], ft_strlen(&str[i]) + 1);
		count--;
	}
	truncate_dec(str, n);
	ft_strpchar(&str, 'e');
	str = add_exp(str, count);
	return (str);
}

char	*modify_double(t_print *form, char *result)
{
	int		i;
	char	*temp;

	if (form->precision == -1)
		i = 6;
	else
		i = form->precision;
	if (form->spec == 'f' || form->spec == 'F')
		truncate_dec(result, i);
	else if (form->spec == 'e' || form->spec == 'E')
		result = sci_convert(result, i);
	else if (form->spec == 'g' || form->spec == 'G')
		result = find_shortest(form, result);
	if (form->spec == 'F' || form->spec == 'E' || form->spec == 'G')
		ft_capitalize(result);
	if (!(ft_strchr(form->flags, '#')) && form->precision == 0 && form->spec
			!= 'g' && form->spec != 'G')
	{
		temp = ft_strchr(result, '.');
		ft_memmove(temp, temp + 1, ft_strlen(temp));
	}
	return (result);
}
