/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:03:09 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/23 18:30:57 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//cub 読み込み部分(gnl)
void			ft_read_cub(int fd, t_all *all)
{
	int			res;
	char		*line;

	line = NULL;
	res = 0;
	while((res = get_next_line(fd, &line)) > 0)
	{
		// printf("%8d : %s\n", res, line);
		ft_parse_line(all, &line);
		free(line);
	}
	if (res == 0 && all->flag.except_map == 0)
		ft_put_error_and_exit(all, &line, "This cub file is insufficient");
	// printf("%8d : %s\n", res, line);
	if (res == -1)
		ft_put_error_and_exit(all, &line, "Failed to read\n");
	free(line);
}

//.cub 判定
static int				ft_iscub(char *cub)
{
	int			len;

	len = (int)ft_strlen(cub);
	if (len > 4 && cub[len - 4] == '.' && cub[len - 3] == 'c' && cub[len - 2] == 'u' && cub[len - 1] == 'b')
		return (1);
	return (0);
}

void			floor_and_ceilling_casting(t_all *all)
{
	int			x;
	int			y;

	y = 0;
	while (y < all->win_r.y / 2)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->info.buf[y][x] = all->color_c.rgb;
			all->info.buf[all->win_r.y - 1 - y][x] = all->color_f.rgb;
			x++;
		}
		y++;
	}
}

void			ft_set_ray_data(t_all *all, t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)all->win_r.x - 1;
	ray->raydir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->raydir_y = player->dir_y + player->plane_x * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;

}

void			ft_check_raydir_and_set_sidedist(t_ray *ray, t_player *player)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

void			ft_find_collision_with_wall(t_ray *ray, t_map *map, t_player *player)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->int_map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->prepwalldist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->prepwalldist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
}

void			ft_calculate_wall_height_on_screen(t_all *all, t_ray *ray)
{
	ray->lineheight = (int)(all->win_r.y / ray->prepwalldist);
	ray->drawstart = - ray->lineheight / 2 + all->win_r.y / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + all->win_r.y / 2;
	if (ray->drawend >= all->win_r.y)
		ray->drawend = all->win_r.y - 1;
}

void			ft_set_direction_tex(t_ray *ray, t_tex *tex)
{
	if (ray->raydir_y > 0 && ray->side == 1)
		tex->num = N_TEX;
	else if (ray->raydir_y < 0 && ray->side == 1)
		tex->num = S_TEX;
	else if (ray->raydir_x > 0 && ray->side == 0)
		tex->num = E_TEX;
	else if (ray->raydir_x < 0 && ray->side == 0)
		tex->num = W_TEX;
	else
		tex->num = -1;
}

void			ft_attach_tex_size_for_screen(t_all *all, t_ray *ray, t_player *player, t_tex *tex)
{
	ray->wall_x = 0;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->prepwalldist * ray->raydir_x;
	else
		ray->wall_x = player->pos_x + ray->prepwalldist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex->tex_x = (int)(ray->wall_x * (double)tex->tex_width[tex->num]);
	if (ray->side == 0 && ray->raydir_x > 0)
		tex->tex_x = tex->tex_width[tex->num] - tex->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		tex->tex_x = tex->tex_width[tex->num] - tex->tex_x - 1;
	tex->step = 1.0 * tex->tex_height[tex->num] / ray->lineheight;
	tex->texpos = (ray->drawstart - all->win_r.y / 2 + ray->lineheight / 2) * tex->step;
}

void			ft_set_buf(t_ray *ray, t_tex *tex, t_info *info, int x)
{
	int			y;
	int			color;

	y = ray->drawstart;
	printf("max tex size %d\n", tex->tex_width[0] * tex->tex_height[0]);
	while (y < ray->drawend)
	{
		tex->tex_y = ft_min((int)tex->texpos, tex->tex_height[tex->num] - 1);
		tex->texpos += tex->step;
		color = info->texture[tex->num][tex->tex_width[tex->num] * tex->tex_y + tex->tex_x];
		// printf("%d\t", info->texture[tex->num][tex->tex_width[tex->num] * tex->tex_y + tex->tex_x]);
		//int_map[y][x] を map[x][y]にする
		info->buf[y][x] = color;
	}
	// info->z_buffer[x] = ray->prepwalldist;
}

void			ft_wall_casting(t_all *all)
{
	int			x;

	x = 0;
	while (x < all->win_r.x)
	{
		ft_set_ray_data(all, &all->ray, &all->player, x);
		ft_check_raydir_and_set_sidedist(&all->ray, &all->player);
		ft_find_collision_with_wall(&all->ray, &all->map, &all->player);
		ft_calculate_wall_height_on_screen(all, &all->ray);
		ft_set_direction_tex(&all->ray, &all->tex);
		ft_attach_tex_size_for_screen(all, &all->ray, &all->player, &all->tex);
		ft_set_buf(&all->ray, &all->tex, &all->info, x);
		x++;
	}
}

void			ft_draw_to_window(t_all *all)
{
	int			x;
	int			y;

	y = 0;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->info.img.data[y * (all->info.img.size_l / 4) + x] = all->info.buf[y][x];
			x++;
		}
		y++;
	}
}

int				ft_raycasting(t_all *all)
{
	floor_and_ceilling_casting(all);
	ft_wall_casting(all);
	ft_draw_to_window(all);
	// key_action(all);
	return (0);
}

int				main(int ac, char **av)
{
	t_all		all;
	int			fd;

	fd = 0;
	if ((ac == 2 && ft_iscub(av[1])) || ac == 3)
	{
		ft_init(&all);
		if ((fd = open(av[1], O_RDONLY)) <  0)
			ft_put_error_and_exit(&all, NULL, "Failed to open\n");
		ft_read_cub(fd, &all);
		ft_combine_input_and_output(&all);
		ft_flood_fill(&all, all.map.char_map, all.map.p_x, all.map.p_y);
		printf("player  :  (%lf, %lf)\n", all.player.pos_x, all.player.pos_y);
		printf("dir     :  (%lf, %lf)\n", all.player.dir_x, all.player.dir_y);
		printf("plane   :  (%lf, %lf)\n", all.player.plane_x, all.player.plane_y);
		for (int i = 0; i < all.sprite_info.num; i++)
			printf("sprite[%d]  :  (%d, %d)\n", i, all.sprite_info.order[i].sp_x, all.sprite_info.order[i].sp_y);
		close(fd);
		ft_mlx_and_raycast_init(&all);
		mlx_loop_hook(all.info.mlx, &ft_raycasting, &all);
		// mlx_hook(all.info.win, X_EVENT_KEY_PRESS, 0, &key_press, &all);
		// mlx_hook(all.info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &all);
		mlx_loop(all.info.mlx);
	}
	ft_free_path(&all);
}






// printf("\nset map\n\n");
		// for(int i = 0; i < MAP_HEIGHT; i++)
		// {
		// 	for(int j = 0; j < MAP_WIDTH; j++)
		// 		printf("%c", all.map.char_map[i][j]);
		// 	printf("\n");
		// }
		// printf("p_x    : %d\n", all.map.p_x);
		// printf("p_y    : %d\n", all.map.p_y);
// printf("win_r.x  : %d\n", all.win_r.x);
		// printf("win_r.y  : %d\n", all.win_r.y);
		// printf("NO       : %s\n", all.path_tex.north);
		// printf("flag_no  : %d\n", all.flag.no);
		// printf("SO       : %s\n", all.path_tex.south);
		// printf("flag_so  : %d\n", all.flag.so);
		// printf("WE       : %s\n", all.path_tex.west);
		// printf("flag_we  : %d\n", all.flag.we);
		// printf("EA       : %s\n", all.path_tex.east);
		// printf("flag_ea  : %d\n", all.flag.ea);
		// printf("S       : %s\n", all.path_tex.sprite);
		// printf("flag_s  : %d\n", all.flag.s);
		// printf("F       : %d, %d, %d\n", all.color_f.r, all.color_f.g, all.color_f.b);
		// printf("C       : %d, %d, %d\n", all.color_c.r, all.color_c.g, all.color_c.b);
		// printf("flag_f  : %d\n", all.flag.f);
		// printf("flag_c  : %d\n", all.flag.c);

		// printf("\nflood fill map\n\n");
		// for(int i = 0; i < MAP_HEIGHT; i++)
		// {
		// 	for(int j = 0; j < MAP_WIDTH; j++)
		// 		printf("%c", all.map.char_map[i][j]);
		// 	printf("\n");
		// }

		// printf("\nint map\n\n");
		// for(int i = 0; i < MAP_HEIGHT; i++)
		// {
		// 	for(int j = 0; j < MAP_WIDTH; j++)
		// 		printf("%d, ", all.map.int_map[i][j]);
		// 	printf("\n");
		// }
