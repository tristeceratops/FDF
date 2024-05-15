/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_line.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ewoillar <ewoillar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/29 17:00:06 by ewoillar		  #+#	#+#			 */
/*   Updated: 2024/05/14 12:32:48 by ewoillar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		get_light_line(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start) + (percentage * end));
}

int		get_color_line(t_dot start, t_dot end, double percentage)
{
	int		red;
	int		green;
	int		blue;
	//printf("start color = 0x%x\n", start.color);
	red = get_light_line((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light_line((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light_line(start.color & 0xFF, end.color & 0xFF, percentage);
	//printf("percentage = %f\n", percentage);
	//printf("red = 0x%x | green = 0x%x | blue = 0x%x\n", red, green, blue);
	//printf("pixel color = 0x%x\n", ((red << 16) | (green << 8) | blue));
	return ((red << 16) | (green << 8) | blue);
}

void	draw_line_x(t_dot start, t_dot end, t_data *data, int color)
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
	int	temp = start.x;
	while(start.x <= end.x)
	{
		if (start.x > 0 && start.x < data->win_width && y > 0 && y < data->win_height)
		{
			color = get_color_line(start, end, ((double)(start.x - temp) / (end.x - temp)));
			my_mlx_pixel_put(data, start.x, y, color);
		}
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
void	draw_line_y(t_dot start, t_dot end, t_data *data, int color)
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
	int	temp = start.y;
	while(start.y <= end.y)
	{
		if (x > 0 && x < data->win_width && start.y > 0 && start.y < data->win_height)
		{
			color = get_color_line(start, end, ((double)(start.y - temp) / (end.y - temp)));
			my_mlx_pixel_put(data, x, start.y, color);
		}
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
void	draw_line(t_dot start, t_dot end, t_data *data)
{
	int		color;
	if (start.z > end.z)
		color = start.color;
	else
		color = end.color;
	start.x *= data->zoom;
	start.y *= data->zoom;
	end.x *= data->zoom;
	end.y *= data->zoom;
	start.z *= data->zoom;
	end.z *= data->zoom;
	start = projection_iso(start);
	end = projection_iso(end);
	start.x += data->x_pad;
	start.y += data->y_pad;
	end.x += data->x_pad;
	end.y += data->y_pad;
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