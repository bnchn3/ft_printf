/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:37:22 by bchan             #+#    #+#             */
/*   Updated: 2018/03/02 12:37:23 by bchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	swap(char *tmp1, char *tmp2)
{
	char c;

	c = *tmp1;
	*tmp1 = *tmp2;
	*tmp2 = c;
}
