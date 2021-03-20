/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:23:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/20 13:25:02 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			ft_free_path(t_all *all)
{
	if (all->path_tex.north)
		free(all->path_tex.north);
	if (all->path_tex.south)
		free(all->path_tex.south);
	if (all->path_tex.west)
		free(all->path_tex.west);
	if (all->path_tex.east)
		free(all->path_tex.east);
	if (all->path_tex.sprite)
		free(all->path_tex.sprite);
}

void			ft_exit(t_all *all, char **line)
{
	ft_free_path(all);
	if (line != NULL)
		free(*line);
	if (all->sprite_info.order != NULL)
		free(all->sprite_info.order);
	exit(0);
}

//error
void			ft_put_error_and_exit(t_all *all, char **line, char *s)
{
	write(1, "\e[31mError\e[m\n", 15);
	ft_putstr_fd(s, 2);
	ft_exit(all, line);
}
