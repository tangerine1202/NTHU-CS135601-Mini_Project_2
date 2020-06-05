all:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DTEST_LIST -DDOUBLE -std=c++11
lst:
	g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11
lst gdb:
	g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11 -g
vec:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11
vec gdb:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11 -g
gdb:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DTEST_LIST -DDOUBLE -std=c++11 -g


