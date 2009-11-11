/*
 * to compile: 
 */

#include <stdio.h>
#include <cairo.h>


int main()
{

	cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 200, 200);

	cairo_t * cr = cairo_create(surface);
	cairo_set_source_rgba(cr, 1, 0, 0, 1);
	cairo_paint(cr);
	cairo_destroy(cr);

	cairo_surface_write_to_png(surface, "test.png");

	unsigned int * buf = (unsigned int *)cairo_image_surface_get_data(surface);

	printf("First word = 0x%x\n", buf[0]);

	return 0;
}
