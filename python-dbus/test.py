#!/usr/bin/python

import dbus

bus = dbus.SystemBus()

import dbus
bus = dbus.SystemBus()
eth0 = bus.get_object('org.freedesktop.NetworkManager',
                      '/org/freedesktop/NetworkManager/Devices/eth0')
props = eth0.getProperties(dbus_interface='org.freedesktop.NetworkManager.Devices')

# props is a tuple of properties, the first of which is the object path

print props

