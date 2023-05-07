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
    double temp;

    temp = viewport_pt->x;
    viewport_pt->x = viewport_pt->x * cos(theta) + viewport_pt->z * sin(theta);
    viewport_pt->z = -temp * sin(theta) + viewport_pt->z * cos(theta);
}

void rotate_z(double theta, t_coord *viewport_pt)
{
    double temp;

    temp = viewport_pt->x;
    viewport_pt->x = viewport_pt->x * cos(theta) - viewport_pt->y * sin(theta);
    viewport_pt->y = temp * sin(theta) + viewport_pt->y * cos(theta);
}

double dot(double v1, double v2, double t1, double t2)
{
    return (v1 * t1 + v2 * t2);
}

double len2(t_point vector)
{
    return (sqrt((pow(vector.x, 2) + pow(vector.y, 2))));
}

t_coord find_projection(t_coord new_vector, t_coord plane)
{
    double c;

    c = dot_product(new_vector, plane) / pow(vector_length(plane), 2);
    new_vector = do_op_coords(
            SUBTRACT,
            new_vector,
            coord_constant_op(MULTIPLY, plane, c));
    return (new_vector);
}

double find_theta_x(t_coord original, t_coord new_vector)
{
    double x;

    x = dot(original.y, original.z, new_vector.y, new_vector.z);
    if (!len2((t_point){new_vector.y, new_vector.z}) || !len2((t_point){original.y, original.z}))
        x = 0;
    else if (x > 0)
        x = acos(x / len2((t_point){new_vector.y, new_vector.z}));
    else
        x = M_PI - acos(x / len2((t_point){new_vector.y, new_vector.z}));
    if (new_vector.y < 0)
        x *= -1;
    return (x);
}

double find_theta_y(t_coord original, t_coord new_vector)
{
    double y;

    y = dot(original.x, original.z, new_vector.x, new_vector.z);
    if (!len2((t_point){new_vector.x, new_vector.z}) || !len2((t_point){original.x, original.z}))
        y = 0;
    else /* if (y > 0) */
        y = acos(y / len2((t_point){new_vector.x, new_vector.z}));
    // else
    //     y = M_PI - acos(y / len2((t_point){new_vector.x, new_vector.z}));
    if (new_vector.x  < 0)
        y *= -1;
    return (y);
}

t_coord find_theta(t_coord original, t_coord new_vector)
{
    t_coord theta;

    theta.x = find_theta_x(original, new_vector);
    theta.y = find_theta_y(original, new_vector);
    theta.z = dot(original.x, original.y, new_vector.x, new_vector.y);
    if (!len2((t_point){new_vector.x, new_vector.y}) || !len2((t_point){original.x, original.y}))
        theta.z = 0;
    else if (theta.z > 0)
        theta.z = acos(theta.z / len2((t_point){new_vector.x, new_vector.y}));
    else
        theta.z = - M_PI + acos(theta.z / len2((t_point){new_vector.x, new_vector.y}));
    return (theta);
}

void  rotate_camera(t_coord theta, t_coord *viewport_pt)
{

    rotate_x(theta.x, viewport_pt);
    rotate_y(theta.y, viewport_pt);
}

void	rotate_plane(int k)
{
	t_plane	*plane;

	plane = (t_plane *)(*who_movin());
	if (k == XK_b)
        rotate_x(0.02, &plane->vector);
	else if (k == XK_h)
        rotate_x(-0.02, &plane->vector);
    else if (k == XK_n)
        rotate_y(0.02, &plane->vector);
    else if (k == XK_j)
        rotate_y(-0.02, &plane->vector);
    else if (k == XK_m)
        rotate_z(0.02, &plane->vector);
    else if (k == XK_k)
        rotate_z(-0.02, &plane->vector);
} 