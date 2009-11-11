#!/usr/bin/python

import cairo

#surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 200, 200)
surface = cairo.ImageSurface(cairo.FORMAT_A8, 200, 200)
#surface = cairo.SVGSurface('cliff.svg', 100, 100)
cr = cairo.Context(surface)

# causes alpha channels to not be added
cr.set_operator(cairo.OPERATOR_SOURCE)

cr.set_source_rgba(0,0,0,0)
cr.paint()

cr.set_source_rgba(0,0,0,.5)
cr.set_line_width(1)
cr.move_to(10,10)
cr.line_to(10,90)
cr.line_to(90,90)
cr.line_to(90,10)
cr.fill()

cr.set_source_rgba(0,0,0,.8)
cr.rectangle(100, 100, 100, 100)
cr.fill()

cr.set_source_rgba(0,0,0,.7)
cr.rectangle(20,20,60,60)
cr.fill()

cr.set_source_rgba(1,1,1,.3)
cr.rectangle(30,30,40,40)
cr.fill()

surface.write_to_png("cliff-1bit.png")

#cr.save()




