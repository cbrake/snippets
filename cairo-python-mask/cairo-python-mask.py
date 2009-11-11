#!/usr/bin/python

import cairo

surface = cairo.ImageSurface(cairo.FORMAT_RGB24, 200, 200)

source = cairo.ImageSurface(cairo.FORMAT_RGB24, 200, 200)

mask = cairo.ImageSurface(cairo.FORMAT_A1, 200, 200)

# create mask
cr = cairo.Context(mask)
cr.set_operator(cairo.OPERATOR_SOURCE)

cr.set_source_rgba(0,0,0,1)
cr.paint()

cr.set_source_rgba(0,0,0,0)
cr.move_to(90,90)
cr.line_to(110,90)
cr.line_to(110,110)
cr.line_to(90,110)
cr.line_to(90,90)
cr.fill()

mask.write_to_png("mask.png")

# create a source image
cr = cairo.Context(source)
cr.set_operator(cairo.OPERATOR_SOURCE)
cr.set_source_rgb(1,0,0)
cr.move_to(50,50)
cr.line_to(150,50)
cr.line_to(150,150)
cr.line_to(50,150)
cr.line_to(50,50)
cr.fill()
source.write_to_png("source.png")

# create final surface image
cr = cairo.Context(surface)
cr.set_operator(cairo.OPERATOR_SOURCE)

# create a small green block and then write over with a larger block
cr.set_source_rgb(0,1,0)
cr.move_to(50,50)
cr.line_to(150,50)
cr.line_to(150,150)
cr.line_to(50,150)
cr.line_to(50,50)
cr.fill()

# apply source image through mask
cr.set_source_surface(source)
cr.mask_surface(mask)

surface.write_to_png("surface.png")

# now try the same thing with a greyscale (alpha) surface

surface = cairo.ImageSurface(cairo.FORMAT_A8, 200, 200)

source = cairo.ImageSurface(cairo.FORMAT_A8, 200, 200)

# create a source image
cr = cairo.Context(source)
cr.set_operator(cairo.OPERATOR_SOURCE)
cr.set_source_rgba(0,0,0,0.5)
cr.move_to(50,50)
cr.line_to(150,50)
cr.line_to(150,150)
cr.line_to(50,150)
cr.line_to(50,50)
cr.fill()
source.write_to_png("source_8.png")

# create final surface image
cr = cairo.Context(surface)
cr.set_operator(cairo.OPERATOR_SOURCE)

# create a small green block and then write over with a larger block
cr.set_source_rgba(0,0,0,0.2)
cr.move_to(50,50)
cr.line_to(150,50)
cr.line_to(150,150)
cr.line_to(50,150)
cr.line_to(50,50)
cr.fill()

# apply source image through mask
cr.set_source_surface(source)
cr.mask_surface(mask)

surface.write_to_png("surface_8.png")


