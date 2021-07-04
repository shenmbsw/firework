cmake_minimum_required(VERSION 3.17)
project(usbrelay C)
add_library(usbrelay SHARED usbrelay.c libusbrelay.c)
target_link_libraries(usbrelay /usr/lib/x86_64-linux-gnu/libhidapi-hidraw.so.0)
