/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:00:06 by ewoillar          #+#    #+#             */
/*   Updated: 2024/04/30 14:26:55 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) && 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

int		gradien(int startcolor, int endcolor, int len, int pix)
{
	double increment[3];
	int	new[3];
	int newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double) len;
	increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double) len;
	increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double) len;

	new[0] = (R(startcolor)) + ft_round(pix * increment[0]);
    new[1] = (G(startcolor)) + ft_round(pix * increment[1]);
    new[2] = (B(startcolor)) + ft_round(pix * increment[2]);

    newcolor = RGB(new[0], new[1], new[2]);

    return (newcolor);
}

void	draw_line_x(t_2dcoord start, t_2dcoord end, t_data *data, int start_color, int end_color)
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
	int steps = end.x - start.x;
	int increment = (end_color - start_color) / steps;
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