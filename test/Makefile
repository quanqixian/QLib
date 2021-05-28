TARGET=test

GTEST_DIR=$(shell dirname `find ../thirdparty/googletest/install/  -name libgtest.a`)
XSL_FILE_PATH=../thirdparty/gtest2html/gtest2html2.xsl

XML_RESULT_FILE_NAME = testResult.xml
HTML_RESULT_FILE_NAME = testResult.html

$(TARGET): ./unitTest.cpp ../QLib/*.cpp  ./test*.h
	g++ $^ -o $@ -g -std=c++11\
        -lgtest    \
        -lpthread  \
        -I../QLib/ \
        -I../thirdparty/googletest/install/include/ \
        -L$(GTEST_DIR)

.PHONY:runTest
runTest:$(TARGET)
	./$(TARGET)

#将gtest执行结果生成为html文件
.PHONY:html
html: $(TARGET)
	./$(TARGET) --gtest_output=xml:$(XML_RESULT_FILE_NAME) 
	xsltproc    $(XSL_FILE_PATH)    $(XML_RESULT_FILE_NAME) > $(HTML_RESULT_FILE_NAME) 
	@echo  "\033[42;37m    The generated file is: $(HTML_RESULT_FILE_NAME)    \033[0m"

.PHONY:clean
clean:
	rm -rf $(TARGET)
	rm -rf $(HTML_RESULT_FILE_NAME)
	rm -rf $(XML_RESULT_FILE_NAME)

