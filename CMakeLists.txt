cmake_minimum_required(VERSION 3.10)

project(btrfs-proj)
set(CMAKE_C_COMPILER gcc)
add_executable(btrfs-readinfo btrfs-readinfo.c)
