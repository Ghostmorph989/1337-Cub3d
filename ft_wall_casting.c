/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/30 01:00:07 by malaoui          ###   ########.fr       */
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
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, X, Y, WHITE);  // put pixel at (X,Y) 
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
                             // generation step by step 
    }
    return (0);
}


void    ft_wall_casting()
{
    int wall_height = 64;
    float dist;
    float distanceProjPlane;
    float wallStripHeight;

    data.dir.x = cos((data.dir.angle)*M_PI/180);
    data.dir.y = sin((data.dir.angle)*M_PI/180);
    dist = ft_get_distance(data.player_x*data.x_l, data.player_y*data.y_l, data.player_x*data.x_l + data.dir.x*10000, data.player_y*data.y_l + data.dir.y*10000);
    distanceProjPlane = (data.x_l/2) / tan((M_PI/180)*data.dir.fov/2);
    wallStripHeight = (data.x_l/dist) * distanceProjPlane;
    printf("wall strripheight : %.2f| distance : %.2f | distancePrjplan : %f | data.x_l : %.2f \n", wallStripHeight, dist, distanceProjPlane, data.x_l);
    // printf("%f\n",(data.x_l/dist) * distanceProjPlane);
    // printf("j :%d| data.x_l : %f| data.x : %d | wallstripheight : %f | Wall_Stripheight %d\n", j, data.x_l , data.x, wallStripHeight, wall_height);
    ft_draw_rectangle(distanceProjPlane, wallStripHeight);
    //printf("%f2\n", distanceProjPlane);
    //printf("%f2\n", dist);
} 