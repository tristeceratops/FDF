/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:17:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/13 11:30:00 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_map(t_dot **map, t_data *img)
{
    int     x;
    int     y;
    int     color;
    
    color = BASE_COLOR;
    y = 0;
    while (map[y])
    {
        ft_printf("y = %d\n", y);
        x = 0;
        while (map[y][x].is_last_in_line != 1)
        {
            draw_line(map[y][x], map[y][x + 1], img, &color);
            if (map[y + 1])
                draw_line(map[y][x], map[y + 1][x], img, &color);
            x++;
        }
        if (map[y][x].is_last_in_line == 1 && map[y + 1])
            draw_line(map[y][x], map[y + 1][x], img, &color);
        y++;
    }
}