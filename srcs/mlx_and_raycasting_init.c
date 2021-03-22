/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_and_raycasting_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:21:20 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/22 21:41:52 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void			ft_key_init(t_key *key)
{
	key->a = 0;
	key->w = 0;
	key->s = 0;
	key->d = 0;
	key->esc = 0;
	key->left = 0;
	key->right = 0;
	//linux x
}

static void			ft_init_buf(t_all *all, int height, int width)
{
	int			i;
	int			j;

	if (!(all->info.buf = (int **)malloc(sizeof(int *) * height)))
		ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_buf\n");
	i = 0;
	while (i < all->win_r.y)
	{
		if (!(all->info.buf[i] = (int *)malloc(sizeof(int) * width)))
			ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_buf\n");
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
	if (!(all->info.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_put_error_and_exit(all, NULL, "Can't malloc in ft_init_texture\n");
}

void			ft_mlx_and_raycast_init(t_all *all)
{
	all->info.mlx = mlx_init();
	ft_key_init(&all->key);
	ft_init_buf(all, all->win_r.y, all->win_r.x);
	ft_init_texture(all);
	ft_load_texture(all);
	all->info.moveSpeed = 0.05;
	all->info.rotSpeed = 0.05;
	all->info.win = mlx_new_window(all->info.mlx, all->win_r.x, all->win_r.y, "cub3d");
	all->info.img.img_ptr = mlx_new_image(info.mlx, all->win_r.x, all->win_r.y);
	all->info.img.data = (int *)mlx_get_data_addr(all->info.img.img_ptr, &all->info.img.bpp, &all->info.img.size_l, &all->info.img.endian);
}
