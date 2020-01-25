/* ************************************************************************** */
/*                              (                                              */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:30:53 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/30 12:59:24 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"


int    *img_data;

void    pixel_put(float x, float y, int color)
{
    if ((x >= 0 && x < data.x) && (y >= 0 && y < data.y))
        img_data[((int)x +  ((int)y) * data.y)] = color;
    else 
        return ;
}

int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 

void ft_draw_line(float X0, float Y0, float X1, float Y1, int color) 
{
    int i;
    int dx;
    int dy;
    int steps;
    float Xinc;
    float Yinc;
    float X; 
    float Y;

    i = 0;
    dx = X1 - X0; 
    dy = Y1 - Y0; 
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
    Xinc = dx / (float) steps; 
    Yinc = dy / (float) steps; 
    X = X0; 
    Y = Y0;
    while (i < steps) 
    {
        pixel_put(X, Y, color);
        X += Xinc;
        Y += Yinc;
        i++;
    } 
}

void  ft_calcul_lenght(void)
{
    // data.x_l = data.x/data.cols;
    // data.y_l = data.y/data.index;

    data.wall.x = TILE_SIZE;
    data.wall.y = TILE_SIZE;
    
    // // Minimap Scale 
    data.x_l = TILE_SIZE;
    data.y_l = TILE_SIZE;
}

void ft_draw_rectangle(int i0, int j0)
{
    int i;
    int j;
    int x;
    int y;

    i = 0;
    j = 0;
    x = 10;
    y = 10;
    while (i < x)
    {
        pixel_put(x*i0 + i, j0*y, WHITE);
        pixel_put(x*i0 + i, j0*y + y, WHITE);
        i++;
    }
    while (j < y)
    {
        pixel_put(x*i0, y*j0 + j, WHITE);
        pixel_put(x*i0 + x, y*j0 + j, WHITE);
        j++;
    }
}

void    ft_draw_player(void)
{
    float i;
    float j;
    int col;


    col = 0;
    j = data.dir.angle - (data.dir.fov)/2;
    i = data.dir.fov/(data.x);
    while (col < data.x)
    {
        normalize(&j);
        ft_find_intersection(col , j);
        col++;
        j += i;
    }
}

void    ft_add_obj(int i, int j)
{
    
}

void ft_draw_map(void)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data.map[i] != '\0')
    {
        j = 0;
        while (data.map[i][j] != '\0')
        {
            // if (data.map[i][j] == '1' && 0)
            //     ft_draw_rectangle(j , i);
            if (data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'E' || data.map[i][j] == 'S')
            {
                if (!data.key_on)
                {
                    if (data.map[i][j] == 'N')
                        data.dir.angle = 90 * M_PI / 180;
                    if (data.map[i][j] == 'W')
                        data.dir.angle = 0;
                    if (data.map[i][j] == 'E')
                        data.dir.angle = 180 * M_PI / 180;
                    if (data.map[i][j] == 'S')
                        data.dir.angle = 270 * M_PI / 180;
                    data.player_x = j;
                    data.player_y = i;
                }
            }
            // else if (data.map[i][j] == '2')
            //     ft_add_obj(i, j);
            j++;
        }
        i++;
    }
    data.map_ln = i;
}

int     isWall(t_direction position)
{
    if (position.x < 0 || position.y < 0)
        return (0);
    if (data.map[(int)(position.y/data.y_l)][(int)(position.x/data.x_l)] == '1')
        return (1);
    return (0);
}

int     is_Wall(t_direction position)
{
    if (position.x < 0 || position.y < 0)
        return (0);
    if (data.map[(int)(position.y)][(int)(position.x)] == '1')
        return (1);
    return (0);
}

t_direction ft_vector_from_angle(float angle, float size)
{
    t_direction result;
    
    result.x = size * cos(angle);
    result.y = size * sin(angle);
    return (result);
}

int   ft_keys(int key, void *ptr)
{
    ptr = NULL;
    t_direction newPlayerPosition;
    t_direction movement = ft_vector_from_angle(data.dir.angle, SPEED);

    data.key_on = 1;
    newPlayerPosition.x = data.player_x;
    newPlayerPosition.y = data.player_y;

    if (key == HELP_KEY)
    {
        data.draw_menu = 1;
        mlx_string_put(data.mlx_ptr, data.mlx_win, 150, 150, WHITE, "---> EXIT");
        return (1);
    }
    if (key == EXIT_KEY)
		exit(1);
    if (key == KEY_LEFT)
        data.dir.angle -= 5 * M_PI / 180;
    if (key == KEY_RIGHT)
        data.dir.angle += 5 * M_PI / 180;

    if (key == KEY_DOWN)
    {
        newPlayerPosition.y -= movement.y;
        newPlayerPosition.x -= movement.x;
    }
    if (key == KEY_UP)
    {
        newPlayerPosition.y += movement.y;
        newPlayerPosition.x += movement.x;
    }
    if (!is_Wall(newPlayerPosition))
    {
        data.player_x = newPlayerPosition.x;
        data.player_y = newPlayerPosition.y;
    }
    return (1);
}

int ft_mouse(int button, int x, int y, void *param)
{
    y = 0;
    button = 1;
    param = NULL;
    if (x >= 0 && x < data.x/2)
        data.dir.angle -= 5 * M_PI / 180;
    else
        data.dir.angle += 5 * M_PI / 180;
    return (1);
}

int     ft_mouse_pressed(int keycode, void *param)
{
    ft_keys(keycode, param);
    return (1);
}

int     ft_exit(int keycode , void* param)
{
    exit(1);
}

void    ft_image_settings()
{
    int     bpp = 0;
    int     size_line = 0;
    int     endian = 0;

    data.mlx_image = mlx_new_image(data.mlx_ptr, data.x, data.y);
    img_data = (int *)mlx_get_data_addr(data.mlx_image, &bpp, &size_line, &endian);
    
    /* Wall Tetures */
    int bits_per_pixel = 0;
    int size_l = 0;
    int end = 0;

    data.img_px = mlx_xpm_file_to_image(data.mlx_ptr, "textures/stone.xpm", &data.img_w, &data.img_h);
    data.img_id = (int *)mlx_get_data_addr(data.img_px, &bits_per_pixel, &size_l, &end);
    printf("1\n");
    int w = 0;
    int h = 0;
    int bi = 0;
    int si = 0;
    int en = 0;
    data.path.sky_xpm = mlx_xpm_file_to_image(data.mlx_ptr, "textures/sky.xpm", &w, &h);
    data.path.sky_data = (int *)mlx_get_data_addr(data.path.sky_xpm, &bi, &si, &en);
}

int     ft_manage_event(void)
{
    mlx_hook(data.mlx_win, 2, 1L<<0, ft_mouse_pressed, "hi");
    mlx_hook(data.mlx_win, 17, 1L<<5, ft_exit, "hi");
    mlx_mouse_hook(data.mlx_win, ft_mouse, "mouse");
    mlx_key_hook(data.mlx_win, ft_keys, "hi");
    ft_draw_map();
    ft_draw_player();
    mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.mlx_image, 0, 0);
    if (data.mlx_image == NULL)
        data.mlx_image = mlx_new_image(data.mlx_ptr, data.x, data.y);
    else
        mlx_destroy_image(data.mlx_ptr, data.mlx_image);
    return (0);
}


int     main(int argc, char **argv)
{
    int     i;
    int     bpp = 0;
    int     size_line = 0;
    int     endian = 0;
    int     w = 0;
    int     h = 0;

    i = 0;
    data.index = 0;
    data.dir.fov = 60 * M_PI / 180;
    data.scale = 0.2;
    data.key_on = 0;
    data.draw_menu = 0;
    data.mlx_image = NULL;
    if (ft_read_map(&argv[argc - 1]) == 0)
        return (EXIT_FAILURE);
    else
        ft_printf("[+] Getting Data From : %s !\n", argv[1]);
    ft_calcul_lenght();
    data.width = data.map_ln * TILE_SIZE;
    data.height = ft_strlen(data.map[0]) * TILE_SIZE;
    if (!(data.mlx_ptr = mlx_init()))
       return (EXIT_FAILURE);
    data.mlx_win = mlx_new_window(data.mlx_ptr, data.x, data.y, "The Manhattan Project");
    ft_image_settings();
    mlx_loop_hook(data.mlx_ptr, ft_manage_event, "hi");
    mlx_loop(data.mlx_ptr);
    free(&data);
    return (EXIT_END);
}