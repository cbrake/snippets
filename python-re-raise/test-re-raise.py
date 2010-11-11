#!/usr/bin/python

try:
    print 'hi'

except:
    print 'we had an exception, re raise'
    raise

else:
    try:
        # generate an exception
        cliff = asdfasdfasdf
    except:
        print 'we had an exception, re raise'
        raise

finally:
    print 'finally block'


# the following works as expected, the exception gets re-raised

try:
    # generate an exception
    cliff = asdfasdfasdf

except:
    print 'we had an exception, re raise'
    raise

finally:
    print 'finally block'



