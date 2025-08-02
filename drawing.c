/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:17:11 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/02 20:38:12 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	calculate_and_draw_pixel(t_map *mapa, int start_y, int tex_x, int x)
{
	int		offset;
	int		color;
	int		tex_y;

	mapa->d = start_y * 256 - HEIGHT * 128 + mapa->line_height * 128;
	tex_y = (mapa->d * mapa->current_tex->height) / mapa->line_height / 256;
	if (tex_x < 0 || tex_x >= mapa->current_tex->width || tex_y < 0
		|| tex_y >= mapa->current_tex->height)
		return ;
	offset = tex_y * mapa->current_tex->line_len + tex_x
		* (mapa->current_tex->bpp / 8);
	if (offset < 0 || offset + 3 >= mapa->current_tex->height
		* mapa->current_tex->line_len)
		return ;
	color = *(int *)(mapa->current_tex->data + offset);
	put_pixel(x, start_y, color, mapa);
}

void	draw_wall(int x, int start_y, int end_y, t_map *mapa)
{
	double		wall_x;
	int			tex_x;

	wall_x = mapa->wall_x - floor(mapa->wall_x);
	tex_x = (int)(wall_x * mapa->current_tex->width);
	if ((mapa->side == 0 && mapa->ray_dir_x < 0)
		|| (mapa->side == 1 && mapa->ray_dir_y > 0))
		tex_x = mapa->current_tex->width - tex_x - 1;
	while (start_y < end_y)
	{
		calculate_and_draw_pixel(mapa, start_y, tex_x, x);
		start_y++;
	}
}

void	draw_3d_dda(int x, int start_y, int end_y, t_map *mapa)
{
	int	y;

	y = -1;
	while (++y < start_y)
		put_pixel(x, y, 0x87CEEB, mapa);
	draw_wall (x, start_y, end_y, mapa);
	y = end_y;
	while (y < HEIGHT)
	{
		put_pixel(x, y, 0x444444, mapa);
		y++;
	}
}

void	clear_image(t_map *mapa)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, mapa);
			x++;
		}
		y++;
	}
}
