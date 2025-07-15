/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:38:04 by nkrasimi          #+#    #+#             */
/*   Updated: 2025/07/15 20:09:10 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
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

/* Estas 3 funciones son para parsear el map */
int	is_valid_line(char *map_line)
{
	int	i;

	i = 0;
	if (map_line[i] != '1')
		return (0);
	while (map_line[i])
	{
		if (map_line[i] != '1' && map_line[i] != '0' && map_line[i] != 'N')
			return (0);
		i++;
	}
	i -= 1;
	if (map_line[i] != '1')
		return (0);
	return (1);
}

void	remove_spaces(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (len == 0)
		msg(2, "Error. Empty line\n");
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

// Con esta funcion sabremos si realmente se esta leyendo y guardando bien el mapa
void	print_matrix(char **matrix)
{
	int i;
	int ii; 

	i = 0;
	while (matrix[i])
	{   
		ii = 0;
		while (matrix[i][ii])
		{
			 write(1, &matrix[i][ii], 1);
			ii++;
		}
		i++;
	}
}   



/* int ismap(char *str) */
/* { */
/* 	int	i; */
/* 	char	*check; */

/* 	i = 0; */
/* 	while (str[i]) */
/* 		i++; */
/* 	if (i < 5) */
/* 		msg(2, "Tiene que tener algo delante de la extension .cub\n"), exit(1); */
/* 	i -= 5; */
/* 	check = &str[i]; */
/* 	if (!ft_isprint(check[0])) */
/* 		msg(2, "El caracter que va delante de la extension .cub tiene que ser imprimible\n"), exit(1); */
/* 	if (check[1] == '.' && check[2] == 'c' && check[3] == 'u' && */
/* 	check[4] == 'b' && check[5] == '\0') */
/* 		return (1); */
/* 	else */
/* 		return (0); */
/* } */


void	init_values(t_map *mapa)
{
	mapa->ndirections = 4;
	mapa->ncolors = 2;
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


static void	events_init(t_map *mapa)
{
	mlx_hook(mapa->win_ptr, KeyPress, KeyPressMask, handle_key, mapa);
	// mlx_hook(mapa->win_ptr, ButtonPress,
	// 	ButtonPressMask, handle_mouse, mapa);
	mlx_hook(mapa->win_ptr, DestroyNotify, StructureNotifyMask,
		closewindow, mapa);
	// mlx_hook(mapa->win_ptr, KeyPress, KeyPressMask, handle_key, mapa);
}


// void	game_init(t_map *mapa)
// {
// 	mapa->mlx_ptr = mlx_init();
// 	if (mapa->mlx_ptr == NULL)
// 		return ;
// 	mapa->win_ptr = mlx_new_window(mapa->mlx_ptr,
// 		WIDTH, HEIGHT, "DOOM");
// 	if (NULL == mapa->win_ptr)
// 	{
// 		mlx_destroy_display(mapa->mlx_ptr);
// 		ft_memdel(mapa->mlx_ptr);
// 		return ;
// 	}
// 	mapa->img.img_ptr = mlx_new_image(mapa->mlx_ptr, WIDTH, HEIGHT );
// 	if (NULL == mapa->img.img_ptr)
// 	{
// 		mlx_destroy_window(mapa->mlx_ptr, mapa->win_ptr);
// 		mlx_destroy_display(mapa->mlx_ptr);
// 		free(mapa->mlx_ptr);
// 		return ;
// 		// error();
// 	}
// 	mapa->img.addr = mlx_get_data_addr(mapa->img.img_ptr,
// 		&mapa->img.bpp, &mapa->img.line_len, &mapa->img.endian);
// 	mapa->img2 = mlx_xpm_file_to_image(mapa->mlx_ptr, "texture0.xpm", &mapa->img_widht, &mapa->img_height);
// 	events_init(mapa);
// 	mlx_put_image_to_window();
// 	mlx_loop(mapa->mlx_ptr);
// }


// "textures/wall_north.xpm",
// "textures/wall_south.xpm",
// "textures/wall_east.xpm",
// "textures/wall_west.xpm"

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
// void	init_player(t_player *player)
// {
// 	player->x = WIDTH / 2;
// 	player->y = HEIGHT /2;
// }

// void move_player(t_player *player)
// {
// 	int speed;

// 	speed = 5;
// }


// int init_textures(t_map *game)
// {
//     const char *paths[4] = {
// 		"doom.xpm",
// 		"doom2.xpm",
// 		"doom3.xpm",
// 		"doom4.xpm"
//     };
// 	// "texture0.xpm",
// 	// "wall_north.xpm"
// 	// "wall_south.xpm",
// 	// "wall_east.xpm"
// 	// "wall_west.xpm"

//     for (int i = 0; i < 4; i++)
//     {
//         game->textures[i].img_ptr = mlx_xpm_file_to_image(
//             game->mlx_ptr,
//             (char *)paths[i],
//             &game->textures[i].img_width,
//             &game->textures[i].img_height
//         );
// 		// printf("path texturas: %s\n",paths[i]);
// 		// printf("path width: %d\n", game->textures->img_width);
// 		// printf("path height: %d\n", game->textures->img_height);
//         if (!game->textures[i].img_ptr)
//         {
//             printf("Error cargando textura: %s\n", paths[i]);
//             return (0);
//         }
//         game->textures[i].addr = mlx_get_data_addr(
//             game->textures[i].img_ptr,
//             &game->textures[i].bpp,
//             &game->textures[i].line_len,
//             &game->textures[i].endian
//         );
//     }
//     return (1);
// }




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

int main (int ac, char **av)
{
	/* size_t	i; */
	t_map	mapa;

	if (ac != 2)
		return (msg(1, ARGERROR), 1);
	if (av[1][0] == '\0')
		return (msg(1, ARGERROR2), 1);
	init_values(&mapa);
	/* i = 0; */
	/* Vamos a ver Ibon aqui tenemos que hacer el parseo de los argumentos por terminal */

	/* Leer el mapa y comprobar que todo esta bien con el floodfill */
	if (ismap(av[1], &mapa) == 1)
    {
		mapa.path = ft_strdup(av[1]);
		if (check3atributtes(&mapa) == 0)
			return (msg(2, "Saliendo...\n"), freetextures(&mapa), 1);
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
