How to install

Download zip from 
https://github.com/Somebody-From-Somewhere/Kolobok-wars

If you don`t have  qt libraries, execute in terminal next comands:
1. sudo apt install qtchooser
2. sudo apt install qt5-default

If you don`t have make utility, execute:
3. sudo apt install make

Installation
Firstly go to common dir and build libcommon.so with
1. qmake
2. make

After that go to the server and client dirs, execute same tips as for common. Before running server and client export external library into client and server dirs
1. export LD_LIBRARY_PATH=./../common

Now you are ready to play

