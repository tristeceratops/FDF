/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:21:45 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/10 15:49:27 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	projection_iso(t_dot p)
{
	t_dot p2;

	p2.x = (p.x - p.y) * cos(0.5);
	p2.y = (p.x + p.y) * sin(0.5) - p.z;
	p2.is_last_in_line = p.is_last_in_line;
	p2.x_pad = p.x_pad;
	p2.y_pad = p.y_pad;
	p2.zoom = p.zoom;
	p2.z = p.z;
	return (p2);
}