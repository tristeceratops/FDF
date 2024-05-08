/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:17:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/08 15:09:07 by ewoillar         ###   ########.fr       */
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
            if (map[y][x + 1].is_last_in_line != 1)
                draw_line(map[y][x], map[y][x + 1], img, 0x00FF00);
            if (map[y + 1] && map[y + 1][x].is_last_in_line != 1)
                draw_line(map[y][x], map[y + 1][x], img, 0x00FF00);
            x++;
        }
        if (map[y + 1])
            draw_line(map[y][x], map[y + 1][x], img, 0x00FF00);
        draw_line(map[y][x - 1], map[y][x], img, 0x00FF00);
        y++;
    }
}