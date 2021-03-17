/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:48:29 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/17 18:00:29 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// typedef struct		s_win_r
// {
// 	int				x;
// 	int				y;
// }					t_win_r;

// typedef struct		s_path_tex
// {
// 	char			*north;
// 	char			*south;
// 	char			*west;
// 	char			*east;
// 	char			*sprite;
// }					t_path_tex;

// typedef struct		s_color
// {
// 	int				r;
// 	int				g;
// 	int				b;
// 	int				rgb;
// }					t_color;

// typedef struct		s_map
// {
// 	char			char_map[MAP_HEIGHT][MAP_WIDTH];
// 	int				map[MAP_HEIGHT][MAP_WIDTH];
// 	int				start;
// 	int				end;
// 	int				tmp_y;
// 	int				pflag;
// }					t_map;

// typedef struct		s_flag
// {
// 	int				eflag;
// 	int				r;
// 	int				no;
// 	int				so;
// 	int				we;
// 	int				ea;
// 	int				s;
// 	int				f;
// 	int				c;
// 	int				except_map;
// }					t_flag;

// typedef struct		s_all
// {
// 	// t_info		info;
// 	// t_img		img;
// 	// t_player	player;
// 	// t_info		info;
// 	// t_key		key;
// 	// t_pair		pair;
// 	// t_sprite	sprite;
// 	t_win_r		win_r;
// 	t_path_tex		path_tex;
// 	t_color			color_f;
// 	t_color			color_c;
// 	t_map			map;
// 	t_flag			flag;
// }					t_all;


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
	free(*line);
	exit(0);
}

//error
void			ft_put_error_and_exit(t_all *all, char **line, char *s)
{
	write(1, "\e[31mError\e[m\n", 15);
	ft_putstr_fd(s, 2);
	ft_exit(all, line);
}

//.cub 判定
int				ft_iscub(char *cub)
{
	int			len;

	len = (int)ft_strlen(cub);
	if (len > 4 && cub[len - 4] == '.' && cub[len - 3] == 'c' && cub[len - 2] == 'u' && cub[len - 1] == 'b')
		return (1);
	return (0);
}

//init struct all
void			ft_init_all(t_all *all)
{
	all->flag.eflag = 0;
	all->flag.r = 0;
	all->flag.no = 0;
	all->flag.so = 0;
	all->flag.we = 0;
	all->flag.ea = 0;
	all->flag.s = 0;
	all->flag.f = 0;
	all->flag.c = 0;
	all->flag.except_map = 0;
	all->win_r.x = 0;
	all->win_r.y = 0;
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;
	all->map.pflag = 0;
	all->map.start = 0;
	all->map.end = 0;
	all->map.tmp_y = 1;
}

void			ft_init_char_map(t_all *all)
{
	int			x;
	int			y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
				all->map.char_map[y][x] = 'x';
			else
				all->map.char_map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void			ft_init(t_all *all)
{
	ft_init_all(all);
	ft_init_char_map(all);
	// printf("init map\n\n");
	// for(int i = 0; i < MAP_HEIGHT; i++)
	// {
	// 	for(int j = 0; j < MAP_WIDTH; j++)
	// 		printf("%c", all->map.char_map[i][j]);
	// 	printf("\n");
	// }
}

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

int			ft_is_all_num(char *num)
{
	int			len;
	int			i;

	i = 0;
	len = (int)ft_strlen(num);
	while (ft_isdigit(num[i]))
		i++;
	if (i == len)
		return (0);
	return (-1);
}

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
		ft_put_error_and_exit(all, line, "Invalid format");
	if (!(res = ft_strdup(tmp[1])))
		ft_put_error_and_exit(all, line, "Invalid format");
	if (res[0] != '.' || res[1] != '/')
		ft_put_error_and_exit(all, line, "Invalid path");
	*path = res;
	*flag = 1;
	ft_free_all(tmp);
}

void			ft_input_rgb(t_all *all, char **line, t_color *color, char **char_rgb)
{
	if ((ft_is_all_num(char_rgb[R])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters");
	color->r = ft_atoi_ex(char_rgb[R]);
	if ((ft_is_all_num(char_rgb[G])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters");
	color->g = ft_atoi_ex(char_rgb[G]);
	if ((ft_is_all_num(char_rgb[B])) < 0)
		ft_put_error_and_exit(all, line, "Contains non-numeric characters");
	color->b = ft_atoi_ex(char_rgb[B]);
	if (color->r < 0 || color->g < 0 || color->b < 0 || 255 < color->r || 255 < color->g || 255 < color->b )
		ft_put_error_and_exit(all, line, "Invalid value");
}

void			ft_parse_line_color(t_all *all, t_color *color, int *flag, char **line)
{
	char		**char_rgb;
	char 		**tmp;

	if (*flag == 1)
		ft_put_error_and_exit(all, line, "Set only one each color\n");
	tmp = NULL;
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit(all, line, "Invalid format");
	if (!(char_rgb = ft_split(tmp[1], ',')))
	{
		ft_free_all(tmp);
		ft_put_error_and_exit(all, line, "Invalid format");
	}
	ft_free_all(tmp);
	ft_input_rgb(all, line, color, char_rgb);
	if (char_rgb[3])
		ft_put_error_and_exit(all, line, "Invalid format");
	ft_free_all(char_rgb);
	*flag = 1;
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

//map以外のflagが全て立っている
int				ft_flag_on_expect_map(t_all *all)
{
	if (all->flag.r == 1 && all->flag.no == 1 && all->flag.so == 1 && all->flag.we == 1 && all->flag.ea == 1 && all->flag.s == 1 && all->flag.f == 1 && all->flag.c == 1)
		return (1);
	else
		return (0);
}

//lineを1行char
void			ft_store_line_with_map(t_all *all, char **line)
{
	int			x;

	x = 0;
	while ((x + 1 < MAP_WIDTH - 1) && ((*line)[x] != '\0'))
	{
		all->map.char_map[all->map.tmp_y][x + 1] = (*line)[x];
		x++;
	}
	// for (int i = 0; i < MAP_WIDTH; i++)
	// 	printf("%c", all->map.char_map[all->map.tmp_y][i]);
	// printf("\n");
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

//line を charmap に格納
void			ft_parse_line_map(t_all *all, char **line)
{
	if (ft_in_the_process_of_forming_map(all, line) >= 0)
	{
		ft_judge_possible_chars(all, line);
		if ((MAP_WIDTH - 2 < (int)ft_strlen(*line)) || (MAP_HEIGHT - 2 < all->map.tmp_y))
			ft_put_error_and_exit(all, line, "Map size limits is exceeded\n");
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

//main input
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

		printf("\nset map\n\n");
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
