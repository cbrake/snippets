#include <cairo.h>

void main()
{
	cairo_surface_t * surface;

	cairo_t * cr;

	// this works
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
	cr = cairo_create(surface);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_rectangle(cr, 10, 10, 80, 80);
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
	cairo_fill(cr);
	cairo_rectangle(cr, 20, 20, 60, 60);
	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_fill(cr);
	cairo_surface_write_to_png(surface, "32bit.png");

	// this works
	surface = cairo_image_surface_create(CAIRO_FORMAT_A8, 100, 100);
	cr = cairo_create(surface);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_rectangle(cr, 10, 10, 80, 80);
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
	cairo_fill(cr);
	cairo_rectangle(cr, 20, 20, 60, 60);
	cairo_set_source_rgba(cr, 1, 1, 1, 0);
	// this also works
	cairo_set_source_rgba(cr, 0, 0, 0, 0);
	cairo_fill(cr);
	cairo_surface_write_to_png(surface, "8bit.png");

	// this does not, there is only a single white rectangle, the black
	// rectangle does not paint
	surface = cairo_image_surface_create(CAIRO_FORMAT_A1, 100, 100);
	cr = cairo_create(surface);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_rectangle(cr, 10, 10, 80, 80);
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
	cairo_fill(cr);
	cairo_rectangle(cr, 20, 20, 60, 60);
	cairo_set_source_rgba(cr, 0, 0, 0, 0);
	cairo_fill(cr);
	cairo_surface_write_to_png(surface, "1bit.png");
}

