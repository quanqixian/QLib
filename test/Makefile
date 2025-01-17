TARGET=test
TARGET_COV=testCov

CXX=g++
COV=gcov
CXXFLAGS:= -fprofile-arcs -ftest-coverage

GTEST_DIR=$(shell dirname `find ../thirdparty/googletest/install/  -name libgtest.a`)
XSL_FILE_PATH=../thirdparty/gtest2html/gtest2html2.xsl

REPORT_DIR=report
XML_RESULT_FILE_NAME = testResult.xml
HTML_RESULT_FILE_NAME = $(REPORT_DIR)/testResult.html

#
#编译所有单元测试
#
$(TARGET): ./unitTest.cpp ../QLib/*.cpp  ./test*.h
	$(CXX) $^ -o $@ -g -std=c++11\
        -lgtest    \
        -lpthread  \
        -I../QLib/ \
        -I../thirdparty/googletest/install/include/ \
        -L$(GTEST_DIR)

#
#执行单元测试
#
.PHONY:runTest
runTest:$(TARGET)
	./$(TARGET)

#
#生成测试通过率和代码覆盖率html报告
#
.PHONY:report
report: testResult coverage

#
#
#将gtest执行结果生成为html文件
#
.PHONY:testResult
testResult: $(TARGET_COV)
	rm -rf $(REPORT_DIR)
	mkdir $(REPORT_DIR)
	./$(TARGET_COV) --gtest_output=xml:$(XML_RESULT_FILE_NAME) 
	xsltproc    $(XSL_FILE_PATH)    $(XML_RESULT_FILE_NAME) > $(HTML_RESULT_FILE_NAME) 
	@echo  "\033[42;37m    The generated file is: $(HTML_RESULT_FILE_NAME)    \033[0m"

#
#生产代码覆盖率html文件
#
.PHONY:coverage
coverage:$(TARGET_COV)
	./$(TARGET_COV)
	$(COV) ./unitTest.cpp
	lcov -d . -t "QLib Code Coverage"  -o "coverageRaw.info" -b . -c
	lcov  -e coverageRaw.info  *QLib*  -o coverage.info
	genhtml -o $(REPORT_DIR) coverage.info
	rm -f ./*.info
	rm -f ./*.gcno
	rm -f ./*.gcda
	
.PHONY:$(TARGET_COV)
$(TARGET_COV): ./unitTest.cpp ../QLib/*.cpp  ./test*.h
	$(CXX) $^ -o $@ -g -std=c++11\
		$(CXXFLAGS)           \
        -lgtest    \
        -lpthread  \
        -I../QLib/ \
        -I../thirdparty/googletest/install/include/ \
        -L$(GTEST_DIR)

.PHONY:clean
clean:
	rm -rf $(TARGET)
	rm -rf $(TARGET_COV)
	rm -rf $(HTML_RESULT_FILE_NAME)
	rm -rf $(XML_RESULT_FILE_NAME)
	rm -rf $(REPORT_DIR)

