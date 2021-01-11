TARGET=test
$(TARGET): ./unitTest.cpp ../QLib/Object.cpp  ./test*.h
	g++ $^ -o $@ -g -std=c++11\
        -lgtest    \
		-lpthread  \
		-I../QLib/ \
		-I../thirdparty/googletest/install/include/ \
		-L../thirdparty/googletest/install/lib/     \
		-L../thirdparty/googletest/install/lib64/

.PHONY:runTest
runTest:
	./$(TARGET)

.PHONY:clean
clean:
	rm -rf $(TARGET)
