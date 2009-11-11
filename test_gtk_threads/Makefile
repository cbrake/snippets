
# tweak the following for your build setup
OE_TMP_DIR=/build/pp/eSight/DisplayUnit/Software/oe2/build/angstrom-2007.1/tmp

PKG_CONFIG_PATH_=${OE_TMP_DIR}/staging/arm-angstrom-linux-gnueabi/lib/pkgconfig
PATH_=${OE_TMP_DIR}/cross/bin

all:
	PKG_CONFIG_PATH=${PKG_CONFIG_PATH_}; PATH=${PATH_}:$$PATH; arm-angstrom-linux-gnueabi-gcc -o test-gtk-threads test-gtk-threads.c `pkg-config --cflags --libs gtk+-2.0 gthread-2.0`
