#!/usr/bin/python

import cairo

surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, 200, 200)
#surface = cairo.ImageSurface(cairo.FORMAT_A8, 200, 200)
#surface = cairo.SVGSurface('cliff.svg', 100, 100)
cr = cairo.Context(surface)

cr.set_source_rgba(0,0,0,0)
cr.paint()

surface.write_to_png("cliff.png")

cr.set_source_rgba(0,0,0,1)
cr.set_line_width(1)
cr.move_to(10,10)
cr.line_to(10,90)
cr.line_to(90,90)
cr.line_to(90,10)
cr.fill()
#cr.stroke()

cr.set_source_rgba(0,0,0,1)
cr.rectangle(100, 100, 100, 100)
cr.fill()

surface.write_to_png("cliff.png")
#cr.save()




