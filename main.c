/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:02:25 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/14 17:42:09 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int		key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == XK_KP_Up)
	{
		data->y_pad -= 10;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	else if (keycode == XK_KP_Down)
	{
		data->y_pad += 10;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	}
	else if (keycode == XK_KP_Left)
	{
		data->x_pad -= 10;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	else if (keycode == XK_KP_Right)
	{
		data->x_pad += 10;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	else if (keycode == XK_KP_Home)
	{
		if (data->zoom > 1)
		{
			data->zoom -= 1;
			mlx_destroy_image(data->mlx, data->img);
			data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
			draw_map(data->map, data);
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
	else if (keycode == XK_KP_Page_Up)
	{
		data->zoom += 1;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

int		red_cross(void)
{
	exit(0);
	return(0);
}

int		check_file_extension(char *path)
{
	int		len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 4] == '.' && path[len - 3] == 'f' && path[len - 2] == 'd' && path[len - 1] == 'f')
		return (1);
	return (0);
}


int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error("Usage: ./fdf <filename>");
	if (!check_file_extension(argv[1]))
		ft_error("Invalid file extension, must be 'filename.fdf'");
	data.win_height = 1080;
	data.win_width = 1920;
	data.x_pad = data.win_width /2;
	data.y_pad = 0;
	data.zoom = 3;
	data.map = read_map(argv[1], data);
	data.map = fill_color_tab(data);
	data.min_z = get_min_height(data.map, get_rows(data.map), get_columns(data.map));
	data.max_z = get_max_height(data.map, get_rows(data.map), get_columns(data.map));
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "FDF");

	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	draw_map(data.map, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.win, 17, 1L<<0, red_cross, &data);
	mlx_loop(data.mlx);
}