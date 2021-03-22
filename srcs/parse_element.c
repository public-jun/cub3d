/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:46:38 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/22 17:06:44 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// input R
void			ft_parse_line_r(t_all *all, char **line)
{
	char		**tmp;

	if (all->flag.r == 1)
		ft_put_error_and_exit(all, line, "Set only one R\n");
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit(all, line, "Invalid R format\n");
	if ((ft_is_all_num(tmp[1])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters\n");
	all->win_r.x = ft_atoi_ex(tmp[1]);
	if ((ft_is_all_num(tmp[2])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters\n");
	all->win_r.y = ft_atoi_ex(tmp[2]);
	if (all->win_r.x < 1 || 1920 < all->win_r.x || all->win_r.y < 1 || 1080 < all->win_r.y)
		ft_put_error_and_exit(all, line, "Invalid value\n");
	if (tmp[3])
		ft_put_error_and_exit(all, line, "Invalid format\n");
	all->flag.r = 1;
	ft_free_all(tmp);
}

void			ft_parse_line_path(t_all *all, char **path, int *flag, char **line)
{
	char		*res;
	char		**tmp;


	tmp = NULL;
	if (*flag == 1)
		ft_put_error_and_exit(all, line, "Set only one each path\n");
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit(all, line, "Invalid format\n");
	if (!(res = ft_strdup(tmp[1])))
		ft_put_error_and_exit(all, line, "Invalid format\n");
	if (res[0] != '.' || res[1] != '/')
		ft_put_error_and_exit(all, line, "Invalid path\n");
	*path = res;
	*flag = 1;
	ft_free_all(tmp);
}

static void			ft_input_rgb(t_all *all, char **line, t_color *color, char **char_rgb)
{
	if ((ft_is_all_num(char_rgb[R])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters\n");
	color->r = ft_atoi_ex(char_rgb[R]);
	if ((ft_is_all_num(char_rgb[G])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters\n");
	color->g = ft_atoi_ex(char_rgb[G]);
	if ((ft_is_all_num(char_rgb[B])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters\n");
	color->b = ft_atoi_ex(char_rgb[B]);
	if (color->r < 0 || color->g < 0 || color->b < 0 || 255 < color->r || 255 < color->g || 255 < color->b )
		ft_put_error_and_exit(all, line, "Invalid value\n");
}

void			ft_parse_line_color(t_all *all, t_color *color, int *flag, char **line)
{
	char		**char_rgb;
	char 		**tmp;

	if (*flag == 1)
		ft_put_error_and_exit(all, line, "Set only one each color\n");
	tmp = NULL;
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit(all, line, "Invalid format\n");
	if (!(char_rgb = ft_split(tmp[1], ',')))
	{
		ft_free_all(tmp);
		ft_put_error_and_exit(all, line, "Invalid format\n");
	}
	ft_free_all(tmp);
	ft_input_rgb(all, line, color, char_rgb);
	if (char_rgb[3])
		ft_put_error_and_exit(all, line, "Invalid format\n");
	ft_free_all(char_rgb);
	color->rgb = color->r * 65536 + color->g * 256 + color->b;
	*flag = 1;
}
