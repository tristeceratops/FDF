/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:17:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:44 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_map(t_dot **map, t_data *img)
{
    int     x;
    int     y;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x].is_last_in_line != 1)
        {
            draw_line(map[y][x], map[y][x + 1], img, &map[y][x].color);
            if (map[y + 1])
                draw_line(map[y][x], map[y + 1][x], img, &map[y][x].color);
            x++;
        }
        if (map[y][x].is_last_in_line == 1 && map[y + 1])
            draw_line(map[y][x], map[y + 1][x], img, &map[y][x].color);
        y++;
    }
}