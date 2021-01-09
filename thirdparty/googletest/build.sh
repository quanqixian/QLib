#!/bin/bash

#############################
#func  :编译安装googletest
#############################
function build()
{
	#创建安装目录install
	mkdir install

	#解压并进入源码目录
	tar -xvf googletest-release-1.10.0.tar.gz
	cd googletest-release-1.10.0

	#创建编译目录build
	mkdir build

	#编译安装
	cd build
	cmake -DCMAKE_INSTALL_PREFIX=../../install ..
	make
	make install

}
#############################
#func  :清除编译
#############################
function clean()
{
	rm -rf ./googletest-release-1.10.0/
	rm -rf ./install/
}

#########################
#func: 菜单
#########################
function menu()
{

	if [ $# -ne 1 ]
	then
		echo "usage : $0 build/clean"
		exit
	fi

	if   [ $1 = "build" ]
	then
		build
	elif [ $1 = "clean" ]
	then
		clean
	else
		echo "usage : $0 build/clean"
	fi
}

function main()
{
	menu $*
}
main $*
