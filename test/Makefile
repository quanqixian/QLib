TARGET=test
GTEST_DIR=$(shell dirname `find ../thirdparty/googletest/install/  -name libgtest.a`)

$(TARGET): ./unitTest.cpp ../QLib/*.cpp  ./test*.h
	g++ $^ -o $@ -g -std=c++11\
        -lgtest    \
		-lpthread  \
		-I../QLib/ \
		-I../thirdparty/googletest/install/include/ \
		-L$(GTEST_DIR)

.PHONY:runTest
runTest:
	./$(TARGET)

.PHONY:clean
clean:
	rm -rf $(TARGET)
