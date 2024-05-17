/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:06:44 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/17 13:44:43 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//function to convert array of a hexadecimal value into int
int	hexarraytoint(char *hex)
{
	int		length;
	int		base;
	int		decimal;
	int		i;

	length = ft_strlen(hex);
	base = 1;
	decimal = 0;
	i = length - 1;
	if (hex[i] == '0' && hex[i - 1] == 'x')
		i -= 2;
	while (i >= 0)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			decimal += (hex[i] - 48) * base;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			decimal += (hex[i] - 55) * base;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			decimal += (hex[i] - 87) * base;
		base = base * 16;
		i--;
	}
	return (decimal);
}

void	move_image(int	*pad, int value, t_data *data)
{
	*pad += value;
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	draw_map(data->map, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_string_put(data->mlx, data->win, 100, 140, 0xf8f8f8, "up : numpad 8");
	mlx_string_put(data->mlx, data->win, 100, 160, 0xf8f8f8, "down : numpad 2");
	mlx_string_put(data->mlx, data->win, 100, 180, 0xf8f8f8, "right : numpad 6");
	mlx_string_put(data->mlx, data->win, 100, 200, 0xf8f8f8, "left : numpad 4");
	mlx_string_put(data->mlx, data->win, 100, 220, 0xf8f8f8, "zoom: numpad 9");
	mlx_string_put(data->mlx, data->win, 100, 240, 0xf8f8f8, "dezoom: numpad 7");
}
