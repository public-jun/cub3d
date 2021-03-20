/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:22:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/20 17:57:51 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//ft_flood_fill
void			ft_flood_fill(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
	char		node;

	if (y < 0 || MAP_HEIGHT + 1 < y || x < 0 || MAP_WIDTH + 1 < x)
		return ;
	node = map[y][x];

	if (node == 'x')
		ft_put_error_and_exit(all, NULL, "This map is not close!\n");
	else if (node != '0')
		return ;
	else
		map[y][x] = 'P';

	ft_flood_fill(all, map, x, y - 1);
	ft_flood_fill(all, map, x, y + 1);
	ft_flood_fill(all, map, x - 1, y);
	ft_flood_fill(all, map, x + 1, y);
}
