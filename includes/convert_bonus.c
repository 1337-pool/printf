#include "ft_printf_bonus.h"

/* apply numeric precision: pad with zeros on the left to reach precision length.
   if value == "0" and precision == 0 => empty string "" (for d i u x X) */
static char *apply_num_precision(char *digits, t_flags *f, int is_zero)
{
	if (!f->dot || f->precision < 0)
		return pf_strdup(digits);
	if (is_zero && f->precision == 0)
		return pf_strdup("");
	int len = (int)pf_strlen(digits);
	if (len >= f->precision)
		return pf_strdup(digits);
	int need = f->precision - len;
	char *pad = (char *)malloc(need + 1);
	if (!pad) return NULL;
	for (int i = 0; i < need; ++i) pad[i] = '0';
	pad[need] = '\0';
	char *res = pf_strjoin_free(pad, pf_strdup(digits));
	return res;
}

/* add sign/space/plus for signed */
static char *apply_sign(char *num, t_flags *f, long n)
{
	if (n < 0)
	{
		/* num currently has digits only (positive form).
		   Prepend '-' */
		char *neg = pf_strjoin_free(pf_strdup("-"), num);
		return neg;
	}
	if (f->plus)
		return pf_strjoin_free(pf_strdup("+"), num);
	if (f->space)
		return pf_strjoin_free(pf_strdup(" "), num);
	return num;
}

/* add 0x / 0X for hex if needed (non-zero or pointer flows) */
static char *apply_hash_hex(char *num, t_flags *f, int upper, int is_zero)
{
	if (!f->hash || is_zero)
		return num;
	if (upper)
		return pf_strjoin_free(pf_strdup("0X"), num);
	return pf_strjoin_free(pf_strdup("0x"), num);
}

/* -------- dispatch -------- */

char *pf_conv_char(int c)
{
	char *s = (char *)malloc(2);
	if (!s) return NULL;
	s[0] = (char)c;
	s[1] = '\0';
	return s;
}

char *pf_conv_str(const char *s, t_flags *f)
{
	if (!s) s = "(null)";
	/* precision on strings: max chars */
	size_t len = pf_strlen(s);
	size_t out = len;
	if (f->dot && f->precision >= 0 && (size_t)f->precision < len)
		out = (size_t)f->precision;
	char *res = (char *)malloc(out + 1);
	if (!res) return NULL;
	for (size_t i = 0; i < out; ++i) res[i] = s[i];
	res[out] = '\0';
	return res;
}

char *pf_conv_ptr(void *p)
{
	uintptr_t v = (uintptr_t)p;
	char *digits = pf_utoa_base((unsigned long)v, 16, 0);
	if (!digits) return NULL;
	/* even for 0, printf prints "0x0" */
	char *pref = pf_strdup("0x");
	if (!pref) { free(digits); return NULL; }
	char *res = pf_strjoin_free(pref, digits);
	return res;
}

char *pf_conv_signed(long n, t_flags *f)
{
	unsigned long un = (n < 0) ? (unsigned long)(-(long)n) : (unsigned long)n;
	char *digits = pf_utoa_base(un, 10, 0);
	if (!digits) return NULL;

	int is_zero = (un == 0);
	char *prec = apply_num_precision(digits, f, is_zero);
	free(digits);
	if (!prec) return NULL;

	char *with_sign = apply_sign(prec, f, n); /* may insert '-', '+', ' ' */
	return with_sign;
}

char *pf_conv_unsigned(unsigned long n, int base, int upper, t_flags *f)
{
	char *digits = pf_utoa_base(n, base, upper);
	if (!digits) return NULL;

	int is_zero = (n == 0);
	char *prec = apply_num_precision(digits, f, is_zero);
	free(digits);
	if (!prec) return NULL;

	if ((base == 16) && f->hash && !is_zero)
	{
		char *hexed = apply_hash_hex(prec, f, upper, is_zero);
		return hexed;
	}
	return prec;
}

char *pf_conv(va_list ap, t_flags *f)
{
	if (f->spec == 'c')
		return pf_conv_char(va_arg(ap, int));
	if (f->spec == 's')
		return pf_conv_str(va_arg(ap, const char *), f);
	if (f->spec == 'p')
		return pf_conv_ptr(va_arg(ap, void *));
	if (f->spec == 'd' || f->spec == 'i')
		return pf_conv_signed((long)va_arg(ap, int), f);
	if (f->spec == 'u')
		return pf_conv_unsigned((unsigned long)va_arg(ap, unsigned int), 10, 0, f);
	if (f->spec == 'x')
		return pf_conv_unsigned((unsigned long)va_arg(ap, unsigned int), 16, 0, f);
	if (f->spec == 'X')
		return pf_conv_unsigned((unsigned long)va_arg(ap, unsigned int), 16, 1, f);
	if (f->spec == '%')
		return pf_conv_char('%');
	return pf_strdup(""); /* safety */
}