/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/28 18:09:22 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"


int        ft_handle_texture(int col, float offset, float start, float end, float wallStripHeight)
{
    float texture_y = 0;
    float step = (float )(data.img_h/(end - start));
    while (start <= end)
    {
        pixel_put(col, start, data.img_id[(int)(texture_y) * data.img_h + (int)offset]);
        texture_y += step;
        start++;
    }
    //printf("start : %f | texture_x : %f |end : %f \n", start, texture_x, end);
    return (0);
}

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
    int c = r;

    c = (c << 8) | g;
    c = (c << 8) | b;
    return c;
}

void    ft_wall_casting(int col, float angle, int wasVert, float wallx, float wally)
{
    float distanceProjPlane;
    float wallStripHeight;
    float raydist;  
    float an;

    an = angle - data.dir.angle;
    normalize(&an);
    raydist  = data.ray.dist * cos(an);
    distanceProjPlane = (data.x/2) / tan(data.dir.fov/2);
    wallStripHeight = (data.wall.x/raydist) * distanceProjPlane;

    float offset = ((wasVert == 0) ? fmod(wallx , TILE_SIZE) : fmod(wally, TILE_SIZE));

    ft_handle_texture(col, offset,  data.y/2 - wallStripHeight/2,  data.y/2 + wallStripHeight/2, wallStripHeight);
    // floor
    
    //ft_draw_line(800, data.y , data.x, data.y/2 - wallStripHeight / 2, WHITE);
    //ft_draw_line(500, data.y/2 - wallStripHeight / 2, data.x, data.y, WHITE);
    
    //printf("%f\n", offset);
    // CEILLING
    //ft_ceilling_texture(col, data.ray.dist /wallStripHeight, data.y/2 + wallStripHeight/2, data.y,data.y - (data.y/2 + wallStripHeight/2));
    // FLOOR
    //ft_floor_texture(col , offset,data.y/2 + wallStripHeight/2, data.y, 0);

    // CEILLING
    ft_draw_line(col , 0, col, data.y/2 - wallStripHeight/2, data.ceilling.color);
    // FLOOR
    ft_draw_line(col , data.y/2 + wallStripHeight/2, col, data.y, data.floor.color);

}