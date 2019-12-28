/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:30:53 by malaoui           #+#    #+#             */
/*   Updated: 2019/12/28 16:42:36 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 
  
//DDA Function for line generation 
void ft_draw_line(int X0, int Y0, int X1, int Y1) 
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
        if (data.map[(int)(Y/data.y_l)][(int)(X/data.x_l)] == '1')
            break;
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, X, Y, 5911220);  // put pixel at (X,Y) 
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
                             // generation step by step 
    } 
}

void  ft_calcul_lenght(void)
{
    // int i;
    // int j;
    // int cpy;

    // i = 0;
    // j = 0;
    // cpy = 0;
    // while (data.map[i] != '\0')
    // {
    //     while (data.map[i][j] != '\0')
    //     {
    //         if (data.map[i][j] == ' ')
    //             j++;
    //         cpy++;
    //         j++;
    //     }
    //     i++;
    // }

    data.x_l = data.x/data.cols;
    data.y_l = data.y/data.index;
}

void ft_draw_wall(int i0, int j0)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < data.x_l)
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.x_l*i0 + i++, data.y_l*j0, 5911220);
    while (j < data.y_l)
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.x_l*i0, data.y_l*j0 + j++, 5911220);
    i = 0;
    j = 0;
    while (i < data.x_l)
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.x_l*i0 + i++, data.y_l*j0 + data.y_l, 5911220);
    while (j < data.y_l)
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.x_l*i0 + data.x_l, data.y_l*j0 + j++, 5911220);
}

void    ft_draw_player(void)
{
    float i;
    int j;


    i = data.dir.fov/data.x;
    j = 0;
    mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.player_x * data.x_l, data.player_y * data.y_l, 5911220);
    // data.dir.x = cos((data.dir.angle + data.dir.fov/2)*M_PI/180) * 150;
    // data.dir.y = sin((data.dir.angle + data.dir.fov/2)*M_PI/180) * 150;
    // ft_draw_line(data.player_x*data.x_l, data.player_y*data.y_l, data.player_x*data.x_l + data.dir.x, data.player_y*data.y_l + data.dir.y);
    while (j < 66)
    {
        data.dir.x = cos((data.dir.angle + data.dir.fov/2 + i)*M_PI/180);
        data.dir.y = sin((data.dir.angle + data.dir.fov/2 + i)*M_PI/180);
        ft_draw_line(data.player_x*data.x_l, data.player_y*data.y_l, data.player_x*data.x_l + data.dir.x*150, data.player_y*data.y_l + data.dir.y*150);
        // data.dir.x = cos((data.dir.angle - data.dir.fov/2 + i)*M_PI/180);
        // data.dir.y = sin((data.dir.angle - data.dir.fov/2 + i)*M_PI/180);
        // ft_draw_line(data.player_x*data.x_l, data.player_y*data.y_l, data.player_x*data.x_l + data.dir.x*100 , data.player_y*data.y_l + data.dir.y*100);
        i--;
        j++;
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
                ft_draw_wall(j , i);
            j++;
            if (data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'E' || data.map[i][j] == 'S')
            {
                if (data.key_pressed == 0)
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
                ft_draw_player();
                }
            }
        }
        i++;
    }
}

int     isWall(t_direction position)
{
    if (data.map[(int)position.y][(int)position.x] == '1')
        return (1);
    return (0);   
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
    data.key_pressed = 1;
    if (key == EXIT_KEY)
		exit(1);
    t_direction newPlayerPosition;
    newPlayerPosition.x =  data.player_x;
    newPlayerPosition.y = data.player_y;
    t_direction movement = ft_vector_from_angle(data.dir.angle, 0.6);
    if (key == KEY_DOWN)
    {
        newPlayerPosition.y -= movement.y;//1 * sin((data.dir.angle - data.dir.fov / 2)*M_PI/180);
        newPlayerPosition.x -= movement.x;//1 * cos((data.dir.angle - data.dir.fov / 2)*M_PI/180);
    }
    if (key == KEY_UP )
    {
        newPlayerPosition.y += movement.y;//1 * sin((data.dir.angle - data.dir.fov / 2)*M_PI/180);
        newPlayerPosition.x += movement.x;//1 * cos((data.dir.angle - data.dir.fov / 2)*M_PI/180);
    }
    if (key == KEY_LEFT )
    {
        data.dir.angle -= 5;
    }
    if (key == KEY_RIGHT )
    {
        data.dir.angle += 5;
    }
    if (!isWall(newPlayerPosition))
    {
        data.player_x = newPlayerPosition.x;
        data.player_y = newPlayerPosition.y;
    }
    return (1);
}

int     ft_manage(void)
{
    mlx_key_hook (data.mlx_win, ft_keys, "hi");
    mlx_clear_window(data.mlx_ptr, data.mlx_win);
    ft_draw_player();
	ft_draw_map();
    return (0);
}

int     main(int argc, char **argv)
{
    int i;

    i = 0;
    data.index = 0;
    data.dir.fov = 66;
    data.key_pressed = 0;
    data.map = (char **)malloc(sizeof(char *) * 15);
    if (ft_read_map(&argv[1]) == 0)
        return (EXIT_FAILURE);
    else
        printf("[+] Getting Data From : %s !\n", argv[1]);
    ft_calcul_lenght();
    if (!(data.mlx_ptr = mlx_init()))
       return (EXIT_FAILURE);
       //printf("%d | %d\n", data.x_l , data.y_l);
    data.mlx_win = mlx_new_window(data.mlx_ptr, data.x, data.y, "The Manhattan Project");
    mlx_loop_hook(data.mlx_ptr, ft_manage, "hi");
    mlx_loop(data.mlx_ptr);
    return (EXIT_END);
}