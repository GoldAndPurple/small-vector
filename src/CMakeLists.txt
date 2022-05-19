include(CompileOptions)

set(target vec)

add_library(
${target} OBJECT
${target}/${target}.hpp
)

set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CPP)

set_compile_options(${target})

target_include_directories(
${target}
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
