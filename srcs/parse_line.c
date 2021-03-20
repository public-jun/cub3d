/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:36:53 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/20 17:35:51 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				ft_skip_null_and_space(char **line, int *i)
{
	if (!(*line)[*i])
		return (-1);
	while((*line)[*i] == ' ')
		(*i)++;
	if (!(*line)[*i])
		return (-1);
	return (0);
}

// param の条件分岐
void			ft_parse_line_param(t_all *all, char **line)
{
	int			i;

	i = 0;
	if (ft_skip_null_and_space(line, &i) == -1)
		return ;
	if ((*line)[i] == 'R' && (*line)[i + 1] == ' ')
		ft_parse_line_r(all, line);
	else if ((*line)[i] == 'N' && (*line)[i + 1] == 'O' && (*line)[i + 2] == ' ')
		ft_parse_line_path(all, &all->path_tex.north, &all->flag.no, line);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == 'O' && (*line)[i + 2] == ' ')
		ft_parse_line_path(all, &all->path_tex.south, &all->flag.so, line);
	else if ((*line)[i] == 'W' && (*line)[i + 1] == 'E' && (*line)[i + 2] == ' ')
		ft_parse_line_path(all, &all->path_tex.west, &all->flag.we, line);
	else if ((*line)[i] == 'E' && (*line)[i + 1] == 'A' && (*line)[i + 2] == ' ')
		ft_parse_line_path(all, &all->path_tex.east, &all->flag.ea, line);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == ' ')
		ft_parse_line_path(all, &all->path_tex.sprite, &all->flag.s, line);
	else if ((*line)[i] == 'F' && (*line)[i + 1] == ' ')
		ft_parse_line_color(all, &all->color_f, &all->flag.f, line);
	else if ((*line)[i] == 'C' && (*line)[i + 1] == ' ')
		ft_parse_line_color(all, &all->color_c, &all->flag.c, line);
	// 	ft_parse_line_c(all, line, &i);

}

void			ft_count_sprite(t_all *all, char **line)
{
	int			i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '2')
			all->sprite_info.num++;
		i++;
	}
}

//line を charmap に格納
void			ft_parse_line_map(t_all *all, char **line)
{
	if (ft_in_the_process_of_forming_map(all, line) >= 0)
	{
		ft_judge_possible_chars(all, line);
		if ((MAP_WIDTH - 2< (int)ft_strlen(*line)) || (MAP_HEIGHT  - 2 < all->map.tmp_y))
			ft_put_error_and_exit(all, line, "Map size limits is exceeded\n");
		ft_count_sprite(all, line);
		ft_store_line_with_map(all, line);
	}
}

//map かそれ以外で判定
void			ft_parse_line(t_all *all, char **line)
{
		ft_parse_line_param(all, line);
	if (all->flag.except_map == 1)
		ft_parse_line_map(all, line);
	if (all->flag.except_map == 0)
		all->flag.except_map = ft_flag_on_expect_map(all);
}
