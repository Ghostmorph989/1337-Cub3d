/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/31 14:46:47 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

float  ft_get_distance(int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    {
        if (data.map[(int)(Y / data.y_l)][(int)(  X / data.x_l)] == '1')
        {
            float dist;
            dist = sqrt(pow(X - X0, 2) + pow(Y - Y0, 2));
            return (dist);
        }       
        //pixel_put(X, Y, WHITE);  // put pixel at (X,Y) 
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
                             // generation step by step 
    }
    return (1);
}

void    RayFacing()
{
    if (data.dir.angle < 0)
        data.dir.angle += 2*180;
    data.ray.down = data.dir.angle > 0 && data.dir.angle < 180;
    data.ray.up = !data.ray.down;
    data.ray.right = data.dir.angle < 90 && data.dir.angle < 180;
    data.ray.left = !data.ray.right;
}

int     ft_intersection(float rayangle)
{
    double yintercept;
    double xintercept;
    float  xstep;
    float  ystep;
    t_direction nextHorz;

    RayFacing();
    yintercept = ((int)(data.player_y/data.y_l)) * data.y_l;
    yintercept += (data.ray.down) ? data.x_l : 0;

    xintercept = data.player_x + (yintercept - data.player_y) / tan(data.dir.fov * M_PI/180);
    ystep = data.y_l;
    ystep *= (data.ray.up) ? -1 : 1;

    xstep = data.x_l;
    xstep *= (data.ray.left && xstep > 0) ? -1 :1;
    xstep *= (data.ray.right && xstep < 0)? -1 : 1;

    nextHorz.x = xintercept;
    nextHorz.y = yintercept;

    printf("%f |%f |%f |%f\n", yintercept, xintercept, ystep, xstep);
    if (data.ray.up)
        nextHorz.y--;
    while ((nextHorz.x >= 0 && nextHorz.x <= data.x) && (nextHorz.y >= 0 && nextHorz.y <= data.y))
    {
        if (isWall(nextHorz))
            break;
        //ft_draw_line(data.player_x*data.x_l, data.player_y*data.y_l, nextHorz.x*data.x_l + data.dir.x*100, nextHorz.y*data.y_l + data.dir.y*100);
        //ft_get_distance(data.player_x*data.x_l, data.player_y*data.y_l, nextHorz.x*data.x_l, nextHorz.y*data.y_l);
        nextHorz.x += xstep;
        nextHorz.y += ystep;
    }
    return (1);
}

void    ft_wall_casting(float col)
{
    int wall_height = 64;
    float distanceProjPlane;
    float wallStripHeight;

    distanceProjPlane = (data.wall.x/2) / tan((M_PI/180)*data.dir.fov/2);
    wallStripHeight = (data.wall.x/data.ray.dist) * distanceProjPlane;

    // printf("wall strripheight : %.2f| distance : %.2f | distancePrjplan : %f | data.x_l : %.2f \n", wallStripHeight, dist, distanceProjPlane, data.x_l);
    // // printf("%f\n",(data.x_l/dist) * distanceProjPlane);
    // // printf("j :%d| data.x_l : %f| data.x : %d | wallstripheight : %f | Wall_Stripheight %d\n", j, data.x_l , data.x, wallStripHeight, wall_height);
    //ft_draw_line(distanceProjPlane , wallStripHeight,distanceProjPlane + wallStripHeight/2, wallStripHeight );
    //ft_draw_line(distanceProjPlane, wallStripHeight, distanceProjPlane, wallStripHeight);
    ft_draw_line(col, data.y/2 - wallStripHeight/2,col, data.y/2 + wallStripHeight/2);
    //ft_draw_rectangle(distanceProjPlane + wallStripHeight/2, wallStripHeight);
    //printf("%f2\n", distanceProjPlane);
    //printf("%f2\n", dist);
} 