/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:19:12 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/19 22:20:48 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//map以外のflagが全て立っている
int				ft_flag_on_expect_map(t_all *all)
{
	if (all->flag.r == 1 && all->flag.no == 1 && all->flag.so == 1 && all->flag.we == 1 && all->flag.ea == 1 && all->flag.s == 1 && all->flag.f == 1 && all->flag.c == 1)
		return (1);
	else
		return (0);
}

//charmap上での座標
void			ft_store_sprite_player_coordinate(t_all *all, char **line, int y, int x)
{
	if ((*line)[x] == 'N' || (*line)[x] == 'S' || (*line)[x] == 'E' || (*line)[x] == 'W')
	{
		if (all->map.p_x == 0 && all->map.p_y == 0)
		{
			all->map.p_x = x + 1;
			all->map.p_y = y;
		}
	}
}

//lineを1行char
void			ft_store_line_with_map(t_all *all, char **line)
{
	int			x;

	x = 0;
	while ((x + 1 < MAP_WIDTH - 1) && ((*line)[x] != '\0'))
	{
		if ((*line)[x] == ' ')
			(*line)[x] = '0';
		if ((*line)[x] == 'N' || (*line)[x] == 'S' || (*line)[x] == 'E' || (*line)[x] == 'W' || (*line)[x] == '2')
			ft_store_sprite_player_coordinate(all, line, all->map.tmp_y, x);
		all->map.char_map[all->map.tmp_y][x + 1] = (*line)[x];
		x++;
	}
	all->map.tmp_y++;
}

//lineがspace,0,1,2,N,S,W,Eで構成されているか
void			ft_judge_possible_chars(t_all *all, char **line)
{
	int			i;

	i = 0;
	while ((*line)[i])
	{
		if (((*line)[i] == 'N' || (*line)[i] == 'S' || (*line)[i] == 'W' || (*line)[i] == 'E') && all->map.pflag == 1)
			ft_put_error_and_exit(all, line, "Set only one player coordinates\n");
		if (!((*line)[i] == ' ' || (*line)[i] == '0' || (*line)[i] ==  '1' || (*line)[i] == '2' || (*line)[i] == 'N' || (*line)[i] == 'S' || (*line)[i] == 'W' || (*line)[i] == 'E'))
			ft_put_error_and_exit(all, line, "The map is be composed of inpossible characters\n");
		if ((*line)[i] == 'N' || (*line)[i] == 'S' || (*line)[i] == 'W' || (*line)[i] == 'E')
			all->map.pflag = 1;
		i++;
	}
}

//mapの終わりを判断する

//mapの始まりと終わりを確認
int				ft_in_the_process_of_forming_map(t_all *all, char **line)
{

	if ((*line)[0] == '\0' && all->map.start == 0)
		return (-1);
	if (all->map.start == 0)
	{
		all->map.start = 1;
		return (1);
	}
	return (0);
}
