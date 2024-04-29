/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:00:06 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/29 17:11:07 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_x(t_2dcoord start, t_2dcoord end, t_data *data, int color)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int y1 = 1;
	if (dy < 0)
	{
		y1 = -1;
		dy = -dy;
	}
	int d = 2 * dy - dx;
	int y = start.y;
	while(start.x <= end.x)
	{
		my_mlx_pixel_put(data, start.x, y, color);
		if (d > 0)
		{
			y += y1;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		start.x += 1;
	}
}
//draw_line_y
void	draw_line_y(t_2dcoord start, t_2dcoord end, t_data *data, int color)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int x1 = 1;
	if (dx < 0)
	{
		x1 = -1;
		dx = -dx;
	}
	int d = 2 * dx - dy;
	int x = start.x;
	while(start.y <= end.y)
	{
		my_mlx_pixel_put(data, x, start.y, color);
		if (d > 0)
		{
			x += x1;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		start.y += 1;
	}
}
//draw line function that redirect to draw_line_x or draw_line_y depending on the slope of the line
void	draw_line(t_2dcoord start, t_2dcoord end, t_data *data, int color)
{
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