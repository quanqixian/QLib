.PHONY:help
help:
	@echo ""
	@echo "make          : compile third party libs and unit test"
	@echo "make unitTest : run unit test"
	@echo "make report   : generate code coverage report and test result report"
	@echo ""

all: thirdParty unitTest

thirdParty:googletest

googletest:
	@cd ./thirdparty/googletest/; ./build.sh build

unitTest:
	make -C ./test/

.PHONY:runTest
runTest:
	make -C ./test/ $@

REPORT_DIR=./report
#生成测试通过率和代码覆盖率html报告
.PHONY:report
report: 
	make -C ./test $@
	cp -r ./test/report/  $(REPORT_DIR)
	@echo ""
	@echo  "\033[42;37m    Html report is generated in directory: $(REPORT_DIR)    \033[0m"

.PHONY:clean
clean:
	@cd ./thirdparty/googletest/; ./build.sh clean
	make -C ./test/ clean
	rm -rf $(REPORT_DIR)

