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
	int i = 0;
	*sign = 1;
	
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	
	if (str[i] == '-') {
		*sign = -1;
		++i;
	} else if (str[i] == '+') {
		++i;
	}
	
	return i;
}

// Process integer part of the number
float process_integer(const char *str, int *idx, bool *overflow)
{
	float num = 0.0F;
	int i = *idx;
	
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		// Check if adding another digit would overflow
		if (num > (FLT_MAX - (str[i] - '0')) / 10.0F)
		{
			*overflow = true;
			*idx = i;
			return FLT_MAX;
		}
		
		num = (num * 10.0F) + (str[i++] - '0');
	}
	
	*idx = i;
	return num;
}

// Process fractional part
float process_fraction(const char *str, int *idx, float num, bool *overflow)
{
	int i = *idx;
	float scale = 0.1F;
	
	if (str[i] == '.')
	{
		++i;
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		{
			float digit_value = (str[i++] - '0') * scale;
			
			if (num > FLT_MAX - digit_value)
			{
				*overflow = true;
				*idx = i;
				return FLT_MAX;
			}
			
			num += digit_value;
			scale *= 0.1F;
		}
	}
	
	*idx = i;
	return num;
}
#include <limits.h>
// Process exponent part with correct overflow and underflow checks
float process_exponent(const char *str, int *idx, float num, bool *overflow)
{
	int i = *idx;
	
	if ((str[i] == 'e' || str[i] == 'E') && str[i + 1] != '\0')
	{
		int exp_sign = 1;
		int exp = 0;
		++i;
		
		if (str[i] == '-') {
			exp_sign = -1;
			++i;
		} else if (str[i] == '+') {
			++i;
		}
		
		// Parse the exponent value
		while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9')) {
			// Check for exponent value overflow
			if (exp > (INT_MAX - (str[i] - '0')) / 10) {
				*overflow = true;
				*idx = i;
				// If huge positive exponent -> overflow
				// If huge negative exponent -> underflow to 0
				return (exp_sign > 0) ? FLT_MAX : 0.0F;
			}
			exp = exp * 10 + (str[i++] - '0');
		}
		
		// Apply sign to exponent
		exp *= exp_sign;
		
		// Shortcut for extreme exponents to avoid unnecessary loops
		if (exp_sign > 0 && exp > 38) {
			// Anything with exponent > 38 will overflow
			*overflow = true;
			*idx = i;
			return FLT_MAX;
		} else if (exp_sign < 0 && exp < -38) {
			// Anything with exponent < -38 will underflow
			*overflow = true;
			*idx = i;
			return 0.0F;  // Return 0 for underflow
		}
		
		// Apply exponent
		if (exp > 0) {
			// For positive exponents (multiply by 10^exp)
			for (int j = 0; j < exp; j++) {
				// Check if multiplying by 10 would cause overflow
				if (num > FLT_MAX / 10.0F) {
					*overflow = true;
					*idx = i;
					return FLT_MAX;
				}
				num *= 10.0F;
			}
		} else if (exp < 0) {
			// For negative exponents (divide by 10^|exp|)
			for (int j = 0; j > exp; j--) {
				num *= 0.1F;
				// Check for underflow after each division
				if (num != 0.0F && fabsf(num) < FLT_MIN) {
					*overflow = true;
					*idx = i;
					return 0.0F;  // Return 0 for underflow
				}
			}
		}
	}
	
	*idx = i;
	return num;
}

#include <strings.h>
// Main function that implements rt_atof with better boundary checks
float rt_atoff(const char *str, bool *overflow)
{
	int i = 0;
	int sign = 1;
	float num = 0.0F;
	*overflow = false;
	
	// Process the sign and get the starting index
	i = process_sign(str, &sign);

	// Handle special cases: inf, -inf, nan, -nan
	if (strcasecmp(str, "inf") == 0 || strcasecmp(str, "infinity") == 0) {
		return INFINITY;
	}
	if (strcasecmp(str, "-inf") == 0 || strcasecmp(str, "-infinity") == 0) {
		return -INFINITY;
	}
	if (strcasecmp(str, "nan") == 0 || strcasecmp(str, "-nan") == 0) {
		return NAN;
	}

	// Parse integer part
	num = process_integer(str, &i, overflow);
	if (*overflow)
		return (sign > 0 ? FLT_MAX : -FLT_MAX);
	
	// Parse fractional part
	num = process_fraction(str, &i, num, overflow);
	if (*overflow)
		return (sign > 0 ? FLT_MAX : -FLT_MAX);
	
	// Parse exponent part
	num = process_exponent(str, &i, num, overflow);
	if (*overflow) {
		// If process_exponent returned 0, it's an underflow
		if (num == 0.0F)
			return 0.0F;
		// Otherwise, it's an overflow
		return (sign > 0 ? FLT_MAX : -FLT_MAX);
	}
	
	// Check if the number is exactly at or very near FLT_MAX
	// We use a small delta to detect values extremely close to FLT_MAX
	if (num > FLT_MAX) {
		*overflow = true;
		return FLT_MAX;
	}
	// Replace the FLT_MAX edge case check with this:
	if (num > FLT_MAX * 0.999999f) {
		// If we're within 0.0001% of FLT_MAX, we need to carefully check
		
		// Parse the exponent value from the string to make a decision
		// This is a simple check: if the original string has an exponent that would
		// push it above what float can represent, mark as overflow
		
		// Find the exponent part if it exists
		int exp_val = 0;
		bool found_exp = false;
		
		for (int j = 0; str[j] != '\0'; j++) {
			if (str[j] == 'e' || str[j] == 'E') {
				found_exp = true;
				int exp_idx = j + 1;
				int exp_sign = 1;
				
				// Handle exponent sign
				if (str[exp_idx] == '-') {
					exp_sign = -1;
					exp_idx++;
				} else if (str[exp_idx] == '+') {
					exp_idx++;
				}
				
				// Parse exponent digits
				while (str[exp_idx] != '\0' && str[exp_idx] >= '0' && str[exp_idx] <= '9') {
					exp_val = exp_val * 10 + (str[exp_idx++] - '0');
				}
				
				exp_val *= exp_sign;
				break;
			}
		}
		
		// If exponent is 38 or greater, we need to check the mantissa
		if (found_exp && exp_val >= 38) {
			// Extract the mantissa (the digits before the exponent)
			float mantissa = 0.0f;
			int mantissa_idx = 0;
			
			// Skip sign and whitespace
			while (str[mantissa_idx] == ' ' || str[mantissa_idx] == '\t')
				mantissa_idx++;
			
			if (str[mantissa_idx] == '-' || str[mantissa_idx] == '+')
				mantissa_idx++;
			
			// Parse integer part
			while (str[mantissa_idx] != '\0' && str[mantissa_idx] >= '0' && str[mantissa_idx] <= '9') {
				mantissa = mantissa * 10.0f + (str[mantissa_idx++] - '0');
			}
			
			// Parse fractional part if present
			if (str[mantissa_idx] == '.') {
				float frac_scale = 0.1f;
				mantissa_idx++;
				
				while (str[mantissa_idx] != '\0' && str[mantissa_idx] >= '0' && str[mantissa_idx] <= '9') {
					mantissa += (str[mantissa_idx++] - '0') * frac_scale;
					frac_scale *= 0.1f;
				}
			}
			
			// Check if the combination of mantissa and exponent would overflow
			// For example, 3.4e38 is close to FLT_MAX but not over
			// 3.5e38 would be over
			if (exp_val > 38 || (exp_val == 38 && mantissa > 3.4f)) {
				*overflow = true;
				return FLT_MAX;
			}
		}
		
		// If num is exactly FLT_MAX, and we've calculated it through our algorithm
		// (not just set it as a result of overflow detection), it's valid
		if (num == FLT_MAX && !(*overflow)) {
			*overflow = false;
		}
	}
	// Apply sign
	num *= sign;
	
	// Check for underflow after applying sign
	if (num != 0.0F && fabsf(num) < FLT_MIN) {
		*overflow = true;
		return 0.0F;
	}
	return num;
}