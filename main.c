/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:38:04 by nkrasimi          #+#    #+#             */
/*   Updated: 2025/08/02 20:33:56 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

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

void	load_texture(t_map *mapa, t_texture *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(mapa->mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		perror("Error cargando textura");
		freeall(mapa);
		exit(1);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	load_all_textures(t_map *mapa)
{
	load_texture(mapa, &mapa->tex_north, mapa->northtexture);
	load_texture(mapa, &mapa->tex_south, mapa->southtexture);
	load_texture(mapa, &mapa->tex_east, mapa->easttexture);
	load_texture(mapa, &mapa->tex_west, mapa->westtexture);
}

void	cubed_init(t_map *mapa)
{
	mapa->xx = mapa->y * SIZE + (SIZE / 2);
	mapa->yy = mapa->x * SIZE + (SIZE / 2);
	mapa->speed = 1;
	mapa->key_a = 0;
	mapa->key_w = 0;
	mapa->key_d = 0;
	mapa->key_s = 0;
	mapa->key_left = 0;
	mapa->key_right = 0;
	set_player_dir_and_plane(mapa);
	mapa->floor_color = parse_color(mapa->floorcolor);
	mapa->ceiling_color = parse_color(mapa->ceilingcolor);
	mapa->mlx_ptr = mlx_init();
	load_all_textures(mapa);
	mapa->win_ptr = mlx_new_window(mapa->mlx_ptr, WIDTH, HEIGHT, mapa->name);
	mapa->img_ptr = mlx_new_image(mapa->mlx_ptr, WIDTH, HEIGHT);
	mapa->pixel_ptr = mlx_get_data_addr(mapa->img_ptr, &mapa->bpp,
			&mapa->line_length, &mapa->endian);
	mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->img_ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_map	mapa;

	if (ac != 2)
		return (msg(1, ARGERROR), 1);
	if (av[1][0] == '\0')
		return (msg(1, ARGERROR2), 1);
	init_values(&mapa);
	if (ismap(av[1], &mapa) == 1)
	{
		mapa.path = ft_strdup(av[1]);
		if (check3atributtes(&mapa) == 0)
			return (msg(2, "Saliendo...\n"), freeall(&mapa), 1);
	}
	else
		return (msg(1, ARGERROR3), 1);
	cubed_init(&mapa);
	mlx_hook (mapa.win_ptr, 2, KeyPressMask, handle_key, &mapa);
	mlx_hook (mapa.win_ptr, 3, KeyReleaseMask, key_release, &mapa);
	mlx_hook (mapa.win_ptr, DestroyNotify, StructureNotifyMask,
		closewindow, &mapa);
	mlx_loop_hook (mapa.mlx_ptr, cubed_render, &mapa);
	mlx_loop (mapa.mlx_ptr);
	freeall(&mapa);
	return (0);
}
