/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:52:35 by jnakahod          #+#    #+#             */
/*   Updated: 2021/03/12 17:50:28 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void			free_set(char **dst, char *src)
// {
// 	free(*dst);
// 	*dst = src;
// }

size_t			ft_strchr_ex(char *s, int c)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	return (0);
}
