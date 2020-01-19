/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:39:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/19 17:09:24 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
    int c = r;

    c = (c << 8) | g;
    c = (c << 8) | b;
    return c;
}

void    ft_wall_casting(int col, float angle, int wasVert)
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

    float x;
    float y;

    if (!wasVert)
    {
        x = fmod((data.player_x * data.wall.x), 64);
        y = data.player_y * data.wall.y;
    }
    else
    {
        x = data.player_x * data.wall.x;
        y = fmod((data.player_y * data.wall.y), 64);
    }
    printf("%s\n", data.path.north);
    int w;
    int h;
    //mlx_xpm_to_image (data.mlx_ptr, char **xpm_data, int *width, int *height );
    mlx_xpm_file_to_image(data.mlx_ptr, data.path.north, &w, &h);
     ft_draw_line(col , data.y/2 - wallStripHeight/2, col, data.y/2 + wallStripHeight/2, WHITE);
    // CEILLING
    ft_draw_line(col , 0, col, data.y/2 - wallStripHeight/2, data.ceilling.color);
    // FLOOR
    ft_draw_line(col , data.y/2 + wallStripHeight/2, col, data.y, data.floor.color);
}