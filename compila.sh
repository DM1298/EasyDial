g++-5 -std=c++98 -c phone.cpp
g++-5 -std=c++98 -c call_registry.cpp
g++-5 -std=c++98 -c dialog.cpp
g++-5 -std=c++98 -c easy_dial.cpp
g++-5 -std=c++98 -c driver_easydial.cpp
g++-5 -std=c++98 -o test.e phone.o call_registry.o dialog.o easy_dial.o driver_easydial.o -lesin
