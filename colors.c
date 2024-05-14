/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:12:37 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/14 17:38:09 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_light(int start, int end, double percentage)
{
	return ((int)(1 - percentage) * start + percentage * end);
}

int		get_color_tab(t_data data, t_dot dot)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	percentage = (dot.z - data.min_z) / (data.max_z - data.min_z);
	red = get_light((BASE_COLOR >> 16) & 0xFF, (TOP_COLOR >> 16) & 0xFF, percentage);
	green = get_light((BASE_COLOR >> 8) & 0xFF, (TOP_COLOR >> 8) & 0xFF, percentage);
	blue = get_light(BASE_COLOR & 0xFF, TOP_COLOR, percentage);
	return ((red << 16) | (green << 8) | blue);
}

t_dot	**fill_color_tab(t_data data)
{
	int		i;
	int		j;

	i = 0;
	while (i < get_rows(data.map))
	{
		j = 0;
		while (j < get_columns(data.map))
		{
			if (data.map[i][j].z == data.min_z)
				data.map[i][j].color = BASE_COLOR;
			else if (data.map[i][j].z == data.max_z)
				data.map[i][j].color = TOP_COLOR;
			else
				data.map[i][j].color = get_color_tab(data, data.map[i][j]);
			j++;
		}
		i++;
	}
	return (data.map);
}