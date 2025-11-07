#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/* ============= Flags =============
   '-' : left align
   '0' : zero pad (ignored if '-' or precision for numbers)
   '.' : precision
   width : field min width
   '#' : 0x / 0X for hex (non-zero)
   '+' : explicit plus for positive
   ' ' : leading space if no plus
*/
typedef struct s_flags
{
	int   minus;
	int   zero;
	int   dot;
	int   width;       // -1 means not set
	int   precision;   // -1 means not set
	int   hash;
	int   plus;
	int   space;
	char  spec;        // conversion specifier
}	t_flags;

/* ========= Public entry ========= */
int   ft_printf(const char *fmt, ...);

/* ========= Parse stage ========== */
const char *pf_parse(const char *p, t_flags *f, va_list ap);

/* ======== Convert stage ========= */
char *pf_conv(va_list ap, t_flags *f);     // returns freshly malloc'ed string (raw, before width)
char *pf_conv_char(int c);
char *pf_conv_str(const char *s, t_flags *f);
char *pf_conv_ptr(void *p);
char *pf_conv_signed(long n, t_flags *f);
char *pf_conv_unsigned(unsigned long n, int base, int upper, t_flags *f);

/* ======== Format stage ========= */
int   pf_emit(char *raw, t_flags *f);      // applies width/padding & writes; returns printed count

/* ============ Utils ============= */
size_t  pf_strlen(const char *s);
char   *pf_strdup(const char *s);
char   *pf_itoa_signed(long n);
char   *pf_utoa_base(unsigned long n, int base, int upper);
char   *pf_pad_left(char *s, int total, char pad);   // returns new malloc'ed padded string; frees s
char   *pf_pad_right(char *s, int total, char pad);  // returns new malloc'ed padded string; frees s
char   *pf_strjoin_free(char *a, char *b);           // join & free both
int     pf_write(const char *s);
int     pf_max(int a, int b);

/* ====== Local helpers (fmt) ===== */
int   pf_isdigit(int c);

#endif