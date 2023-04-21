//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

void	print_coords(t_coord coord);

void rotate_camera_x(double theta, t_coord *D)
{
    D->y = D->y * cos(theta) + D->z * sin(theta);
    D->z = -D->y * sin(theta) + D->z * cos(theta);
}

void rotate_camera_y(double theta, t_coord *D)
{
    D->x = D->x * cos(theta) + D->z * sin(theta);
    D->z = -D->x * sin(theta) + D->z * cos(theta);
}

void rotate_camera_z(double theta, t_coord *D)
{
    D->x = D->x * cos(theta * M_PI / 180) - D->y * sin(theta * M_PI / 180);
    D->z = D->x * sin(theta * M_PI / 180) + D->y * cos(theta * M_PI / 180);
}

double dot(double v1, double v2, double t1, double t2)
{
    return (v1 * t1 + v2 * t2);
}

double len2(t_point vector)
{
    return (sqrt((pow(vector.x, 2) + pow(vector.y, 2))));
}


t_point find_theta(void)
{
    t_point theta;

    theta.x = dot(0, 1, m()->camera.vector.y, m()->camera.vector.z);
    theta.x = acos(theta.x / len2((t_point){m()->camera.vector.y, m()->camera.vector.z}));
    theta.y = dot(0, 1, m()->camera.vector.x, m()->camera.vector.z);
    theta.y = acos(theta.y / len2((t_point){m()->camera.vector.x, m()->camera.vector.z}));
    return (theta);
}

void  rotate_camera(t_point theta, t_coord *D)
{
    if (m()->camera.vector.x < 0)
        theta.y *= -1;
    if (m()->camera.vector.y < 0)
        theta.x *= -1;
    rotate_camera_x(theta.x, D);
    rotate_camera_y(theta.y, D);
}