/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/06 18:46:33 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"


void    RayFacing(float j)
{
    float angle;

    angle = j;
    //angle = fmod(angle, 2*M_PI);
    // if (angle < 0)
    //     angle += 2*M_PI;
    data.ray.down = angle > 0 && angle < M_PI;
    data.ray.up = !data.ray.down;
    data.ray.right = angle < M_PI/2 && angle < 1.5*M_PI;
    data.ray.left = !data.ray.right;
}


void    ft_wall_casting(float col, float angle)
{
    float distanceProjPlane;
    float wallStripHeight;
    // double raydist;

    //raydist  = data.ray.dist * cos((angle - angle) * M_PI/180);
    distanceProjPlane = (data.wall.x/2) / tan((M_PI/180)*data.dir.fov/2);
    
    wallStripHeight = (data.wall.x/(data.ray.dist)) * distanceProjPlane;
    ft_draw_line(col , data.y/2 - wallStripHeight/2, col, data.y/2 + wallStripHeight/2);
}