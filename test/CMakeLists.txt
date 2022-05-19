set(target_name test_vec)

add_executable(
  ${target_name}
  ${target_name}.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
  ${target_name}
  PRIVATE
    vec
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${target_name})