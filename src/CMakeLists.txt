set(BINARY ${CMAKE_PROJECT_NAME})

include_directories(jsoncpp/include)

# Collect all header files
# file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true *.h *.hpp)

# Collect all source files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.c *.cpp *.h *.hpp)

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})