/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/10 20:34:52 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"


float   ft_distance_beetwen_points(float x0, float y0, float x1, float y1)
{
    return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

void    RayFacing(double *j)
{
   double angle;

    angle = *j;
    angle = fmod(angle, 2*M_PI);
    if (angle < 0)
        angle += 2*M_PI;
    data.ray.down = angle > 0 && angle < M_PI;
    data.ray.up = !data.ray.down;
    data.ray.right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
    data.ray.left = !data.ray.right;
    *j = angle;
}

void    ft_find_intersection(float angle)
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
    double ray_angle = angle;
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;

    RayFacing(&ray_angle);
    yintercept = floor(data.player_y) * data.y_l;
    yintercept += data.ray.down ? data.y_l : 0;

    xintercept = data.player_x*data.x_l + (yintercept - data.player_y*data.y_l) / tan(ray_angle);

    ystep = data.y_l;
    ystep *= data.ray.up ? -1 : 1;

    xstep = data.x_l / tan(ray_angle);
    xstep *= (data.ray.left && xstep > 0) ? -1 : 1;
    xstep *= (data.ray.right && xstep < 0) ? -1 : 1;

    t_direction nextHorzTouch;

    nextHorzTouch.x = xintercept;
    nextHorzTouch.y = yintercept;

    if (data.ray.up)
        (nextHorzTouch.y)--;
    
    while ((nextHorzTouch.x >= 0 && nextHorzTouch.x < data.x) && (nextHorzTouch.y >= 0 && nextHorzTouch.y < data.y))
    {
        if (!isWall(nextHorzTouch))
        {
            foundHorzWallHit = 1;
            horzWallHitX = nextHorzTouch.x;
            horzWallHitY = nextHorzTouch.y;
            break ;
        }
        else
        {
            nextHorzTouch.x += xstep;
            nextHorzTouch.y += ystep;
        }
    }
      //ft_draw_line(data.player_x * data.x_l, data.y_l * data.player_y, horzWallHitX, horzWallHitY);

    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;

    xintercept = floor(data.player_x) * data.x_l;
    xintercept += data.ray.right ? data.x_l : 0;

    yintercept = data.player_y*data.y_l + (xintercept - data.player_x*data.x_l) * tan(ray_angle);

    xstep = data.x_l;
    xstep *= data.ray.left ? -1 : 1;

    ystep = data.y_l * tan(ray_angle);
    ystep *= (data.ray.up && ystep > 0) ? -1 : 1;
    ystep *= (data.ray.down && ystep < 0) ? -1 : 1;

    t_direction nextVertTouch;

    nextVertTouch.x = xintercept;
    nextVertTouch.y = yintercept;

    if (data.ray.left)
        (nextVertTouch.x)--;
        
    while ((nextVertTouch.x >= 0 && nextVertTouch.x < data.x) && (nextVertTouch.y >= 0 && nextVertTouch.y < data.y))
    {
        if (!isWall(nextVertTouch))
        {
            foundVertWallHit = 1;
            vertWallHitX = nextVertTouch.x;
            vertWallHitY = nextVertTouch.y;
            break ;
        }
        else
        {
            nextVertTouch.x += xstep;
            nextVertTouch.y += ystep;
        }
    }
    //ft_draw_line(data.player_x * data.x_l, data.y_l * data.player_y, vertWallHitX, vertWallHitY);
    float horzHitDistance = ft_distance_beetwen_points(data.player_x*data.x_l, data.player_y*data.y_l, horzWallHitX, horzWallHitY);
    float vertHitDistance = ft_distance_beetwen_points(data.player_x*data.x_l, data.player_y*data.y_l, vertWallHitX, vertWallHitY);
    
    float WallHitX;
    float WallHitY;

    WallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
    WallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
    data.ray.dist = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
    //ft_draw_line(data.player_x * data.x_l, data.y_l * data.player_y, WallHitX, WallHitY);
}
