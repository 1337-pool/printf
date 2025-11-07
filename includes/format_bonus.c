#include "ft_printf_bonus.h"

/* Apply final width & padding rules and write out. */
int pf_emit(char *raw, t_flags *f)
{
	int len = (int)pf_strlen(raw);
	int width = (f->width >= 0) ? f->width : 0;
	int printed = 0;

	/* Choose pad char:
	   - If numeric and precision is specified, zero flag is ignored.
	   - If left align ('-'), pad with spaces.
	   - Else if zero flag and no dot for numbers, pad with '0'.
	*/
	int is_num = (f->spec=='d'||f->spec=='i'||f->spec=='u'||f->spec=='x'||f->spec=='X');
	char pad = ' ';
	if (!f->minus && f->zero && (!is_num || !f->dot))
		pad = '0';

	if (width > len)
	{
		int need = width - len;
		if (f->minus)
		{
			printed += write(1, raw, len);
			while (need-- > 0) printed += write(1, " ", 1);
			return printed;
		}
		else
		{
			/* Special case: sign or 0x with zero padding → pad after sign/prefix */
			if (pad == '0' && is_num)
			{
				/* Move any leading sign/0x/0X to front, then zeros, then rest */
				int off = 0;
				if (raw[0] == '-' || raw[0] == '+' || raw[0] == ' ')
				{
					printed += write(1, &raw[0], 1);
					off = 1;
					while (need-- > 0) printed += write(1, "0", 1);
					printed += write(1, raw + off, len - off);
					return printed;
				}
				if ((len >= 2) && raw[0]=='0' && (raw[1]=='x' || raw[1]=='X'))
				{
					printed += write(1, raw, 2);
					off = 2;
					while (need-- > 0) printed += write(1, "0", 1);
					printed += write(1, raw + off, len - off);
					return printed;
				}
			}
			/* normal left pad */
			while (need-- > 0) printed += write(1, &pad, 1);
			printed += write(1, raw, len);
			return printed;
		}
	}
	/* no width padding needed */
	printed += write(1, raw, len);
	return printed;
}