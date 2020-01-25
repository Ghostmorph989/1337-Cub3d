/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:31:16 by malaoui           #+#    #+#             */
/*   Updated: 2020/01/24 19:10:33 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Protection from multiple inclusion

#ifndef     LIBCUB_H
# define    LIBCUB_H

// Including used Libraries 
 
#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "ft_printf/libft/libft.h"
#include "ft_printf/libftprintf.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <limits.h>

// Marcos 
# define EXIT_SUCCES 1
# define EXIT_END 0
# define ABS(x) (x < 0) ? -x : x
# define    EXIT_KEY  53
# define    KEY_LEFT  123
# define    KEY_RIGHT 124
# define    KEY_DOWN  125
# define    KEY_UP    126
# define    WHITE     16777215
# define    RED       9830400
# define    SPEED     0.3
# define    Ceilling 3381759
# define    Floor       2697513 
# define    HELP_KEY 4
# define    TILE_SIZE 64
// Struct to Store rgb();
typedef struct s_color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    unsigned int color;
}             t_color;

// Struct to Store Texture Path's
typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    char *sprite;

    char *sky;
    void  *sky_xpm;
    int *sky_data;
    char *floor;
    int  *floor_xpm;
}               t_texture;

// Struct to get Directions
typedef struct s_direction
{
    // Angles 
    float fov;
    float angle;

    // Direction 
    float x;
    float y;

}              t_direction;

// Struct For Ray Facing 
typedef struct s_facing
{
    int down;
    int right;
    int left;
    int up;

    float dist;
}               t_facing;

// Struct For wall

typedef struct s_wall
{
    int x;
    int y;
}               t_wall;

// Struct to get Data from *.cub file [MAP_FILE]
typedef struct s_data
{
    // Mlx Window Pointers
    void    *mlx_ptr;
    void    *mlx_win;
    void    *mlx_image;
    // Resolution [Width && Height]
    int x;
    int y;

    // Player Initial Position
    float player_x;
    float player_y;

    // Ceilling Colors
    t_color ceilling;

    // Floor Colors
    t_color floor;

    // Texture Path's
    t_texture path;

    // Map [0 || 1 || 2]  1: Wall 2: objects 
    char *map[50];
    int index;
    float cols;
    float x_l;
    float y_l;

    // Direction
    t_direction dir;

    // MiniMap Scale
    float scale;

    // Ray facing 
    t_facing ray;

    // Wall 
    t_wall wall;
    int map_ln;
    // Key Pressed
    int key_on;

    int     width;
    int     height;

    int     draw_menu;
    void   *img_px;
    int    *img_id;

    int img_w;
    int img_h;
    int wasVert;
}               t_data;

t_data data;

// Functions used all along the Execution

int      ft_read_map(char **str);
void     ft_wall_casting(int col, float angle, int wasVert);
void     ft_draw_rectangle(int i0, int j0);
int      isWall(t_direction position);
int      ft_intersection(float col, float rayangle);
void     ft_draw_line(float X0, float Y0, float X1, float Y1, int color);
void     pixel_put(float x, float y, int color);
void     ft_get_distance();
void     ft_find_intersection(int col, float ray_angle);
void     RayFacing(float angle);
void    normalize(float *angle);
unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b);

#endif