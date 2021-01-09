all: thirdParty unitTest

thirdParty:googletest

googletest:
	@cd ./thirdparty/googletest/; ./build.sh build
unitTest:

.PHONY:clean
clean:
	@cd ./thirdparty/googletest/; ./build.sh clean

