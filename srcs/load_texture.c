/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:21:10 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/22 15:21:50 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			all->info.texture[i][all->img_width * y + x] = all->img.data[all->img_width * y + x];
			x++;
		}
		y++;
	}
}

void			load_image(t_all *all, char *path)
{
	static int	i;
	int			x;

	if (!(all->img.img_ptr = mlx_xpm_file_to_image(all->info.mlx, path, &all->img.img_width, &all->img.img_height))
		ft_put_error_and_exit(all, NULL, "Invalid path\n");
	if (!(all->img.data = (int *)mlx_get_data_addr(al->img.img_ptr, &all->img.bpp, &all->img.size_l, all->img.endian))
		ft_put_error_and_exit(all, NULL, "mlx_get_data_addr failed\n");
	if (!(all->info.texture[i] = (int *)malloc(sizeof(int) * (all->img.img_width * all->img.img_height))))
		ft_put_error_and_exit(all, NULL, "Cant allocate memory\n");
	x = 0;
	while (x < all->img.img_width * all->img.img_height)
		all->info.texture[i][x++] = 0;
	set_texture_in_load_image(all, i)
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
