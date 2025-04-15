#include <parsing.h>
#include <mathRT.h>

/**
 * @brief Skips till it encounters a new numerical value.
 * @param str Ptr in string to skip from.
 * @return char* to the first character of the next value in str,
 * or \0 if it encountered no whitespace.
 * @note If the given *str is pointing to a value (digit, period or minus),
 * it will also skip that until it finds the next separate value.
 */
char	*nxtv(char *str)
{
	while (*str != '\0' && ft_isspace(*str) == false && *str != ',')
		++str;
	while (*str != '\0' && *str != '.' && *str != '-' && \
	ft_isdigit(*str) == false)
		++str;
	return (str);
}

/**
 * @brief Skips till it encounters a new numerical value.
 * @param str Address of ptr in string to skip from.
 * @return char* to the first character of the next value in str,
 * or \0 if it encountered no whitespace.
 * @note If the given *str is pointing to a value (digit, period or minus),
 * it will also skip that until it finds the next separate value.
 * @note Also changes the original ptr given under the address **str!
 */
char	*nxtvp(char **str)
{
	char	*c;

	c = *str;
	while (*c != '\0' && ft_isspace(*c) == false && *c != ',')
		++c;
	while (*c != '\0' && *c != '.' && *c != '-' && ft_isdigit(*c) == false)
		++c;
	*str = c;
	return (c);
}

float	rt_atof(const char *str)
{
	float	num;
	int		i;
	int		sign;
	int		place;

	num = 0.0F;
	i = 0;
	sign = 1;
	while (ft_isdigit(str[i]) == false || str[i] == '.')
		++i;
	if (i > 0 && str[i - 1] == '-')
		sign = -1;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		num = (num * 10.0F) + (str[i++] - '0');
	if (str[i] != '.')
		return (num * sign);
	++i;
	place = 1;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		num += (float)(str[i++] - '0') / pow(10, (float)(place++));
	return (num * sign);
}

bool	validate_orientation(t_vec4 *or, char **line)
{
	uint8_t	i;

	i = 0;
	while (i <= 2)
	{
		(*or)[i] = rt_atof(nxtvp(line));
		if ((*or)[i] < -1.0F || (*or)[i] > 1.0F)
		{
			return (false);
		}
		++i;
	}
	(*or)[i] = 0.0F;
	*or = vnorm(*or);
	return (true);
}

bool	validate_and_normalize_color(t_vec4 *color, char **line)
{
	int32_t	color_value;
	uint8_t	i;

	i = 0;
	while (i <= 2)
	{
		color_value = atoi32(nxtvp(line));
		if (color_value < 0 || color_value > 255)
			return (false);
		(*color)[i] = (float)color_value / 255.0F;
		++i;
	}
	(*color)[i] = 1.0F;
	return (true);
}






#include <float.h> // For FLT_MAX and FLT_MIN
#include <math.h>  // For fabs()
#include <stdbool.h>

// Skip whitespace and process sign
int process_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

// Process integer part of the number
float process_integer(const char *str, int *idx, bool *overflow)
{
	float	num;
	int 	i;

	i = *idx;
	num = 0.0F;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (num > (FLT_MAX - (str[i] - '0')) / 10.0F)
		{
			*overflow = true;
			*idx = i;
			return (FLT_MAX);
		}
		num = (num * 10.0F) + (str[i] - '0');
		++i;
	}
	*idx = i;
	return (num);
}

// Process fractional part
float process_fraction(const char *str, int *idx, float num, bool *overflow)
{
	float	digit_value;
	float	scale;
	int		i;

	i = *idx;
	scale = 0.1F;
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		{
			digit_value = (str[i++] - '0') * scale;
			if (num > FLT_MAX - digit_value)
			{
				*overflow = true;
				*idx = i;
				return (FLT_MAX);
			}
			num += digit_value;
			scale *= 0.1F;
		}
	}
	*idx = i;
	return (num);
}
#include <limits.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

// Helper function to parse the exponent sign
static int parse_exponent_sign(const char *str, int *i)
{
	int	exp_sign;

	exp_sign = 1;
	if (str[*i] == '-')
	{
		exp_sign = -1;
		(*i)++;
	} 
	else if (str[*i] == '+')
		(*i)++;
	return (exp_sign);
}

// Helper function to parse the exponent value
static int parse_exponent_value(const char *str, int *i, bool *overflow)
{
	int	exp;

	exp = 0;
	while (str[*i] != '\0' && (str[*i] >= '0' && str[*i] <= '9'))
	{
		if (exp > (INT_MAX - (str[*i] - '0')) / 10)
		{
			*overflow = true;
			return (INT_MAX);
		}
		exp = exp * 10 + (str[(*i)++] - '0');
	}
	return (exp);
}

// Helper function to handle positive exponents
static float apply_positive_exponent(float num, int exp, bool *overflow)
{
	while (exp > 0)
	{
		if (num > FLT_MAX / 10.0F)
		{
			*overflow = true;
			return (FLT_MAX);
		}
		num *= 10.0F;
		--exp;
	}
	return (num);
}

// Helper function to handle negative exponents
static float apply_negative_exponent(float num, int exp, bool *overflow)
{
	while (exp < 0)
	{
		num *= 0.1F;
		if (num != 0.0F && fabsf(num) < FLT_MIN)
		{
			*overflow = true;
			return (0.0F);
		}
		++exp;
	}
	return (num);
}

// Main process_exponent function
float process_exponent(const char *str, int *idx, float num, bool *overflow)
{
	int	exp_sign;
	int	exp;

	if ((str[*idx] == 'e' || str[*idx] == 'E') && str[*idx + 1] != '\0')
	{
		++(*idx);
		exp_sign = parse_exponent_sign(str, idx);
		exp = parse_exponent_value(str, idx, overflow);
		if (*overflow == true)
		{
			if (exp_sign > 0)
				return (FLT_MAX);
			return (0.0F);
		}
		exp *= exp_sign;
		if (exp > 0)
			num = apply_positive_exponent(num, exp, overflow);
		else if (exp < 0)
			num = apply_negative_exponent(num, exp, overflow);
	}
	return (num);
}

#include <strings.h>
// Check if string is a special floating point value like "inf" or "nan"
static bool is_special_float(const char *str, float *result)
{
	if (strcasecmp(str, "inf") == 0 || strcasecmp(str, "infinity") == 0)
	{
		*result = INFINITY;
		return (true);
	}
	if (strcasecmp(str, "-inf") == 0 || strcasecmp(str, "-infinity") == 0)
	{
		*result = -INFINITY;
		return (true);
	}
	if (strcasecmp(str, "nan") == 0 || strcasecmp(str, "-nan") == 0)
	{
		*result = NAN;
		return (true);
	}
	return (false);
}

/**
 * @brief Parses the exponent part of a string, including sign and numeric value.
 * @param str The input string.
 * @param i Pointer to the current index in the string (updated during parsing).
 * @return The parsed exponent value, or INT_MAX/INT_MIN in case of overflow.
 */
static int parse_exponent(const char *str, int i)
{
    int exp_sign;
    int exp_val;

	exp_sign = 1;
	exp_val = 0;
    if (str[i] == '-')
    {
        exp_sign = -1;
        ++i;
    }
    else if (str[i] == '+')
        ++i;
    while (str[i] != '\0' && ft_isdigit(str[i]) == true)
    {
        if (exp_val > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (exp_sign > 0)
				return (INT_MAX);
			return (INT_MIN);
		}
        exp_val = exp_val * 10 + (str[i] - '0');
        ++i;
    }
    return (exp_val * exp_sign);
}

// Extract exponent value from string
static int extract_exp_value(const char *str, bool *found_exp)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'e' || str[i] == 'E')
		{
			*found_exp = true;
			return (parse_exponent(str, ++i));
		}
		++i;
	}
	return (0);
}

// Extract mantissa for high-precision checking
static float extract_mantissa(const char *str)
{
	float	mantissa;
	float	frac_scale;
	int		idx;

	mantissa = 0.0F;
	frac_scale = 0.1F;
	idx = 0;
	while (str[idx] == ' ' || str[idx] == '\t')
		++idx;
	if (str[idx] == '-' || str[idx] == '+')
		++idx;
	while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		mantissa = mantissa * 10.0f + (str[idx++] - '0');
	if (str[idx] == '.')
	{
		++idx;
		while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
		{
			mantissa += (str[idx] - '0') * frac_scale;
			frac_scale *= 0.1f;
			++idx;
		}
	}
	return (mantissa);
}

// Check if number is near FLT_MAX and potentially overflows
static bool check_near_max(const char *str, float num)
{
	bool	found_exp;
	float	mantissa;
	int		exp_val;

	found_exp = false;
	mantissa = 0.0F;
	exp_val = 0;
	if (num <= FLT_MAX * 0.999999F)
		return (false);
	exp_val = extract_exp_value(str, &found_exp);
	mantissa = extract_mantissa(str);
	if (exp_val > 38 || (exp_val == 38 && mantissa > 3.4028234F))
		return (true);
	return (false);
}

// Handle overflow based on sign
static float handle_overflow(int sign, float num)
{
	if (num == 0.0F)
		return (0.0F);
	if (sign > 0)
		return (FLT_MAX);
	return (-FLT_MAX);
}

// Process the first part of numeric parsing
static float process_first_part(const char *str, int *i, int sign, bool *overflow)
{
	float	num;

	num = process_integer(str, i, overflow);
	if (*overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	num = process_fraction(str, i, num, overflow);
	if (*overflow == true)
	{
		if (sign > 0)
			return (FLT_MAX);
		return (-FLT_MAX);
	}
	return (num);
}

// Process the second part of numeric parsing
static float process_second_part(const char *str, int *i, float num, int sign, bool *overflow)
{
	num = process_exponent(str, i, num, overflow);
	if (*overflow == true)
		return (handle_overflow(sign, num));
	if (num > FLT_MAX)
	{
		*overflow = true;
		return (FLT_MAX);
	}
	if (check_near_max(str, num))
	{
		*overflow = true;
		return (FLT_MAX);
	}
	if (num == FLT_MAX && !(*overflow))
		*overflow = false;
	return (num);
}

// Handle applying sign and checking underflow
static float apply_sign_and_check(float num, int sign, bool *overflow)
{
	float	result;

	result = num * sign;
	if (result != 0.0F && fabsf(result) < FLT_MIN)
	{
		*overflow = true;
		return (0.0F);
	}
	return (result);
}

// Main function that implements rt_atof with better boundary checks
float rt_atoff(const char *str, bool *overflow)
{
	float	special_val;
	float	num;
	int		i;
	int		sign;

	special_val = 0.0F;
	num = 0.0F;
	sign = 1;
	i = process_sign(str, &sign);
	if (is_special_float(str, &special_val))
		return (special_val);
	num = process_first_part(str, &i, sign, overflow);
	if (*overflow == true)
		return (num);
	num = process_second_part(str, &i, num, sign, overflow);
	if (*overflow == true)
		return (num);
	return (apply_sign_and_check(num, sign, overflow));
}


// float rt_atoff(const char *str, bool *overflow) {
// 	RealType float_type = {
// 		.max_value = FLT_MAX,
// 		.min_value = FLT_MIN,
// 		.epsilon = FLT_EPSILON,
// 		.abs_func = (double (*)(double))fabsf
// 	};
// 	return (float)rt_atoreal(str, overflow, &float_type);
// }

// double rt_atod(const char *str, bool *overflow) {
// 	RealType double_type = {
// 		.max_value = DBL_MAX,
// 		.min_value = DBL_MIN,
// 		.epsilon = DBL_EPSILON,
// 		.abs_func = fabs
// 	};
// 	return rt_atoreal(str, overflow, &double_type);
// }