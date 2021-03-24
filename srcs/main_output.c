/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:34:00 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/24 14:47:02 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// #include "key_macos.h"
// #include "includes/define.h"
// #include "includes/struct.h"
// #include <math.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #define X_EVENT_KEY_PRESS	2
// #define X_EVENT_KEY_RELEASE	3
// #define X_EVENT_KEY_EXIT	17




static void			ft_key_init(t_all *all)
{
	all->key.a = 0;
	all->key.w = 0;
	all->key.s = 0;
	all->key.d = 0;
	all->key.esc = 0;
	all->key.left = 0;
	all->key.right = 0;
	//linux x
}


static void			ft_init_buf(t_all *all, int height, int width)
{
	int			i;
	int			j;

	//free
	if (!(all->info.buf = (int **)malloc(sizeof(int *) * height)))
		ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_buf\n");
	i = 0;
	while (i < height)
	{
		if (!(all->info.buf[i] = (int *)malloc(sizeof(int) * width)))
			ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_buf\n");
		i++;
	}
	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			all->info.buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void			ft_init_texture(t_all *all)
{
	//free
	if (!(all->info.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_texture\n");
}

void			set_texture_in_load_image(t_all *all, int i)
{
	int			x;
	int			y;

	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			all->info.texture[i][all->img.img_width * y + x] = all->img.data[all->img.img_width * y + x];
			x++;
		}
		y++;
	}
}

void			load_image(t_all *all, char *path)
{
	static int	i;
	int			x;

	if (!(all->img.img_ptr = mlx_xpm_file_to_image(all->info.mlx, path, &all->img.img_width, &all->img.img_height)))
		ft_put_error_and_exit(all, NULL, "Invalid path\n");
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img_ptr, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit(all, NULL, "mlx_get_data_addr failed\n");
	if (!(all->info.texture[i] = (int *)malloc(sizeof(int) * (all->img.img_width * all->img.img_height))))
		ft_put_error_and_exit(all, NULL, "Cant allocate memory\n");
	x = 0;
	while (x < all->img.img_width * all->img.img_height)
		all->info.texture[i][x++] = 0;
	set_texture_in_load_image(all, i);
	all->tex.tex_width[i] = all->img.img_width;
	all->tex.tex_height[i] = all->img.img_height;
	i++;
	mlx_destroy_image(all->info.mlx, all->img.img_ptr);
}

void			ft_load_texture(t_all *all)
{
	load_image(all, all->path_tex.north);
	load_image(all, all->path_tex.south);
	load_image(all, all->path_tex.west);
	load_image(all, all->path_tex.east);
	load_image(all, all->path_tex.sprite);
}


void			ft_mlx_and_raycast_init(t_all *all)
{
	all->info.mlx = mlx_init();
	ft_key_init(all);
	ft_init_buf(all, all->win_r.y, all->win_r.x);
	ft_init_texture(all);
	ft_load_texture(all);
	all->info.moveSpeed = 0.05;
	all->info.rotSpeed = 0.05;
	all->info.win = mlx_new_window(all->info.mlx, all->win_r.x, all->win_r.y, "cub3d");


	all->info.img.img_ptr = mlx_new_image(all->info.mlx, all->win_r.x, all->win_r.y);
	all->info.img.data = (int *)mlx_get_data_addr(all->info.img.img_ptr, &all->info.img.bpp, &all->info.img.size_l, &all->info.img.endian);
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
	mlx_put_image_to_window(all->info.mlx, all->info.win, all->info.img.img_ptr, 0, 0);
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

	color  = 0;
	y = ray->drawstart;
	// printf("max tex size %d\n", tex->tex_width[0] * tex->tex_height[0]);
	while (y < ray->drawend)
	{
		tex->tex_y = fmin(tex->texpos, tex->tex_height[tex->num] - 1);
		tex->texpos += tex->step;
		color = info->texture[tex->num][tex->tex_width[tex->num] * tex->tex_y + tex->tex_x];
		// printf("%d\t", info->texture[tex->num][tex->tex_width[tex->num] * tex->tex_y + tex->tex_x]);
		//int_map[y][x] を map[x][y]にする
		info->buf[y][x] = color;
		y++;
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
