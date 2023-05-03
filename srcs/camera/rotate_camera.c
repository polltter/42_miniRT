//
// Created by miguel on 21-04-2023.
//

#include "../../incs/miniRT.h"

void	print_coords(t_coord coord);

void rotate_x(double theta, t_coord *viewport_pt)
{
    double temp;

    temp = viewport_pt->y;
    viewport_pt->y = viewport_pt->y * cos(theta) + viewport_pt->z * sin(theta);
    viewport_pt->z = -temp * sin(theta) + viewport_pt->z * cos(theta);
}

void rotate_y(double theta, t_coord *viewport_pt)
{
    viewport_pt->x = viewport_pt->x * cos(theta) + viewport_pt->z * sin(theta);
    viewport_pt->z = -viewport_pt->x * sin(theta) + viewport_pt->z * cos(theta);
}

void rotate_z(double theta, t_coord *viewport_pt)
{
    viewport_pt->x = viewport_pt->x * cos(theta * M_PI / 180) - viewport_pt->y * sin(theta * M_PI / 180);
    viewport_pt->z = viewport_pt->x * sin(theta * M_PI / 180) + viewport_pt->y * cos(theta * M_PI / 180);
}

double dot(double v1, double v2, double t1, double t2)
{
    return (v1 * t1 + v2 * t2);
}

double len2(t_point vector)
{
    return (sqrt((pow(vector.x, 2) + pow(vector.y, 2))));
}


t_coord find_theta(t_coord original, t_coord new_vector)
{
    t_coord theta;

    theta.x = dot(original.y, original.z, new_vector.y, new_vector.z);
    theta.x = acos(theta.x / len2((t_point){new_vector.y, new_vector.z}));
    theta.y = dot(original.x, original.z, new_vector.x, new_vector.z);
    theta.y = acos(theta.y / len2((t_point){new_vector.x, new_vector.z}));
	theta.z = dot(original.x, original.y, new_vector.x, new_vector.y);
    theta.z = acos(theta.z / len2((t_point){new_vector.x, new_vector.y}));
    return (theta);
}

void  rotate_camera(t_coord theta, t_coord *viewport_pt)
{
	theta.z = 0;
    if (m()->camera->vector.x < 0)
        theta.y *= -1;
    if (m()->camera->vector.y < 0)
        theta.x *= -1;
    rotate_x(theta.x, viewport_pt);
    rotate_y(theta.y, viewport_pt);
    rotate_y(theta.z, viewport_pt);
}

void	rotate_plane(int k)
{
	t_plane	*plane;

	plane = (t_plane *)(*who_movin());
	if (k == XK_Left)
		plane->vector.x -= 0.1;
	else if (k == XK_Right)
		plane->vector.x += 0.1;
	else if (k == XK_Down)
		plane->vector.z -= 0.1;
	else if (k == XK_Up)
		plane->vector.z += 0.1;
	// plane->theta = find_theta((t_coord){0, 0, 1}, plane->vector);
	// if (plane->vector.x < 0)
    //     plane->theta.y *= -1;
	// if (plane->vector.y < 0)
    //     plane->theta.x *= -1;
	// rotate_x(plane->theta.x, &plane->vector);
    // rotate_y(plane->theta.y, &plane->vector);
    // rotate_y(plane->theta.z, &plane->vector);
	// print_coords(plane->vector);
} 