enable_testing()
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} src)

file(GLOB_RECURSE treelibtest_SRC
  "src/*.cpp"
)

add_executable(treelibTest ${treelibtest_SRC})
target_link_libraries(treelibTest ${GTEST_BOTH_LIBRARIES} pthread)
