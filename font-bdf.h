/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2 -*-
   font-bdf.h --- simple, self-contained code for manipulating BDF fonts.

   Copyright � 2001 Jamie Zawinski <jwz@jwz.org>

   Permission to use, copy, modify, distribute, and sell this software and its
   documentation for any purpose is hereby granted without fee, provided that
   the above copyright notice appear in all copies and that both that
   copyright notice and this permission notice appear in supporting
   documentation.  No representations are made about the suitability of this
   software for any purpose.  It is provided "as is" without express or 
   implied warranty.
 */

#ifndef __FONT_BDF__
#define __FONT_BDF__

struct font_char {
  int lbearing;  /* origin to left edge of raster */
  int width;     /* advance to next char's origin */
  int descent;   /* baseline to bottom edge of raster */
  struct ppm *ppm;
};

struct font {
  char *name;
  int ascent;
  int descent;
  int monochrome_p;
  struct font_char chars[256];
};


/* Filename below may be "-" for stdin. */
extern struct font *read_bdf (const char *filename);

/* Copies the font and the PPMs in it */
struct font * copy_font (struct font *font);
extern void free_font (struct font *font);


/* draw a string with origin XY.
   Alignment 0 means center on the Y axis;
   -1 means flushright; 1 means flushleft.
   Alpha ranges from 0-255.
   Newlines are allowed; tabs are not handled specially.
 */
extern void draw_string (struct font *font, const unsigned char *string,
                         struct ppm *into, int x, int y,
                         int alignment,
                         unsigned long fg, unsigned long bg,
                         int alpha);

/* Scale font bitmaps with scale_ppm(). */
extern void scale_font (struct font *font, double scale);

/* Add a blurry halo around the font: e.g., so that the same text will
   be visible on light or dark backgrounds.
 */
extern void halo_font (struct font *font, int radius);

/* Write debugging info on stderr. */
extern void dump_font (struct font *font, int which_char);

#endif /* __FONT_BDF__ */
