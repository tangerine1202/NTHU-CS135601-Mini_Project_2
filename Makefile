all:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DTEST_LIST -DDOUBLE -std=c++11
lst:
	g++ I2P2_main.cpp src/*.cpp -DTEST_LIST -DDOUBLE -std=c++11
vec:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DDOUBLE -std=c++11
gdb:
	g++ I2P2_main.cpp src/*.cpp -DTEST_VECTOR -DTEST_LIST -DDOUBLE -std=c++11 -g


