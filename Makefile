all: thirdParty unitTest

thirdParty:googletest

googletest:
	@cd ./thirdparty/googletest/; ./build.sh build

unitTest:
	make -C ./test/

.PHONY:runTest
runTest:
	make -C ./test/ $@

.PHONY:clean
clean:
	@cd ./thirdparty/googletest/; ./build.sh clean
	make -C ./test/ clean

