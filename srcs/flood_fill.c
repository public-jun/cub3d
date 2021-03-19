/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:22:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/19 22:23:08 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//ft_flood_fill
void			ft_flood_fill(t_all *all, int x, int y, char target, char replace)
{
	char		node;

	if (y < 0 || MAP_HEIGHT - 1 < y || x < 0 || MAP_WIDTH - 1 < x)
		return ;
	node = all->map.char_map[y][x];

	if (target == replace)
		return ;
	else if (node == 'x')
		ft_put_error_and_exit(all, NULL, "This map is not close!\n");
	else if (node != target)
		return ;
	else
		all->map.char_map[y][x] = replace;

	ft_flood_fill(all, x, y - 1, target, replace);
	ft_flood_fill(all, x, y + 1, target, replace);
	ft_flood_fill(all, x - 1, y, target, replace);
	ft_flood_fill(all, x + 1, y, target, replace);
}
