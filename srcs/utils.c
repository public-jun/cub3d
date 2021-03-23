/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:28:51 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/23 18:33:19 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_is_all_num(char *num)
{
	int			len;
	int			i;

	i = 0;
	len = (int)ft_strlen(num);
	while (ft_isdigit(num[i]))
		i++;
	if (i == len)
		return (0);
	return (-1);
}

int			ft_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
