/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:18 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/23 16:18:15 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color_line(t_dot start, t_dot end, double percentage)
{
	int		red;
	int		green;
	int		blue;

	red = get_light((start.color >> 16) & 0xFF, \
	(end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, \
	(end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, \
	end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	draw_x_init(t_bresenham *wrap, t_dot start, t_dot end)
{
	wrap->dx = end.x - start.x;
	wrap->dy = end.y - start.y;
	wrap->iterator_value = 1;
	if (wrap->dy < 0)
	{
		wrap->iterator_value = -1;
		wrap->dy = -wrap->dy;
	}
	wrap->d = 2 * wrap->dy - wrap->dx;
	wrap->iterator = start.y;
}

void	draw_line_x(t_dot start, t_dot end, t_data *data, int color)
{
	t_bresenham	*wrap;
	int			temp;

	wrap = malloc(sizeof(t_bresenham));
	draw_x_init(wrap, start, end);
	temp = start.x;
	while (start.x <= end.x)
	{
		if (start.x > 0 && start.x < data->win_width && \
		wrap->iterator > 0 && wrap->iterator < data->win_height)
		{
			color = get_color_line(start, end, \
			((double)(start.x - temp) / (end.x - temp)));
			my_mlx_pixel_put(data, start.x, wrap->iterator, color);
		}
		if (wrap->d > 0)
		{
			wrap->iterator += wrap->iterator_value;
			wrap->d += 2 * (wrap->dy - wrap->dx);
		}
		else
			wrap->d += 2 * wrap->dy;
		start.x += 1;
	}
	free(wrap);
}

void	draw_y_init(t_bresenham *wrap, t_dot start, t_dot end)
{
	wrap->dx = end.x - start.x;
	wrap->dy = end.y - start.y;
	wrap->iterator_value = 1;
	if (wrap->dx < 0)
	{
		wrap->iterator_value = -1;
		wrap->dx = -wrap->dx;
	}
	wrap->d = 2 * wrap->dx - wrap->dy;
	wrap->iterator = start.x;
}

void	draw_line_y(t_dot start, t_dot end, t_data *data, int color)
{
	t_bresenham	*wrap;
	int			temp;

	wrap = malloc(sizeof(t_bresenham));
	draw_y_init(wrap, start, end);
	temp = start.y;
	while (start.y <= end.y)
	{
		if (wrap->iterator > 0 && wrap->iterator < data->win_width \
		&& start.y > 0 && start.y < data->win_height)
		{
			color = get_color_line(start, end, \
			((double)(start.y - temp) / (end.y - temp)));
			my_mlx_pixel_put(data, wrap->iterator, start.y, color);
		}
		if (wrap->d > 0)
		{
			wrap->iterator += wrap->iterator_value;
			wrap->d += 2 * (wrap->dx - wrap->dy);
		}
		else
			wrap->d += 2 * wrap->dx;
		start.y += 1;
	}
	free(wrap);
}
