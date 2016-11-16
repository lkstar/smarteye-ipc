#!/bin/bash
echo "
******************************************************
Linux ipc 编译版本需求：
	CMake 3.5 及其以上版本
	GCC 4.8 及其以上版本
	G++ 4.8 及其以上版本
	C++ 运行时库 libstdc++.so.6.0.19 及其以上版本
Linux ipc 编译步骤：
	1. 修改smarteye-ipc根目录下CMakeLists.txt 中 
	   COMPILER 变量设置成 LINUX(或者其它想编译的平台)
	2. 直接运行smarteye-ipc根目录下的 ./build.sh
******************************************************
"
echo "cmake --version:"
cmake --version
echo "gcc --version:"
gcc --version
echo "g++ --version:"
g++ --version
