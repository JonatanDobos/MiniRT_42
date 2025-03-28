/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dbltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 01:27:15 by rjw           #+#    #+#                 */
/*   Updated: 2025/03/12 01:27:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dbltoa.h>

//	Static functions
static uint16_t	dbltoa_convert(double value, t_dbl *strings, bool trim);

uint16_t	dbltoa_buff_prec(t_dbltoa_params dbl)
{
	char		result[MAX_DBL_BUFF];
	t_dbl		strings;
	uint16_t	result_len;

	if (dbl.buff != NULL && dbl.buff_size >= 1)
		dbl.buff[0] = '\0';
	if (dbl.buff == NULL || dbl.buff_size <= 1)
		return (0);
	strings.result = result;
	strings.prec = dbl.precision;
	result_len = dbltoa_convert(dbl.value, &strings, dbl.trim_trailing_zeros);
	if (dbl.buff_size < result_len)
	{
		ft_strlcpy(dbl.buff, result, dbl.buff_size);
		return (--dbl.buff_size);
	}
	return (ft_strlcpy(dbl.buff, result, result_len + 1));
}

static uint16_t	dbltoa_convert(double value, t_dbl *strings, bool trim)
{
	char		numerator[MAX_DBL_STR_LEN + 1];
	char		denominator[MAX_DBL_STR_LEN + 1];
	uint16_t	result_len;
	int16_t		digitexpo;
	bool		is_neg;

	is_neg = true;
	intialize_buff(numerator);
	intialize_buff(denominator);
	strings->s1 = numerator;
	strings->s2 = denominator;
	if (fraction_conversion(value, strings, &is_neg) == false)
		return (ft_strlen(strings->result));
	scientific_notation(numerator, denominator, &digitexpo, value);
	result_len = double_to_string(strings, digitexpo, is_neg);
	if (result_len > 0 && (trim == true || strings->prec == 0))
		return (result_len);
	result_len = process_precision(strings->result, strings->prec);
	if (trim == true && strings->prec > 0 && result_len > 1)
		return (trim_trailing_zeros(strings->result, result_len));
	return (result_len);
}
