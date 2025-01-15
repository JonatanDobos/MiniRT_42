#ifndef UTILS_H
# define UTILS_H

t_cint32	cleanup(t_rt *rt, t_cint32 status);

//	if many more math functions come, create ft_math.h
t_vec3	normalize(t_vec3 v);
t_vec3	subtract(t_vec3 a, t_vec3 b);
double	dot_product(t_vec3 a, t_vec3 b);

#endif