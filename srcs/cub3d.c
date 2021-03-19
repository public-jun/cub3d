/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:03:09 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/19 21:32:14 by jnakahod         ###   ########.fr       */
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

		printf("\nset map\n\n");
		for(int i = 0; i < MAP_HEIGHT; i++)
		{
			for(int j = 0; j < MAP_WIDTH; j++)
				printf("%c", all.map.char_map[i][j]);
			printf("\n");
		}
		printf("p_x    : %d\n", all.map.p_x);
		printf("p_y    : %d\n", all.map.p_y);

		all.map.char_map[all.map.p_y][all.map.p_x] = '0';
		ft_flood_fill(&all, all.map.p_x, all.map.p_y, '0', 'P');
		printf("win_r.x  : %d\n", all.win_r.x);
		printf("win_r.y  : %d\n", all.win_r.y);
		printf("NO       : %s\n", all.path_tex.north);
		printf("flag_no  : %d\n", all.flag.no);
		printf("SO       : %s\n", all.path_tex.south);
		printf("flag_so  : %d\n", all.flag.so);
		printf("WE       : %s\n", all.path_tex.west);
		printf("flag_we  : %d\n", all.flag.we);
		printf("EA       : %s\n", all.path_tex.east);
		printf("flag_ea  : %d\n", all.flag.ea);
		printf("S       : %s\n", all.path_tex.sprite);
		printf("flag_s  : %d\n", all.flag.s);
		printf("F       : %d, %d, %d\n", all.color_f.r, all.color_f.g, all.color_f.b);
		printf("C       : %d, %d, %d\n", all.color_c.r, all.color_c.g, all.color_c.b);
		printf("flag_f  : %d\n", all.flag.f);
		printf("flag_c  : %d\n", all.flag.c);

		printf("\nflood fill map\n\n");
		for(int i = 0; i < MAP_HEIGHT; i++)
		{
			for(int j = 0; j < MAP_WIDTH; j++)
				printf("%c", all.map.char_map[i][j]);
			printf("\n");
		}

	}
	close(fd);
	ft_free_path(&all);
}
