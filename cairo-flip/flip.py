#!/usr/bin/python

import cairo

s = cairo.ImageSurface.create_from_png("test.png")

pat = cairo.SurfacePattern(s)

# one way to flip an image on the Y axis
#m = cairo.Matrix(1, 0, 0, -1, 0, s.get_height())

# another way to flip an image on the Y axis
# the order of the translate and scale are important
m = cairo.Matrix()
m.translate(0, s.get_height())
m.scale(1, -1)

pat.set_matrix(m)

dest = cairo.ImageSurface(cairo.FORMAT_ARGB32, s.get_width(), s.get_height())
cr = cairo.Context(dest)

cr.set_source(pat)
cr.paint()

dest.write_to_png("test_modified.png")

