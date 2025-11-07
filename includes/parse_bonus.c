#include "ft_printf_bonus.h"

/* width and precision can be '*' (take from va_arg(int)) */
static const char *pf_parse_number_or_star(const char *p, int *out, va_list ap)
{
	int val = 0;
	if (*p == '*')
	{
		val = va_arg(ap, int);
		p++;
	}
	else
	{
		while (pf_isdigit(*p))
		{
			val = val * 10 + (*p - '0');
			p++;
		}
	}
	*out = val;
	return p;
}

const char *pf_parse(const char *p, t_flags *f, va_list ap)
{
	/* 1) flags */
	int cont = 1;
	while (cont && *p)
	{
		if (*p == '-') f->minus = 1;
		else if (*p == '0') f->zero = 1;
		else if (*p == '#') f->hash = 1;
		else if (*p == '+') f->plus = 1;
		else if (*p == ' ') f->space = 1;
		else cont = 0;
		if (cont) p++;
	}

	/* 2) width */
	if (*p == '*' || pf_isdigit(*p))
	{
		p = pf_parse_number_or_star(p, &f->width, ap);
		if (f->width < 0) { f->minus = 1; f->width = -f->width; } // printf rule
	}

	/* 3) precision */
	if (*p == '.')
	{
		f->dot = 1;
		p++;
		f->precision = 0;
		if (*p == '*' || pf_isdigit(*p))
		{
			p = pf_parse_number_or_star(p, &f->precision, ap);
			if (f->precision < 0) { f->dot = 0; f->precision = -1; } // negative precision: ignored
		}
	}

	/* 4) specifier */
	if (*p == 'c' || *p == 's' || *p == 'p' ||
	    *p == 'd' || *p == 'i' || *p == 'u' ||
	    *p == 'x' || *p == 'X' || *p == '%')
	{
		f->spec = *p;
	}
	else
	{
		/* unknown spec: we’ll treat it like literal '%' upstream */
		f->spec = 0;
		p--; /* step back so ft_printf increments lands on the unknown char */
	}
	return p;
}