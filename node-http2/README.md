(adapted from https://github.com/molnarg/node-http2/tree/master/example)

Node http2 example of a persistent connection, and 
the server sends a count to the client every
second.  This is to demonstrate using http2 to 
create a persistent connection to a server, and have
the server push data to the client.

to use:

  npm install

In two different terminals run:

* node server.js
* node client.js

You should see the client printing out an incrementing count every 1s:

    node client.js
    Receiving pushed resource: push%20data
    { count: 0 }
    { count: 1 }
    { count: 2 }
    { count: 3 }
    { count: 4 }
    { count: 5 }
    { count: 6 }
    { count: 7 }
    { count: 8 }
    ....



