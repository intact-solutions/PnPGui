function(set_loguru target)
  set(LOGURU_SRC ${CMAKE_SOURCE_DIR}/ThirdParty/loguru/loguru.cpp)
  target_sources(${target}
    PRIVATE
    ${LOGURU_SRC}
  )
  set_source_files_properties(${LOGURU_SRC} PROPERTIES COMPILE_FLAGS -Wno-everything)

  target_include_directories(${target}
    SYSTEM
    PUBLIC
    ${CMAKE_SOURCE_DIR}/ThirdParty/loguru/)
  target_compile_definitions(${target} PUBLIC LOGURU_WITH_STREAMS=1)

  # Loguru requires pthreads
  find_package(Threads REQUIRED)
  target_link_libraries(${target} PUBLIC Threads::Threads)
  target_link_libraries(${target} PUBLIC ${CMAKE_DL_LIBS})

  if(NOT MSVC)
    # This ensures that all symbols are in the dynamic symbol table
    # Which means they can appear in the stack traces produced by loguru
    # https://stackoverflow.com/questions/6934659/how-to-make-backtrace-backtrace-symbols-print-the-function-names
    target_link_options(${target} PUBLIC "-rdynamic")
  endif()
endfunction()
