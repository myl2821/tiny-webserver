#Tiny

Tiny is a small webserver which is designed for easy deployment.

Though, this stupid server is still under developing.

-------------
##usage

To compile, just type
	
	make
	
To run this server, run

	./tiny <The directory of you webRoot> <listening port>
	
##examples
	./tiny . 55555

Static content test:
	
	http://127.0.0.1:55555/test/static.html

cgi-bin test:

	http://127.0.0.1:55555/cgi-bin/adder?2&3