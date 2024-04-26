/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/26 18:07:32 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		close_w(int keycode, t_vars *vars)
{
	printf("keycode: %d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//function to generate a square, argument is the image, the color, the size and the left_top corner
void	generate_square(t_data *img, int color, int size, int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			my_mlx_pixel_put(img, x + i, y + j, color);
	}
}

int main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	generate_square(&img, 0x00FF0000, 50, 100, 100);
	generate_square(&img, 0x00FFFF00, 50, 500, 500);
	generate_square(&img, 0x0000FFFF, 50, 800, 800);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, XK_Escape, close_w, &vars);
	mlx_loop(vars.mlx);
}