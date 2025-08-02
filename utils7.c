/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:39 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/02 19:02:31 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	parse_color(const char *line)
{
	int	r;
	int	g;
	int	b;

	while (*line && (*line == 'F' || *line == ' '))
		line++;
	r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	b = ft_atoi(line);
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel(int x, int y, int color, t_map *mapa)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * mapa->line_length + x * mapa->bpp / 8;
	mapa->pixel_ptr[index] = color & 0xFF;
	mapa->pixel_ptr[index + 1] = (color >> 8) & 0xFF;
	mapa->pixel_ptr[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int color, t_map *mapa)
{
	int	x2;
	int	y2;

	y2 = y;
	x2 = x;
	while (y < (y2 + SIZE))
	{
		x = x2;
		while (x < (x2 + SIZE))
		{
			put_pixel (x, y, color, mapa);
			x++;
		}
		y++;
	}
}

int	key_release(int keysym, t_map *mapa)
{
	if (keysym == XK_a)
		mapa->key_a = 0;
	else if (keysym == XK_d)
		mapa->key_d = 0;
	else if (keysym == XK_w)
		mapa->key_w = 0;
	else if (keysym == XK_s)
		mapa->key_s = 0;
	else if (keysym == XK_Left)
		mapa->key_left = 0;
	else if (keysym == XK_Right)
		mapa->key_right = 0;
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
