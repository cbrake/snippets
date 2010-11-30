
#include <QDebug>

#include "myobject.h"

class myobject2: public myobject
{
	Q_OBJECT

public:
	void test()
	{
		qDebug() << "Test 1";
		emit myobject_signal();
	}
};


