/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:31:16 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/28 15:48:22 by malaoui          ###   ########.fr       */
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
#include "get_next_line/get_next_line.h"
#include <fcntl.h>

// Marcos 
# define EXIT_SUCCES 1
# define EXIT_END 0
# define ABS(x) (x < 0) ? -x : x
# define    EXIT_KEY 53
# define    KEY_LEFT 123
# define    KEY_RIGHT 124
# define    KEY_DOWN 125
# define    KEY_UP 126
# define    WHITE 16777215
# define     RED 9830400
// Struct to Store rgb();

typedef struct s_color
{
    int r;
    int g;
    int b; 
}             t_color;

// Struct to Store Texture Path's

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    char *sprite;
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

// Struct to get Data from *.cub file [MAP_FILE]

typedef struct s_data
{
    // Mlx Window Pointers
    void    *mlx_ptr;
    void    *mlx_win;
    
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
    char **map;
    int index;
    float cols;
    float x_l;
    float y_l;

    // Direction
    t_direction dir;

    // Key is Pressed
    int key_pressed;
}               t_data;

t_data data;

// Functions used all along the Execution
int     ft_read_map(char **str);
#endif