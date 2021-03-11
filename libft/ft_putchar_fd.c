/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 16:59:53 by jnakahod          #+#    #+#             */
/*   Updated: 2020/10/30 19:49:47 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	char    head;
	char    tail;
	char    mask1;
	char    mask2;

	// asciiの範囲内
	if ((unsigned char)c <= 0x7F)
	{
		write(fd, &c, sizeof(char));
	}
	// 0x80以上は2バイト文字の領域
	else
	{
		mask1 = 0b00111111;
		mask2 = 0b11000000;

		// 2バイトの前
		// cの上位2ビット分を取り出して、6ビット右にシフトして、先頭に11をつける
		head = (((unsigned char)c & mask2) >> 6) | mask2;
		// 2バイトの後ろ
		// cの下位6ビット分を取り出して、先頭に10をつける
		tail = ((unsigned char)c & mask1) | 0b10000000;

		write(fd, &head, 1);
		write(fd, &tail, 1);
	}
}
