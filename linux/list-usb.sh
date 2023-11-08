for device in /sys/bus/usb/devices/*/; do
	if [ -e "$device/product" ] && [ -e "$device/manufacturer" ]; then
		echo "Product: $(cat $device/product)"
		echo "Manufacturer: $(cat $device/manufacturer)"
		echo
	fi
done
