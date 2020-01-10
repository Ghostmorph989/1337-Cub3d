/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/10 16:14:55 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void    ft_wall_casting(float col, float angle)
{
    float distanceProjPlane;
    float wallStripHeight;
    double raydist;

    raydist  = data.ray.dist * cos(angle - data.dir.angle*M_PI/180);
    distanceProjPlane = (data.wall.x/2) / tan((M_PI/180)*data.dir.fov/2);
    wallStripHeight = (data.wall.x/data.ray.dist) * distanceProjPlane;
    ft_draw_line(col , data.y/2 - wallStripHeight/2, col, data.y/2 + wallStripHeight/2);
}