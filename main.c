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

void    pixel_put(float x, float y, int color)
{
    if ((x >= 0 && x <= data.x) && (y >= 0 && y <= data.y))
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y , color);
    else 
        return ;
}

int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 

void ft_draw_line(float X0, float Y0, float X1, float Y1) 
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
    while (i <= steps) 
    {
        pixel_put(X, Y, RED);
        X += Xinc;
        Y += Yinc;
        i++;
    } 
}

void  ft_calcul_lenght(void)
{
    // data.x_l = data.x/data.cols;
    // data.y_l = data.y/data.index;

    data.wall.x = 32;
    data.wall.y = 32;
    
    // // Minimap Scale 
    data.x_l = 32;
    data.y_l = 32;
}

void ft_draw_rectangle(int i0, int j0)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < data.x_l)
    {
        pixel_put(data.x_l*i0 + i, j0*data.y_l, WHITE);
        pixel_put(data.x_l*i0 + i, j0*data.y_l + data.y_l, WHITE);
        i++;
    }
    while (j < data.y_l)
    {
        pixel_put(data.x_l*i0, data.y_l*j0 + j, WHITE);
        pixel_put(data.x_l*i0 + data.x_l, data.y_l*j0 + j, WHITE);
        j++;
    }
}

void    ft_draw_player(void)
{
    float i;
    float j;
    int col;


    col = data.x -1 ;
    j = data.dir.angle - (data.dir.fov)/2;
    i = data.dir.fov/data.x;
    while (col <= data.x)
    {
        ft_find_intersection(j*M_PI/180);
        //ft_wall_casting(col, j);
        j += i;
        col++;
    }
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
            if (data.map[i][j] == '1')
                ft_draw_rectangle(j , i);
            else if (data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'E' || data.map[i][j] == 'S')
            {
                if (!data.key_on)
                {
                if (data.map[i][j] == 'N')
                    data.dir.angle = 90;
                if (data.map[i][j] == 'W')
                    data.dir.angle = 0;
                if (data.map[i][j] == 'E')
                    data.dir.angle = 180;
                if (data.map[i][j] == 'S')
                    data.dir.angle = 270;
                    data.player_x = j;
                    data.player_y = i;
                }
            }
            j++;
        }
        i++;
    }
}

int     isWall(t_direction position)
{
    if (position.x < 0 || position.y < 0 )
        return 0;
    if (data.map[(int)(position.y/data.y_l)][(int)(position.x/data.x_l)] == '1')
        return (0);
    return (1);   
}

t_direction ft_vector_from_angle(double angle, double size)
{
    t_direction result;

    result.x = size * cos(angle * M_PI / 180);
    result.y = size * sin(angle * M_PI / 180);
    return (result);
}

int   ft_keys(int key, void *ptr)
{
    ptr = NULL;
    t_direction newPlayerPosition;
    t_direction movement = ft_vector_from_angle(data.dir.angle, 0.2);

    data.key_on = 1;
    newPlayerPosition.x = data.player_x;
    newPlayerPosition.y = data.player_y;
    if (key == EXIT_KEY)
		exit(1);
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
    if (key == KEY_LEFT)
        data.dir.angle -= 2;
    if (key == KEY_RIGHT)
        data.dir.angle += 2;
    if (!isWall(newPlayerPosition))
    {
        data.player_x = newPlayerPosition.x;
        data.player_y = newPlayerPosition.y;
    }
    return (1);
}

int ft_mouse(int button,int x,int y,void *param)
{
    y = 0;
    button = 1;
    param = NULL;
    if (x >= 0 && x < data.x/2)
        data.dir.angle += 5;
     else
        data.dir.angle -= 5;
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

int     ft_manage(void)
{
    int i;

    i = 0;
    mlx_clear_window(data.mlx_ptr, data.mlx_win);
    mlx_hook(data.mlx_win, 2, 1L<<0, ft_mouse_pressed, "hi");
    mlx_hook(data.mlx_win, 17, 1L<<5, ft_exit, "hi");
    mlx_mouse_hook(data.mlx_win, ft_mouse, "mouse");
    ft_draw_map();
    ft_draw_player();
    return (0);
}


int     main(int argc, char **argv)
{
    int i;

    i = 0;
    data.index = 0;
    data.dir.fov = 60;
    data.scale = 0.2;
    data.map = (char **)malloc(sizeof(char *) * 15);
    data.key_on = 0;
    if (ft_read_map(&argv[argc - 1]) == 0)
        return (EXIT_FAILURE);
    else
        printf("[+] Getting Data From : %s !\n", argv[1]);
    ft_calcul_lenght();
    if (!(data.mlx_ptr = mlx_init()))
       return (EXIT_FAILURE);
    data.mlx_win = mlx_new_window(data.mlx_ptr, data.x, data.y, "The Manhattan Project");
    mlx_key_hook (data.mlx_win, ft_keys, "hi");
    mlx_loop_hook(data.mlx_ptr, ft_manage, "hi");
    mlx_loop(data.mlx_ptr);
    free(&data);
    return (EXIT_END);
}