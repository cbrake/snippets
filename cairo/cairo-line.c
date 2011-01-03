#include <cairo.h>

static void generate(int antialias, char * filename)
{
	cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_A8, 20, 20);

	cairo_t * cr =  cairo_create(surface);

	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	if (!antialias)
		cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);

	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_set_line_width(cr, 1);

	cairo_move_to(cr, 5, 5);
	cairo_line_to(cr, 5, 10);
	cairo_stroke(cr);

	cairo_move_to(cr, 0, 0);
	cairo_line_to(cr, 5, 0);
	cairo_stroke(cr);

	cairo_move_to(cr, 10, 1);
	cairo_line_to(cr, 15, 1);
	cairo_stroke(cr);

	cairo_set_line_width(cr, 2);
	cairo_move_to(cr, 10, 10);
	cairo_line_to(cr, 15, 10);
	cairo_stroke(cr);

	cairo_move_to(cr, 15, 15);
	cairo_line_to(cr, 20, 20);
	cairo_stroke(cr);

	cairo_move_to(cr, 5, 15);
	cairo_line_to(cr, 0, 20);
	cairo_stroke(cr);

	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, 15, 5);
	cairo_line_to(cr, 20, 0);
	cairo_stroke(cr);

	cairo_surface_write_to_png(surface, filename);
}

int main()
{
	generate(0, "cario-line.png");
	generate(1, "cario-line-antialias.png");
}


