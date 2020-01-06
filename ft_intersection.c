/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:45:22 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/06 19:57:31 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

t_direction nextHorz;
t_direction nextHorzHit;
t_direction nextVertHit;
int foundHorzWall;
int foundVertWall;

void     ft_h_intersection(float ray_angle)
{
    float yintercept;
    float xintercept;
    float xstep;
    float ystep; 

    foundHorzWall = 0;
    RayFacing(ray_angle);
    yintercept = floor(data.player_y/data.y_l) * data.y_l;
    yintercept += data.ray.down ? data.y_l : 0;

    xintercept = data.player_x + (yintercept - data.player_y) / tan(ray_angle);
    ystep = data.y_l;
    ystep *= (data.ray.up) ? -1 : 1;
    xstep = data.x_l / tan(ray_angle);
    xstep *= (data.ray.left && xstep > 0) ? -1 :1;
    xstep *= (data.ray.right && xstep < 0)? -1 : 1;
    nextHorz.x = xintercept;
    nextHorz.y = yintercept;

    if (data.ray.up)
        (nextHorz.y)--;
    while ((nextHorz.x >= 0 && nextHorz.x <= data.x) && (nextHorz.y >= 0 && nextHorz.y <= data.y))
    {
        printf("xstep %f |ystep %f\n", nextHorz.x, nextHorz.y);
        if (isWall(nextHorz))
        {
            printf("i m a wall");
            nextHorzHit.x = nextHorz.x;
            nextHorzHit.y = nextHorz.y;
            foundHorzWall = 1;
            break ;
        }
        else
        {
            // ft_draw_line(data.player_x * data.x_l, data.player_y * data.y_l, nextHorz.x * data.x_l , nextHorz.y * data.y_l);
            nextHorz.x += xstep;
            nextHorz.y += ystep;
        }
    }
    ft_v_intersection(ray_angle);
}

float   ft_distance_beetwen_points(float x0, float y0, float x1, float y1)
{
    return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

void    ft_v_intersection(float ray_angle)
{
    float yintercept;
    float xintercept;
    float xstep;
    float ystep;
    t_direction nextVert;

    foundVertWall = 0;
    xintercept = round(data.player_x / data.x_l) * data.x_l;
    xintercept += data.ray.right ? data.x_l : 0;
    yintercept = data.player_y + (xintercept - data.player_x) * tan(ray_angle);

    xstep = data.x_l;
    xstep *= data.ray.left ? -1 : 1;

    ystep = data.y_l * tan(ray_angle);
    ystep *= (data.ray.up &&  ystep > 0) ? -1 : 1;
    ystep *= (data.ray.down && ystep < 0) ? -1 : 1;
    nextVert.x = xintercept;
    nextVert.y = yintercept;
    if (data.ray.left)
        nextVert.x--;

    while ((nextVert.x >= 0 && nextVert.x <= data.x) && (nextVert.y >= 0 && nextVert.y <= data.y))
    {
        if (isWall(nextVert))
        {
            nextVertHit.x = nextVert.x;
            nextVertHit.y = nextVert.y;
            foundVertWall = 1;
            break ;
        }
        nextVert.x += xstep;
        nextVert.y += ystep;
    }
    //ft_draw_line(data.player_x * data.x_l, data.player_y * data.y_l, nextVertHit.x* data.x_l , nextVertHit.y * data.y_l);

    float horzHitDistance; 
    float vertHitDistance;
    float wallHitX;
    float wallHitY;

    horzHitDistance = foundHorzWall ? ft_distance_beetwen_points(data.player_x * data.x_l, data.player_y* data.y_l, nextHorzHit.x* data.x_l, nextHorzHit.y* data.y_l) : INT_MAX;
    vertHitDistance = foundVertWall ? ft_distance_beetwen_points(data.player_x * data.x_l, data.player_y* data.y_l, nextVertHit.x* data.x_l, nextVertHit.y* data.y_l) : INT_MAX;
    wallHitX = (horzHitDistance < vertHitDistance) ? nextHorzHit.x : nextVertHit.x;
    wallHitY = (horzHitDistance < vertHitDistance) ? nextHorzHit.y : nextVertHit.y;
    // ft_draw_line(data.player_x * data.x_l, data.player_y * data.y_l, nextVertHit.x * data.x_l , nextVertHit.y * data.y_l);
    //ft_draw_line(data.player_x * data.x_l, data.player_y * data.y_l, nextHorzHit.x * data.x_l , nextHorzHit.y * data.y_l);
    data.ray.dist = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
}   