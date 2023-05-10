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
    return (c * (c < a) + a * (a < c));
}

void    update_caps(t_cylinder *cy, t_coord normal)
{
    normalize(&normal);
    cy->top.vector = cy->vector;
    cy->bottom.vector = cy->vector;
    cy->top.coord = do_op_coords(ADD, cy->coord, coord_constant_op(MULTIPLY, normal, cy->height / 2));
    cy->bottom.coord = do_op_coords(SUBTRACT, cy->coord, coord_constant_op(MULTIPLY, normal, cy->height / 2));
}

double cylinder_collision_plane(t_coord origin, t_coord ray, t_cylinder *body)
{
    t_point top;
    t_point bottom;
    t_coord r_top;
    t_coord r_bottom;

    update_caps(body, body->vector);
    top = plane_collision(ray, &body->top, origin);
    bottom = plane_collision(ray, &body->bottom, origin);
    r_top = do_op_coords(ADD, origin, coord_constant_op(MULTIPLY, ray, top.x));
    r_top = do_op_coords(SUBTRACT, body->top.coord, r_top);
    r_bottom = do_op_coords(ADD, origin, coord_constant_op(MULTIPLY, ray, bottom.x));
    r_bottom = do_op_coords(SUBTRACT, body->bottom.coord, r_bottom);
    top.y = vector_length(r_top);
    bottom.y = vector_length(r_bottom);
	if (fabs(top.x) > INT_MAX || fabs(bottom.x) > INT_MAX)
		return (INT_MAX);
    top.x += (INT_MAX + fabs(top.x) + 1) * (top.y > body->diameter / 2);
    bottom.x += (INT_MAX + fabs(bottom.x) + 1) * (bottom.y > body->diameter / 2);
    return (top.x * (top.x < bottom.x) + bottom.x * (bottom.x < top.x));
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
    return (fabs(vector_length(center_to_coord) * cos(angle)));
}

int in_cylinder(double t, t_cylinder *cy, t_coord ray)
{
    return (find_distance_in_axis(t, cy, ray) > (cy->height / 2));
}

int in_plane(t_coord point, t_cylinder *cy)
{
    if (fabs(dot_product(cy->vector, do_op_coords(SUBTRACT, cy->top.coord, point)) - 0) < 0.001|| \
        fabs(dot_product(cy->vector, do_op_coords(SUBTRACT, cy->bottom.coord, point)) - 0) < 0.001)
        return (1);
    return (0);
}

t_coord find_normal(double t, t_cylinder *cy, t_coord ray)
{
    t_coord normal;
    t_coord point_in_axis;
    t_coord point_in_surface;
    double  dist;

    point_in_surface = do_op_coords(ADD, m()->camera->coord, coord_constant_op(MULTIPLY, ray, t));
    if (in_plane(point_in_axis, cy))
        return (cy->vector);
    dist = find_distance_in_axis(t, cy, ray) / vector_length(cy->vector);
    point_in_axis = coord_constant_op(MULTIPLY, cy->vector, dist);
    point_in_axis = do_op_coords(ADD, cy->coord, point_in_axis);
    normal = do_op_coords(SUBTRACT, point_in_surface, point_in_axis);
    return (normal);
}

t_point cylinder_collision(t_coord origin, t_coord ray, t_cylinder *body)
{
    t_point new;
    double surface = INT_MAX;
    double plane = INT_MAX;

   	surface = cylinder_collision_surface(origin, ray, body);
    plane = cylinder_collision_plane(origin, ray, body);
    new.x = surface * (surface < plane) + plane * (plane < surface);
    new.y = 0;
    return (new);
}