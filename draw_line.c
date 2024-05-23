/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:07:22 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/23 16:15:32 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	draw_init(t_dot *start, t_dot *end, t_data *data)
{
	start->x *= data->zoom;
	start->y *= data->zoom;
	end->x *= data->zoom;
	end->y *= data->zoom;
	start->z *= data->zoom;
	end->z *= data->zoom;
	*start = projection_iso(*start);
	*end = projection_iso(*end);
	start->x += data->x_pad;
	start->y += data->y_pad;
	end->x += data->x_pad;
	end->y += data->y_pad;
}

void	draw_line(t_dot start, t_dot end, t_data *data)
{
	int		color;

	if (start.z > end.z)
		color = start.color;
	else
		color = end.color;
	draw_init(&start, &end, data);
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_line_x(end, start, data, color);
		else
			draw_line_x(start, end, data, color);
	}
	else
	{
		if (start.y > end.y)
			draw_line_y(end, start, data, color);
		else
			draw_line_y(start, end, data, color);
	}
}
