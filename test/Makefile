TARGET=test
$(TARGET): ./unitTest.cpp ../QLib/Object.cpp  ./test*.h
	g++ $^ -o $@ -g\
        -lgtest    \
		-lpthread  \
		-I../QLib/ \
		-I../thirdparty/googletest/install/include/ \
		-L../thirdparty/googletest/install/lib/

.PHONY:runTest
runTest:
	./$(TARGET)

.PHONY:clean
clean:
	rm -rf $(TARGET)
