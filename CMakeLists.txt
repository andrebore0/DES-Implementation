cmake_minimum_required(VERSION 3.0)
project(DESImpl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE
	bit_manipulation.h
	bit_manipulation.cxx
	string_manipulation.h
	string_manipulation.cxx
	input_handling.h
	input_handling.cxx
	des_defs.h
	des.h
	des.cxx
)

add_executable(desimpl ${SOURCE})