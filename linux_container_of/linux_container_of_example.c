/* test code to illustrate use of Linux kernel container_of macro
 *
 * Copyright (c) 2008 Cliff Brake, BEC Systems LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This program illustrates how the container_of macro works.
 * The container of macro is very useful in multi layered
 * software systems where you have progressivly more detailed
 * software layers.  Below is an example of a bus layer,
 * and then a device layer where a number of different
 * devices might register with the bus.
 * The device registers itself with the bus subsystem, and
 * then the bus subsystem makes a callback into the device.
 * Normally if there are multiple devices registered, the 
 * bus subsystem must store and pass a device structure
 * when making callbacks.  With the container_of macro, this is
 * no longer necessary, and the bus subsystem only has to
 * know about one generic device structure, and does not need visibility
 * into lots of different device structures, or do tricks
 * by casting void pointers, etc.  With the container_of macro
 * we can backcast from the generic data structure, to the containing
 * datastructure.  This forces good separation of code in that
 * that bus layer cannot modifiy data structures that are specific
 * to the device layer.
 *
 */


/**
 * (from Linux kernel source)
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)


/*==========================================================
 * BUS layer code
 *==========================================================*/

/* generic bus device structure */
struct bus_device 
{
	int general_device_param_a;
	int general_device_param_b;
	void (*device_callback)(struct bus_device * bd);
};

/* the following is a global list of
 * devices that have registered with the 
 * bus subsystem.  Normally this would
 * be something like a dynamic linked list.
 */
struct bus_device * bd_list[5];

/* function to register a device with the bus */
void register_with_bus(struct bus_device * bd)
{
	/* since this example only deals with one
	 * device, will put it in slot 0
	 */

	bd_list[0] = bd;
}

void start_bus()
{
	int i;
	struct bus_device * bd;

	/* make callbacks to all devices on bus */
	for (i=0;i<sizeof(bd_list)/sizeof(bd_list[0]);i++) {
		bd = bd_list[i];
		if (!bd) continue;
		/* call device callback with generic
		 * bus device structure
		 */
		bd->device_callback(bd);
	}
}

/*==========================================================
 * device X specific code
 * this would normally be in a different module
 *==========================================================*/

/* structure that holds device X specific stuff, as well as
 * generic bus_device structure
 */
struct device_x
{
	int device_x_specific_param_a;
	int device_x_specific_param_b;
	struct bus_device bd;
};

void device_x_callback(struct bus_device * bd)
{
	/* if we know the structure type that contains the bus_device structure,
	 * we can extract a pointer to the containing structure using the container_of
	 * macro
	 */

	/*                                   ptr       type       member  */
	struct device_x * devx = container_of(bd, struct device_x, bd);

	/* the above statement expands to
	 * struct device_x * devx = (
	 * { 
	 *   const typeof( ((struct device_x *)0)->bd ) *__mptr = (bd); 
	 *   (struct device_x *)( (char *)__mptr - ((size_t) &((struct device_x *)0)->bd) );
	 * }
	 * );
	 */  

	printf("device_x_callback called!, device_x_specific_param_a = %i\n", 
			devx->device_x_specific_param_a);
}

void device_x_init()
{
	/* dynamically allocate structures */
	struct device_x * devx = malloc(sizeof(*devx));
	memset(devx, 0, sizeof(*devx));

	/* set a parameter in the device_x structure so 
	 * we can test for this in the callback
	 */
	devx->device_x_specific_param_a = 1001;

	/* set up callback function */
	devx->bd.device_callback = device_x_callback;

	/* we register the generic bus device structure
	 * as the bus layer does not need to know
	 * about the device_x stucture.  Note, the 
	 * devx structure is not stored anywhere, yet
	 * its location is being preserved without
	 * specifically passing it to the bus 
	 * layer.
	 */
	register_with_bus(&devx->bd);
}


int main()
{

	/* test the above system */

	/* first, initialize device_x */
	device_x_init();

	/* now, start the bus.  This should make
	 * a callback into the device_x
	 */
	start_bus();
}

/* when run, this program returns:
 * device_x_callback called!, device_x_specific_param_a = 1001
 */

