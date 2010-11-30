
#include <QObject>


class myobject: public QObject
{
	Q_OBJECT

public:
	virtual void test() =0;

signals:
	void myobject_signal();
};

