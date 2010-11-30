
#include <QDebug>
#include <QObject>

#include "myobject2.h"

main()
{
	qDebug() << "qobject-inherit";

	myobject2 myo2;
	myo2.test();
}


