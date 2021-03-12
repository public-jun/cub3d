/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:47:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/11 23:07:16 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAP_HEIGHT 50
#define MAP_WIDTH 50
#define NO_TEX 0
#define SO_TEX 1
#define WE_TEX 2
#define EA_TEX 3
#define S_TEX 4

typedef struct		s_win_size
{
	int				w_width;
	int				w_height;
}					t_win_size;

typedef struct		s_tex_path
{
	char			**path;
}					t_tex_path;

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

typedef struct		s_all
{
	// t_info		info;
	// t_img		img;
	// t_player	player;
	// t_info		info;
	// t_key		key;
	// t_pair		pair;
	// t_sprite	sprite;
	t_win_size		win_size;
	t_tex_path		tex_path;
	t_color			color_f;
	t_color			color_c;
	t_map			map;
}				t_all;

// int				ft_exit(all)
// {
// 	exit(0);
// }

// void			ft_put_error_and_exit(char *s, t_all *all)

void			ft_put_error_and_exit(char *s)
{
	write(1, "\e[31mError\e[m\n", 15);
	ft_putstr_fd(s, 2);
	// ft_exit(all);
}

int				ft_skip_str(char *str, char *line)
{
	int			i;

	i = 0;
	while (str[i] == line[i])
		i++;
	if (str[i] != '\0')
		return (-1);
	return (i);

}

int				ft_check_value(int *i, char *line, int min, int max, int digits)
{
	int			first;
	int			res;
	int			j;
	char		*tmp;

	first = *i;
	while('0' <= line[*i] && line[*i] <= '9' && (*i - first) < digits)
		(*i)++;
	if ((*i - first) == 0)
		return (-1);
	digits = *i - first;
	tmp = (char *)malloc(sizeof(char) * (digits + 1));
	if (!tmp)
		return (-1);
	j = 0;
	while (j < digits)
		tmp[j++] = line[first++];
	tmp[j] = '\0';
	res = ft_atoi(tmp);
	if (res <= min || max <= res)
		return (-1);
	free(tmp);
	return (res);
}

//input win_size
void			ft_input_win_size(char *line, t_all *all)
{
	int			first;


	first = ft_skip_str("R ", line);
	//load w_width
	if (first < 0 )
		// ft_put_error_and_exit("Invalid R name", all);
		ft_put_error_and_exit("Invalid R name\n");
	all->win_size.w_width = ft_check_value(&first, line, 1, 1920, 4);
	if (all->win_size.w_width < 0)
		// ft_put_error_and_exit("Invalid R param", all);
		ft_put_error_and_exit("Invalid R param\n");
	if (line[first] != ' ')
		// ft_put_error_and_exit("Invalid R format", all);
		ft_put_error_and_exit("Invalid R format\n");
	//load w_height
	first++;
	all->win_size.w_height = ft_check_value(&first, line, 1, 1080, 4);
	if (all->win_size.w_height < 0)
		// ft_put_error_and_exit("Invalid R param", all);
		ft_put_error_and_exit("Invalid R param\n");
	if(line[first] != '\0')
		// ft_put_error_and_exit("Invalid R param", all);
		ft_put_error_and_exit("Invalid R param\n");
}

char				*ft_input_path(char *str, char *line)
{
	int			first;
	int			path_len;
	char 		*path;

	first = ft_skip_str(str, line);
	if (first < 0)
		return (NULL);
	path_len = (int)ft_strlen(line) - first + 1;
	if (path_len < 1 || 255 < path_len)
		return (NULL);
	path = ft_substr(line, first, path_len);
	if (!path)
		ft_put_error_and_exit("Invalid path\n");
	return (path);
}

void			ft_load_tex_paths(int fd, char **line, t_all *all)
{
	int			i;
	// int			res;

	all->tex_path.path = (char **)malloc(sizeof(char *) * 5);
	if (!all->tex_path.path)
		ft_put_error_and_exit("cant malloc");
	i = get_next_line(fd, line);
	all->tex_path.path[0] = ft_input_path("NO ", *line);
	if (!all->tex_path.path[0])
		// ft_put_error_and_exit("Invalid NO format\n", all);
		ft_put_error_and_exit("Invalid path\n");
	printf("%8d : %s\n", i, *line);
	free(*line);
	*line = NULL;
	i = get_next_line(fd, line);
	all->tex_path.path[1] = ft_input_path("SO ", *line);
	if (!all->tex_path.path[1])
		// ft_put_error_and_exit("Invalid NO format\n", all);
		ft_put_error_and_exit("Invalid path\n");
	printf("%8d : %s\n", i, *line);
	free(*line);
	*line = NULL;

}

int main(int ac, char **av)
{
	(void)av;
	char *line;
	int i;
	t_all		all;


	line = NULL;

	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);

		//load win_size
		i = get_next_line(fd, &line);
		ft_input_win_size(line, &all);
		printf("%8d : %s\n", i, line);
		printf("w_width  : %d\n", all.win_size.w_width);
		printf("w_height : %d\n", all.win_size.w_height);
		free(line);

		// while (i > 0)
		// {
		// 	i = get_next_line(fd, &line);
		// 	printf("%8d : %s\n", i, line);
		// 	free(line);
		// }
		//load tex_path
		ft_load_tex_paths(fd, &line, &all);
		printf("NO  : %s\n", all.tex_path.path[NO_TEX]);
		printf("SO  : %s\n", all.tex_path.path[SO_TEX]);
		free(all.tex_path.path[NO_TEX]);
		free(all.tex_path.path[SO_TEX]);
		free(all.tex_path.path[WE_TEX]);
		free(all.tex_path.path[EA_TEX]);
		free(all.tex_path.path[S_TEX]);
		free(all.tex_path.path);

		close(fd);
	}
	return (0);
}
