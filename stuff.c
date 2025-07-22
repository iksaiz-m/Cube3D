/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:38:04 by nkrasimi          #+#    #+#             */
/*   Updated: 2025/07/22 20:14:27 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

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

void	init_values(t_map *mapa)
{
	mapa->northtexture = NULL;
	mapa->southtexture = NULL;
	mapa->easttexture = NULL;
	mapa->westtexture = NULL;
	mapa->path = NULL;
	mapa->name = NULL;
	mapa->floorcolor = NULL;
	mapa->ceilingcolor = NULL;
	mapa->toflood_map = NULL;
	mapa->final_map = NULL;
}

// mlx_hook(mapa->win_ptr, ButtonPress,
// 	ButtonPressMask, handle_mouse, mapa);
// mlx_hook(mapa->win_ptr, KeyPress, KeyPressMask, handle_key, mapa);
static void	events_init(t_map *mapa)
{
	mlx_hook(mapa->win_ptr, KeyPress, KeyPressMask, handle_key, mapa);
	mlx_hook(mapa->win_ptr, DestroyNotify, StructureNotifyMask,
		closewindow, mapa);
}

static void	my_mlx_pixel_put(int x, int y, int color, t_img *img)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->line_len + x * img->bpp / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_map *mapa)
{
	for (int i = 0; i < size; i++)
		my_mlx_pixel_put(x + i, y, color, &mapa->img);
	for (int i = 0; i < size; i++)
		my_mlx_pixel_put(x, y + i, color, &mapa->img);
	for (int i = 0; i < size; i++)
		my_mlx_pixel_put(x + size, y + i, color, &mapa->img);
	for (int i = 0; i < size; i++)
		my_mlx_pixel_put(x + i, y + size, color, &mapa->img);
}

void	game_start(t_map *mapa)
{
    mapa->mlx_ptr = mlx_init();
	if (!mapa->mlx_ptr)
		return ;
    mapa->win_ptr = mlx_new_window(mapa->mlx_ptr, WIDTH, HEIGHT, mapa->name);
	if (!mapa->win_ptr)
		return ;
	mapa->img.img_ptr = mlx_new_image(mapa->mlx_ptr, WIDTH, HEIGHT);
	mapa->img.addr = mlx_get_data_addr(mapa->img.img_ptr,
			&mapa->img.bpp,&mapa->img.line_len, &mapa->img.endian);
	mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->img.img_ptr, 0, 0);
	// if (!init_textures(mapa))
	// 	return ;
    // Mostrar una de las texturas en pantalla (por ejemplo, la del norte)
	// my_mlx_pixel_put(mapa->mlx_ptr, 300, 300, YELLOW);
	events_init(mapa);
	// mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->textures[0].img_ptr, 0, 0);
	// mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->textures[1].img_ptr, 1833, 0);
	// mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->textures[2].img_ptr, 0, 993);
	// mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->textures[3].img_ptr, 1833, 993);
	return ;
}

int	main(int ac, char **av)
{
	t_map	mapa;

	if (ac != 2)
		return (msg(1, ARGERROR), 1);
	if (av[1][0] == '\0')
		return (msg(1, ARGERROR2), 1);
	init_values(&mapa);
	/* Vamos a ver Ibon aqui tenemos que hacer el parseo de los argumentos por terminal */
	/* Leer el mapa y comprobar que todo esta bien con el floodfill */
	if (ismap(av[1], &mapa) == 1)
	{
		mapa.path = ft_strdup(av[1]);
		if (check3atributtes(&mapa) == 0)
			return (msg(2, "Saliendo...\n"), freeall(&mapa), 1);
	}
	else
		return (msg(1, ARGERROR3), 1);
		/* Raycasting */
	// game_init(&mapa);
		/* Por ahora vamos a dejar el resto para luego */
	game_start(&mapa);
	draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, &mapa);
	mlx_loop(mapa.mlx_ptr);
	freeall(&mapa);
	return (0);
}
