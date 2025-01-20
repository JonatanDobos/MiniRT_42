#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// defines and enums

# define WIN_HEIGHT 900
# define WIN_WIDTH 1600

# define FOV_MAX 180.0

// Custom in-program rendering resolution

# define RNDR_RES 360

// Camera manipulation speeds

# define FOV_SCROLL_SPEED 1.0f

# define CAM_ROTATION_SPEED 0.05f

# define CMS 0.8f
# define CAM_MOVE_SPEED (t_vec4){CMS, CMS, CMS, CMS}

// Math

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define EPSILON 1e-6f

// Custom error messages

# define EMSG_1 "Insufficient line in .rt file."
# define EMSG_2 "Unknown identifier in .rt file."
# define EMSG_3 "Unknown symbol in .rt file."
# define EMSG_4C "Unsupported amount of cameras (C)."
# define EMSG_4A "Unsupported amount of ambient light (A)."
# define EMSG_4L "Unsupported amount of Lights (L)."
# define EMSG_4O "Unsupported amount of objects (sp, cy, pl)."

// Custom error code macro's

# define CUST_ERR_AMOUNT 4

/**
 * @brief Custom error code macros (range <= -2).
 * @param ERTRN A fixed option (errset() & nsave())
 * which returns the set value.
 * @param ESET A fixed option (errset()),
 * or returned by errset() when waiting for address.
 * @param ERRNSET Returned by errset() when static is NULL.
 * @param ERRFORM Format error (in file).
 * @param ERRFEXT Wrong file extension.
 */
enum	custom_error
{
	ERTRN = -1,
	ESET = -2,
	ERRNSET = -3,
	ERRFORM = -4,
	ERRFEXT = -5
};

enum	coord
{
	X = 0,
	Y,
	Z,
	W
};

enum	color
{
	R = 0,
	G,
	B,
	A
};

#endif
