/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:05:21 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/24 14:04:53 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "mlx/mlx.h"
#include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 500
#define height 500
#define N_TEX 0
#define S_TEX 1
#define E_TEX 2
#define W_TEX 3
#define SP_TEX 4
#define numSprites 8

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		**buf;
	double	zBuffer[width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_esc;
}				t_info;

typedef struct		s_pair
{
	//distance
	double		first;
	//order
	int			second;
}				t_pair;

struct Sprite
{
	double 		x;
	double		y;
	int			texture;
};

struct Sprite sprite[numSprites] =
{

	{20.5, 11.5, 4}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 4},
	{10.0,4.5, 4},
	{10.0,12.5, 4},
	{3.5, 6.5, 4},
	{3.5, 20.5, 4},
	{3.5, 14.5, 4},
	{14.5,20.5, 4},

	//row of pillars in front of wall: fisheye test
	// {18.5, 10.5, 9},
	// {18.5, 11.5, 9},
	// {18.5, 12.5, 9},

	//some barrels around the map
	// {21.5, 1.5, 8},
	// {15.5, 1.5, 8},
	// {16.0, 1.8, 8},
	// {16.2, 1.2, 8},
	// {3.5,  2.5, 8},
	// {9.5, 15.5, 8},
	// {10.0, 15.1,8},
	// {10.5, 15.8,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

void		sort_order(t_pair *orders, int amount)
{
	t_pair tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void		sortSprites(int *order, double *dist, int amount)
{
	t_pair * sprites;

	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void		key_update(t_info *info);

int	worldMap[mapWidth][mapHeight] =
						{
							{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * (info->img.size_l / 4) + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img_ptr, 0, 0);
}

void			calc(t_info *info)
{
	int		x;

	x = 0;
	while (x < width)
	{
		double	cameraX = 2 * x / (double)width - 1;
		double	rayDirX = info->dirX + info->planeX * cameraX;
		double	rayDirY = info->dirY + info->planeY * cameraX;

		int		mapX = (int)info->posX;
		int		mapY = (int)info->posY;

		double	sideDistX;
		double	sideDistY;

		double	deltaDistX = fabs(1 / rayDirX);
		double	deltaDistY = fabs(1 / rayDirY);
		double	perpWallDist;

		int		stepX;
		int		stepY;

		int		hit = 0;
		int		side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		int	lineHeight = (int)(height / perpWallDist);

		int	drawStart = -lineHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;

		int texNum;
		//east
		if ( rayDirY > 0 && side == 1)
			texNum = N_TEX;
		else if (rayDirY < 0 && side == 1)
			texNum = S_TEX;
		else if (rayDirX > 0 && side == 0)
			texNum = E_TEX;
		else if (rayDirX < 0 && side == 0)
			texNum = W_TEX;
		else
			texNum = -1;
		// int	texNum = worldMap[mapX][mapY] - 1;

		double wallX;
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int	texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth -texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;

		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for (int j = 0; j < height / 2; j++)
		{
			info->buf[j][x] = 120 * 65536 + 205 * 256 + 255;
			info->buf[height - 1 - j][x] = 80 * 65536 + 80 * 256 + 80;
		}
		for (int y = drawStart; y < drawEnd; y++)
		{
			int	texY = fmin((int)texPos, texHeight - 1);
			texPos += step;
			int	color = info->texture[texNum][texHeight * texY + texX];
			info->buf[y][x] = color;
		}
		info->zBuffer[x] = perpWallDist;
		x++;
	}
	for (int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->posX - sprite[i].x) * (info->posX - sprite[i].x) + (info->posY - sprite[i].y) * (info->posY - sprite[i].y));
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);

	for (int i = 0; i < numSprites; i++)
	{
		double spriteX = sprite[spriteOrder[i]].x - info->posX;
		double spriteY = sprite[spriteOrder[i]].y - info->posY;

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY);

		int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));

		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0

		int vMoveScreen = (int)(vMove / transformY);

		int spriteHeight = (int)fabs((height / transformY) / vDiv);

		int drawStartY = -spriteHeight / 2 + height / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + height / 2 + vMoveScreen;
		if (drawEndY >= height)
			drawEndY = height - 1;

		int spriteWidth = (int)fabs((height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= width)
			drawEndX = width - 1;

		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			if (transformY > 0 && stripe > 0 && stripe < width && transformY < info->zBuffer[stripe])
			for (int y = drawStartY; y < drawEndY; y++)
			{
				int d = (y - vMoveScreen) * 256 - height * 128 + spriteHeight * 128;
				int texY = ((d * texHeight) / spriteHeight) / 256;
				// int color = info->texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX];
				int color = info->texture[SP_TEX][texWidth * texY + texX];
				if ((color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = color;
			}
		}
	}
}

int				main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->key_s)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (info->key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (info->key_esc)
		exit(0);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit (0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

int 	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit (0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}

void			load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img_ptr);
}

void			load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[N_TEX], "textures/kuma.xpm", &img);
	load_image(info, info->texture[S_TEX], "textures/minami.xpm", &img);
	load_image(info, info->texture[E_TEX], "textures/east.xpm", &img);
	load_image(info, info->texture[W_TEX], "textures/nishi.xpm", &img);
	load_image(info, info->texture[SP_TEX], "textures/barrel.xpm", &img);
}

int				main(void)
{
	t_info	info;
	info.mlx = mlx_init();

	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.00;
	info.planeY = 0.66;
	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;

	if (!(info.buf = (int **)malloc(sizeof(int *) * height)))
		return (-1);
	for (int i = 0; i < height; i++)
	{
		if (!(info.buf[i] = (int *)malloc(sizeof(int) * width)))
			return (-1);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			info.buf[i][j] = 0;
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 5)))
		return (-1);
	for (int i = 0; i < 5; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
			info.texture[i][j] = 0;
	}

	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.win = mlx_new_window(info.mlx, width, height, "my_mlx");

	info.img.img_ptr = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
