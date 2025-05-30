/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:37:36 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/29 18:37:29 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

static void	error(void)
{
	ft_printf("Error\n");
	exit(1);
}

// void	data_init(t_fractal *fractal)
// {
// 	fractal->escape_value = 4;
// 	fractal->iterations = 42;
// 	fractal->changed_x = 0.0;
// 	fractal->changed_y = 0.0;
// 	fractal->zoom = 1.0;
// }

int	closewindow(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	ft_free(fractal->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		closewindow(fractal);
	// if (keysym == XK_Left)
	// 	fractal->changed_x += (0.5 * fractal->zoom);
	// else if (keysym == XK_Right)
	// 	fractal->changed_x -= (0.5 * fractal->zoom);
	// else if (keysym == XK_Up)
	// 	fractal->changed_y -= (0.5 * fractal->zoom);
	// else if (keysym == XK_Down)
	// 	fractal->changed_y += (0.5 * fractal->zoom);
	// else if (keysym == XK_plus)
	// 	fractal->iterations += 10;
	// else if (keysym == XK_minus)
	// 	fractal->iterations -= 10;
	// fractal_render(fractal);
	return (0);
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr, KeyPress, KeyPressMask, handle_key, fractal);
	mlx_hook(fractal->win_ptr, DestroyNotify, StructureNotifyMask,
		closewindow, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (NULL == fractal->mlx_ptr)
		error();
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr,
			WIDTH, HEIGHT, fractal->name);
	if (NULL == fractal->win_ptr)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		ft_free(fractal->mlx_ptr);
		error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr,
			WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		ft_free(fractal->mlx_ptr);
		error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

// int	parse_map_name(char	*map_name)
// {
// 	int	i;

// 	i = 0;
// 	while (map_name[i])
// 	{
// 		if (map_name[i] == '.')
// 		{
// 			i++;
// 			if (map_name[i] != 'c')
// 		}
// 		i++;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	t_cube	map;

// 	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
// 		|| (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
// 	{
// 		ft_printf("%s", "Valid imput\n");
// 		map.name = av[1];
// 		parse_map_name(map.name);
// 		if (!ft_strncmp(map.name, "julia", 5))
// 		{
// 			map.julia_x = atod(av[2]);
// 			map.julia_y = atod(av[3]);
// 		}
// 		fractal_init(&map);
// 		fractal_render(&map);
// 		mlx_loop(map.mlx_ptr);
// 	}
// 	else
// 	{
// 		ft_printf("There needs to be either julia or mandelbrot fractals\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }
