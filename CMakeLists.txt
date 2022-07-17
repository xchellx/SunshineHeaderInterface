cmake_minimum_required(VERSION 3.8)

add_library(JSystem INTERFACE)
target_include_directories(JSystem INTERFACE include/JSystem)

add_library(dolphin INTERFACE)
target_include_directories(dolphin INTERFACE include/dolphin)