/*
 * sstdio.c
 *
 *  Created on: 22-12-2012
 *      Author: Tomek
 */

#include <stdint.h>
#include <stdarg.h>
#include <util/stdio.h>
#include <util/fixp.h>

/* print string */
static int p_s(char *dst, char *src)
{
	int len = 0;

	while (*src) {
		*(dst++) = *(src++);
		len++;
	}

	return len;
}

/* print hex */
static int p_x(char *dst, unsigned int hex)
{
	char digits[] = "0123456789abcdef";
	char temp[8];
	char *ptr = dst;
	int len = 0, rc;

	if (hex == 0) {
		temp[len++] = '0';
	}

	while (hex) {
		temp[len++] = digits[hex & 0xf];
		hex = hex >> 4;
	}
	rc = len;

	while (len--) {
		*(ptr++) = temp[len];
	}

	return rc;
}

/* print dec */
static int p_d(char *dst, int dec)
{
	char digits[] = "0123456789";
	char temp[12];
	char *ptr = dst;
	int len = 0, rc, minus = 0;

	if (dec < 0) {
		minus = 1;
		dec = dec * -1;
	} else if (dec == 0) {
		temp[len++] = '0';
	}

	while (dec) {
		temp[len++] = digits[dec % 10];
		dec = dec / 10;
	}

	if (minus) {
		temp[len++] = '-';
	}

	rc = len;

	while (len--) {
		*(ptr++) = temp[len];
	}

	return rc;
}

/* scan char */
static int s_c(char *in, char *c)
{
	int len = 0;

	/* skip whitespace*/
	while (*in && is_space(*in)) {
		in++;
		len++;
	}
	/* fail */
	if (!*in) {
		return 0;
	}

	/* get char */
	*c = *in;
	len++;

	return len;
}

/* scan dec */
static int s_d(char *in, int *d)
{
	int len = 0;
	int value = 0, sign = 1;
	/* skip whitespace*/
	while (*in && is_space(*in)) {
		in++;
		len++;
	}
	/* fail */
	if (!*in) {
		return 0;
	}
	/* minus sign */
	if (*in == '-') {
		sign = -1;
		in++;
		len++;
	/* plus sign */
	} else if (*in == '+') {
		in++;
		len++;
	}
	/* digit is a must have here */
	if (!is_digit(*in)) {
		return 0;
	}

	/* scan digits */
	while (is_digit(*in)) {
		value = value * 10 + *in - '0';
		in++;
		len++;
	}
	*d = value * sign;
	return len;
}

/* scan hex */
static int s_x(char *in, int *x)
{
	int len = 0;
	int value = 0, sign = 1;
	/* skip whitespace*/
	while (*in && is_space(*in)) {
		in++;
		len++;
	}
	/* fail */
	if (!*in) {
		return 0;
	}
	/* minus sign */
	if (*in == '-') {
		sign = -1;
		in++;
		len++;
	/* plus sign */
	} else if (*in == '+') {
		in++;
		len++;
	}
	/* digit is a must have here */
	if (!is_xdigit(*in)) {
		return 0;
	}

	/* maybe its meaningless '0x'? */
	if (*in == '0') {
		in++;
		len++;
		if (*in && (*in == 'x' || *in == 'X')) {
			in++;
			len++;
		}
	}


	/* scan digits */
	while (is_xdigit(*in)) {
		/* 0-9 */
		if (is_digit(*in)) {
			value = value * 16 + *in - '0';
		} else {
			char _in = *in | 0x20;
			value = value * 16 + (_in + 10) - 'a';
		}
		in++;
		len++;
	}

	*x = value * sign;
	return len;
}

/* scan string */
static int s_s(char *in, char *s)
{
	int len = 0;
	/* skip whitespace */
	while (*in && is_space(*in)) {
		in++;
		len++;
	}
	/* fail */
	if (!*in) {
		return 0;
	}

	/* scan digits */
	while (*in && !is_space(*in)) {
		*(s++) = *(in++);
		len++;
	}
	/* zero-terminate */
	*(s) = 0;

	return len;
}

/* simple sprintf */
int sprintf(char *out, char *fmt, ...)
{
	va_list argp;
	int len = 0, _len;
	char *dst = out, *src = fmt;

	va_start(argp, fmt);

	/* scan formats */
	while (*src) {
		/* normal char */
		if (*src != '%') {
			*(dst++) = *(src++);
			len++;
			continue;
		}
		/* formatting detected */
		src++;
		_len = 0;
		/* start of format */
		switch (*src) {
		/* char */
		case 'c' : {
			int _c = va_arg(argp, int);
			*dst = _c & 0xff;
			_len = 1;
		} break;
		/* hex */
		case 'x' : {
			int _x = va_arg(argp, int);
			_len = p_x(dst, _x);
		} break;
		/* dec */
		case 'd' : {
			int _d = va_arg(argp, int);
			_len = p_d(dst, _d);
		} break;
		/* string */
		case 's' : {
			char *_s = va_arg(argp, char *);
			_len = p_s(dst, _s);
		} break;
		}
		/* next char */
		src++;
		/* update len */
		len += _len;
		/* update dst */
		dst += _len;
	}
	*dst = '\0';
	va_end(argp);

	return len;
}

/* simple sscanf */
int sscanf(char *in, char *fmt, ...)
{
	va_list argp;
	int count = 0, _len;

	va_start(argp, fmt);

	/* scan formats */
	while (*fmt && *in) {
		/* normal char */
		if (*fmt != '%') {
			/* strings differ */
			if (*fmt != *in) {
				va_end(argp);
				return count;
			}
			fmt++;
			in++;
			continue;
		}

		/* formatting detected */
		fmt++;
		_len = 0;
		/* start of format */
		switch (*fmt) {
		/* char */
		case 'c' : {
			/* get char */
			_len = s_c(in, va_arg(argp, char *));
		} break;
		/* dec */
		case 'd' : {
			/* get dec */
			_len = s_d(in, va_arg(argp, int *));
		} break;
		/* hex */
		case 'x' : {
			/* get hex */
			_len = s_x(in, va_arg(argp, int *));
		} break;
		/* string */
		case 's' : {
			/* get string */
			_len = s_s(in, va_arg(argp, char *));
		} break;
		}

		/* conversion failed */
		if (_len == 0) {
			va_end(argp);
			return count;
		}

		in += _len;
		fmt++;
		count++;
	}

	va_end(argp);
	return count;
}

/* check if character is digit */
int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/* check if character is hex digit */
int is_xdigit(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
			(c >= 'A' && c <= 'F'));
}

/* is whitespace */
int is_space(char c)
{
	return (c == '\n' || c == '\t' || c == ' ' || c == '\v' || c == '\f');
}

/* convert string to integer */
int atoi(char *str)
{
	int minus = 0, value = 0, count = 0, mult = 1;
	char *ptr = str;

	/* skip whitespace */
	while (*ptr == ' ' || *ptr == '\n'|| *ptr == '\t') {
		ptr++;
	}

	/* minus sign comes first */
	if (*ptr == '-') {
		minus = 1;
		ptr++;
	/* optional plus sign */
	} else if (*ptr == '+') {
		ptr++;
	}

	/* skip over all digits */
	while (is_digit(*ptr)) {
		count++;
		ptr++;
	}
	/* no digits? */
	if (count == 0) {
		return 0;
	}

	/* parse */
	while (count > 0) {
		value += (*(--ptr) - '0') * mult;
		mult = mult * 10;
		count--;
	}

	if (minus) {
		value = -value;
	}

	return value;
}
