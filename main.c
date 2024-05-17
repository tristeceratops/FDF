/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:02:25 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/17 13:47:09 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		free_map(data->map);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	else if (keycode == XK_KP_Up)
		move_image(&data->y_pad, -20, data);
	else if (keycode == XK_KP_Down)
		move_image(&data->y_pad, 20, data);
	else if (keycode == XK_KP_Left)
		move_image(&data->x_pad, -20, data);
	else if (keycode == XK_KP_Right)
		move_image(&data->x_pad, 20, data);
	else if (keycode == XK_KP_Home)
	{
		if (data->zoom > 1)
			move_image(&data->zoom, -1, data);
	}
	else if (keycode == XK_KP_Page_Up)
		move_image(&data->zoom, 1, data);
	return (0);
}

int	red_cross(t_data *data)
{
	free_map(data->map);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	check_file_extension(char *path)
{
	int		len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 4] == '.' && path[len - 3] == 'f' && \
		path[len - 2] == 'd' && path[len - 1] == 'f')
		return (1);
	return (0);
}

t_data	data_init(t_data data, char *arg)
{
	data.win_height = 1080;
	data.win_width = 1920;
	data.x_pad = data.win_width / 2;
	data.y_pad = 0;
	data.zoom = 4;
	data.map = read_map(arg, data);
	data.rows = get_rows(data.map);
	data.columns = get_columns(data.map);
	data.min_z = get_min_height(data.map, data.rows, data.columns);
	data.max_z = get_max_height(data.map, data.rows, data.columns);
	data.map = fill_color_tab(data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "FDF");
	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
	&data.line_length, &data.endian);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error("Usage: ./fdf <filename>");
	if (!check_file_extension(argv[1]))
		ft_error("Invalid file extension, must be 'filename.fdf'");
	data = data_init(data, argv[1]);
	draw_map(data.map, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_string_put(data.mlx, data.win, 100, 140, 0xf8f8f8, "up : numpad 8");
	mlx_string_put(data.mlx, data.win, 100, 160, 0xf8f8f8, "down : numpad 2");
	mlx_string_put(data.mlx, data.win, 100, 180, 0xf8f8f8, "right : numpad 6");
	mlx_string_put(data.mlx, data.win, 100, 200, 0xf8f8f8, "left : numpad 4");
	mlx_string_put(data.mlx, data.win, 100, 220, 0xf8f8f8, "zoom: numpad 9");
	mlx_string_put(data.mlx, data.win, 100, 240, 0xf8f8f8, "dezoom: numpad 7");
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, 1L << 0, red_cross, &data);
	mlx_loop(data.mlx);
}
