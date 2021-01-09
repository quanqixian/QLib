TARGET=test
$(TARGET): ./unitTest.cpp ../QLib/Object.cpp
	g++ $^ -o $@   \
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
