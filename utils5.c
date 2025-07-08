/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:11:19 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/08 20:23:24 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	closewindow(t_map *mapa)
{
	mlx_destroy_image(mapa->mlx_ptr, mapa->img.img_ptr);
	mlx_destroy_window(mapa->mlx_ptr, mapa->win_ptr);
	mlx_destroy_display(mapa->mlx_ptr);
	free(mapa->mlx_ptr);
    freeall(mapa);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_map *mapa)
{
	if (keysym == XK_Escape)
		closewindow(mapa);
	// if (keysym == W)
	// 	fractal->changed_x += (0.5 * fractal->zoom);
	// else if (keysym == A)
	// 	fractal->changed_x -= (0.5 * fractal->zoom);
	// else if (keysym == S)
	// 	fractal->changed_y -= (0.5 * fractal->zoom);
	// else if (keysym == D)
	// 	fractal->changed_y += (0.5 * fractal->zoom);
	// game_render(mapa);
	return (0);
}

int checkmap_name_folders(char *str)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (str[i])
	{
		if (str[i] == '/')
			ii = i;
		i++;
	}
	return (ii);
}



int	check_printable_map_name(char *str, int i, int ii)
{
	while (ii < i - 4)
	{
		if (!ft_isprint(str[ii]))
			return (msg(2, FORMAT2), exit(1), 0);
		ii++;
	}
	return (1);
}

