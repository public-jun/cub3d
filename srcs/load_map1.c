/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:48:29 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/12 22:55:30 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

typedef struct		s_win_r
{
	int				x;
	int				y;
}					t_win_r;

typedef struct		s_path_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_path_tex;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				rgb;
}					t_color;

typedef struct		s_map
{
	char			char_map[MAP_HEIGHT][MAP_WIDTH];
	int				map[MAP_HEIGHT][MAP_WIDTH];
}					t_map;

typedef struct		s_flag
{
	int				eflag;
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
}					t_flag;

typedef struct		s_all
{
	// t_info		info;
	// t_img		img;
	// t_player	player;
	// t_info		info;
	// t_key		key;
	// t_pair		pair;
	// t_sprite	sprite;
	t_win_r		win_r;
	t_path_tex		path_tex;
	t_color			color_f;
	t_color			color_c;
	t_map			map;
	t_flag			flag;
}					t_all;


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

void			ft_exit(t_all *all)
{
	ft_free_path(all);
	exit(0);
}

//error
void			ft_put_error_and_exit(char *s)
{
	write(1, "\e[31mError\e[m\n", 15);
	ft_putstr_fd(s, 2);
	// ft_exit(all);
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
	all->win_r.x = 0;
	all->win_r.y = 0;
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;
}

// init map
// void			ft_init_map(t_all *all)
// {

// }

void			ft_init(t_all *all)
{
	ft_init_all(all);
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

	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit("Invalid R format");
	if ((ft_is_all_num(tmp[1])) < 0)
		ft_put_error_and_exit("Contains non-numeric characters");
	all->win_r.x = ft_atoi_ex(tmp[1]);
	if (all->win_r.x < 1 || 1920 < all->win_r.x)
		ft_put_error_and_exit("Invalid value");
	if ((ft_is_all_num(tmp[2])) < 0)
		ft_put_error_and_exit("Contains non-numeric characters");
	all->win_r.y = ft_atoi_ex(tmp[2]);
	if (all->win_r.y < 1 || 1080 < all->win_r.y)
		ft_put_error_and_exit("Invalid value");
	if (tmp[3])
		ft_put_error_and_exit("Invalid format");
	all->flag.r = 1;
	ft_free_all(tmp);
}

void			ft_parse_line_path(char **path, int *flag, char **line)
{
	char		*res;
	char		**tmp;


	tmp = NULL;
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit("Invalid format");
	if (!(res = ft_strdup(tmp[1])))
		ft_put_error_and_exit("Invalid format");
	if (res[0] != '.' || res[1] != '/')
		ft_put_error_and_exit("Invalid path");
	*path = res;
	*flag = 1;
	ft_free_all(tmp);
}

void			ft_input_rgb(t_color *color, char **char_rgb)
{
	if ((ft_is_all_num(char_rgb[R])) < 0)
		ft_put_error_and_exit("Contains non-numeric characters");
	color->r = ft_atoi_ex(char_rgb[R]);
	if ((ft_is_all_num(char_rgb[G])) < 0)
		ft_put_error_and_exit("Contains non-numeric characters");
	color->g = ft_atoi_ex(char_rgb[G]);
	if ((ft_is_all_num(char_rgb[B])) < 0)
		ft_put_error_and_exit("Contains non-numeric characters");
	color->b = ft_atoi_ex(char_rgb[B]);
	if (color->r < 0 || color->g < 0 || color->b < 0 || 255 < color->r || 255 < color->g || 255 < color->b )
		ft_put_error_and_exit("Invalid value");
}

void			ft_parse_line_color(t_color *color, int *flag, char **line)
{
	char		**char_rgb;
	char 		**tmp;

	tmp = NULL;
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit("Invalid format");
	if (!(char_rgb = ft_split(tmp[1], ',')))
		ft_put_error_and_exit("Invalid format");
	ft_free_all(tmp);
	ft_input_rgb(color, char_rgb);
	if (char_rgb[3])
		ft_put_error_and_exit("Invalid format");
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
		ft_parse_line_path(&all->path_tex.north, &all->flag.no, line);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == 'O' && (*line)[i + 2] == ' ')
		ft_parse_line_path(&all->path_tex.south, &all->flag.so, line);
	else if ((*line)[i] == 'W' && (*line)[i + 1] == 'E' && (*line)[i + 2] == ' ')
		ft_parse_line_path(&all->path_tex.west, &all->flag.we, line);
	else if ((*line)[i] == 'E' && (*line)[i + 1] == 'A' && (*line)[i + 2] == ' ')
		ft_parse_line_path(&all->path_tex.east, &all->flag.ea, line);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == ' ')
		ft_parse_line_path(&all->path_tex.sprite, &all->flag.s, line);
	else if ((*line)[i] == 'F' && (*line)[i + 1] == ' ')
		ft_parse_line_color(&all->color_f, &all->flag.f, line);
	else if ((*line)[i] == 'C' && (*line)[i + 1] == ' ')
		ft_parse_line_color(&all->color_c, &all->flag.c, line);
	// 	ft_parse_line_c(all, line, &i);

}


//map かそれ以外で判定
void			ft_parse_line(t_all *all, char **line)
{
	ft_parse_line_param(all, line);
	//map判定
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
		printf("%8d : %s\n", res, line);
		ft_parse_line(all, &line);
		free(line);
	}
	printf("%8d : %s\n", res, line);
	if (res == -1)
		ft_put_error_and_exit("Failed to read\n");
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
			ft_put_error_and_exit("Failed to open\n");
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
		printf("flag_f  : %d\n", all.flag.c);
	}
	close(fd);
	ft_exit(&all);
}
