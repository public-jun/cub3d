/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:47:16 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/20 18:16:15 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//sprite座標
void			ft_store_sprite_coordinate(t_all *all, int x, int y)
{
	all->sprite_info.order[all->sprite_info.tmp].sp_x = x;
	all->sprite_info.order[all->sprite_info.tmp].sp_y = y;
	all->sprite_info.tmp++;
}

void			ft_store_player_dir(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
	if (map[y][x] == 'N')
	{
		all->player.dir_x = 0.0;
		all->player.dir_y = 1.0;
	}
	else if (map[y][x] == 'S')
	{
		all->player.dir_x = 0.0;
		all->player.dir_y = -1.0;
	}
	else if (map[y][x] == 'E')
	{
		all->player.dir_x = -1.0;
		all->player.dir_y = 0.0;
	}
	else if (map[y][x] == 'W')
	{
		all->player.dir_x = 1.0;
		all->player.dir_y = 0.0;
	}
}

void			ft_store_player_info(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
	all->player.pos_x = (double)(all->map.p_x);
	all->player.pos_y = (double)(all->map.p_y);
	ft_store_player_dir(all, map, x, y);
	all->player.plane_x = 0.0;
	all->player.plane_y = 0.660;
}

void			ft_get_info_from_map(t_all *all, char map[MAP_HEIGHT][MAP_WIDTH])
{
	int			x;
	int			y;
	char		tmp;

	y = 1;
	while (y < MAP_HEIGHT - 1)
	{
		x = 1;
		while (x < MAP_WIDTH - 1)
		{
			if (map[y][x] == '2')
				ft_store_sprite_coordinate(all, x, y);
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				ft_store_player_info(all, map, x, y);
				map[y][x] = '0';
			}
			tmp = map[y][x];
			all->map.int_map[y][x] = ft_atoi(&tmp);
			x++;
		}
		y++;
	}
}

void			ft_combine_input_and_output(t_all *all)
{
	all->sprite_info.order = (t_sprite*)malloc(sizeof(t_sprite) * all->sprite_info.num);
	if (all->sprite_info.order == NULL)
		ft_put_error_and_exit(all, NULL, "cant malloc!\n");
	ft_get_info_from_map(all, all->map.char_map);
}
