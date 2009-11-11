#!/usr/bin/python

import dbus

system_bus = dbus.SystemBus()

# create proxy
backlight = system_bus.get_object('org.freedesktop.PowerManagement', '/org/freedesktop/PowerManagement/Backlight')

backlight_iface = dbus.Interface(backlight, dbus_interface='org.freedesktop.PowerManagement')
props = backlight_iface.getProperties()

print props








