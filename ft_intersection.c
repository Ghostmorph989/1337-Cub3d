/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/19 16:29:57 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"


float   ft_distance_beetwen_points(float x0, float y0, float x1, float y1)
{
    return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

void    normalize(float *angle)
{
    if (*angle < 0)
        *angle += 2*M_PI;
    *angle = fmod(*angle, 2*M_PI);
}

void    RayFacing(float angle)
{
    data.ray.down = angle > 0 && angle < M_PI;
    data.ray.up = !data.ray.down;
    data.ray.right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
    data.ray.left = !data.ray.right;

}

void    ft_find_intersection(int col, float angle)
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    t_direction nextHorzTouch;

    RayFacing(angle);
    
    yintercept = floor(data.player_y) * data.wall.y;
    yintercept += data.ray.down ? data.wall.y : 0;

    xintercept = data.player_x*data.wall.x + (yintercept - data.player_y*data.wall.y) / tan(angle);

    ystep = data.wall.y;
    ystep *= data.ray.up ? -1 : 1;

    xstep = data.wall.x / tan(angle);
    xstep *= (data.ray.left && xstep > 0) ? -1 : 1;
    xstep *= (data.ray.right && xstep < 0) ? -1 : 1;


    nextHorzTouch.x = xintercept;
    nextHorzTouch.y = yintercept;

    int  width;
    int  height;

    width = ft_strlen(data.map[0]) * data.wall.x;
    height = data.map_ln * data.wall.y;

    if (data.ray.up)
        (nextHorzTouch.y)--;
        
    while ((nextHorzTouch.x >= 0 && nextHorzTouch.x <= width) && (nextHorzTouch.y >= 0 && nextHorzTouch.y <= height))
    {
        if (isWall(nextHorzTouch))
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
    
    xintercept = 0;
    yintercept = 0;
    xstep = 0;
    ystep = 0;

    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    t_direction nextVertTouch;

    RayFacing(angle);

    xintercept = floor(data.player_x) * data.wall.x;
    xintercept += data.ray.right ? data.wall.x : 0;

    yintercept = data.player_y*data.wall.y + (xintercept - data.player_x*data.wall.x) * tan(angle);

    xstep = data.wall.x;
    xstep *= data.ray.left ? -1 : 1;

    ystep = data.wall.y * tan(angle);
    ystep *= (data.ray.up && ystep > 0) ? -1 : 1;
    ystep *= (data.ray.down && ystep < 0) ? -1 : 1;


    nextVertTouch.x = xintercept;
    nextVertTouch.y = yintercept;

    if (data.ray.left)
        (nextVertTouch.x)--;
        
    while ((nextVertTouch.x >= 0 && nextVertTouch.x <= width) && (nextVertTouch.y >= 0 && nextVertTouch.y <= height))
    {
        if (isWall(nextVertTouch))
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
    float horzHitDistance = foundHorzWallHit ? ft_distance_beetwen_points(data.player_x*data.wall.x, data.player_y*data.wall.y, horzWallHitX, horzWallHitY) : INT_MAX;
    float vertHitDistance = foundVertWallHit ? ft_distance_beetwen_points(data.player_x*data.wall.x, data.player_y*data.wall.y, vertWallHitX, vertWallHitY) : INT_MAX;
    
    float WallHitX;
    float WallHitY;
    int wasVert;

    wasVert = (vertHitDistance < horzHitDistance);
    WallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
    WallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
    data.ray.dist = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
    ft_wall_casting(col, angle, wasVert);
}
