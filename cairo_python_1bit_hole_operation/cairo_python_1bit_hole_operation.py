#!/usr/bin/python

import cairo

surface = cairo.ImageSurface(cairo.FORMAT_A1, 200, 200)
cr = cairo.Context(surface)
cr.set_operator(cairo.OPERATOR_SOURCE)

cr.set_source_rgba(0,0,0,1)
cr.paint()

cr.set_source_rgba(0,0,0,0)
cr.set_line_width(5)
cr.move_to(10,10)
cr.line_to(90,90)
cr.stroke()

surface.write_to_png("test.png")

