//
// Created by miguel on 07-05-2023.
//

#include "../../incs/miniRT.h"

int in_cylinder(double t, t_cylinder *cy, t_coord ray);

double cylinder_collision_surface(t_coord origin, t_coord ray, t_cylinder *body)
{
    t_coord B;
    double a;
    double b;
    double c;
    double sqr_mod_eixo;

    sqr_mod_eixo = pow(vector_length((body)->vector), 2);
    B = do_op_coords(SUBTRACT, origin, (body)->coord);
    a = dot_product(ray, ray) \
        * sqr_mod_eixo \
        - pow(dot_product(ray, (body)->vector), 2);
    b = 2 * dot_product(B, ray) * sqr_mod_eixo \
            - 2 * dot_product(ray, body->vector) * dot_product(B, body->vector);
    c = (dot_product(B, B) - pow((body)->diameter / 2, 2)) * sqr_mod_eixo \
        - pow(dot_product(B, (body)->vector), 2);
    double discriminant = (b * b) - (4*a*c);
    if (discriminant < 0)
        return (INT_MAX);
    c = (-b + sqrt(discriminant)) / (2 * a);
    a = (-b - sqrt(discriminant)) / (2 * a);
    c += in_cylinder(c, (t_cylinder *)body, ray) * (INT_MAX + fabs(c) + 1);
    a += in_cylinder(a, (t_cylinder *)body, ray) * (INT_MAX + fabs(a) + 1);
	// if (c < INT_MAX || a < INT_MAX)
	// 	printf("oi\n");
    return (c * (c < a) + a * (a < c));
}

double find_distance_in_axis(double t, t_cylinder *cy, t_coord ray)
{
    t_coord cross;
    t_coord center_to_coord;
    double  angle;

    cross = do_op_coords(ADD, m()->camera->coord, coord_constant_op(MULTIPLY, ray, t));
    center_to_coord = do_op_coords(SUBTRACT, cy->coord, cross);
    angle = dot_product(center_to_coord, cy->vector);
    angle = acos(angle / (vector_length(center_to_coord) * vector_length(cy->vector)));
	// if (fabs(vector_length(center_to_coord) * cos(angle))  < (cy->height / 2))
	// 	printf("oi\n");
    return (fabs(vector_length(center_to_coord) * cos(angle)));
}

int in_cylinder(double t, t_cylinder *cy, t_coord ray)
{
    return (find_distance_in_axis(t, cy, ray) > (cy->height / 2));
}

t_coord find_normal(double t, t_cylinder *cy, t_coord ray)
{
    t_coord normal;
    t_coord point_in_axis;
    t_coord point_in_surface;
    double  dist;

    point_in_surface = coord_constant_op(MULTIPLY, ray, t);
    dist = find_distance_in_axis(t, cy, ray) / vector_length(cy->vector);
    point_in_axis = coord_constant_op(MULTIPLY, cy->vector, dist);
    point_in_axis = do_op_coords(ADD, cy->coord, point_in_axis);
    normal = do_op_coords(SUBTRACT, point_in_surface, point_in_axis);
    return (normal);
}

t_point cylinder_collision(t_coord origin, t_coord ray, t_cylinder *body)
{
    t_point new;
    // t_coord x;
    double surface;

    surface = cylinder_collision_surface(origin, ray, body);
    new.x = surface;
	// if (new.x < INT_MAX)
	// 	printf("oi\n");
    // x = coord_constant_op(MULTIPLY, ray, surface);
    // if (ray.x == 0 && !ray.y && ray.z)
    //     print_coords(x);
    new.y = 0;
    return (new);
}