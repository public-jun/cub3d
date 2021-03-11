/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:52:28 by jnakahod          #+#    #+#             */
/*   Updated: 2020/11/25 16:18:44 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>

int main(int ac, char **av)
{
	(void)av;
	char *line = NULL;
	int i, j;


	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		do
		{
			i = get_next_line(fd, &line);
			printf("%4d : %s\n", i, line);
			free(line);
		} while (0 < i);
		close(fd);
	}
	else if (ac == 3)
	{
		int fd2 = open(av[1], O_RDONLY);
		int fd3 = open(av[2], O_RDONLY);
		do
		{
			i = get_next_line(fd2, &line);
			printf("%4d : %s\n", i, line);
			free(line);

			j = get_next_line(fd3, &line);
			printf("%4d : %s\n", j, line);
			free(line);
		} while (0 < i || 0 < j);
		close(fd2);
		close(fd3);
	}
	return (0);
}
