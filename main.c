/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:06:16 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/13 11:18:13 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
int		close_w(int keycode, t_vars *vars)
{
	ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int		red_cross(void)
{
	exit(0);
	return(0);
}*/

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
	data.map = read_map(argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "FDF");
	data.win_height = 1080;
	data.win_width = 1920;
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	draw_map(data.map, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}