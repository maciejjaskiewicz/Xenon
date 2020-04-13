option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)

if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all
                                --inconclusive -i ${CMAKE_SOURCE_DIR}/imgui/lib)
    else()
        message(SEND_ERROR "cppcheck requested but executable not found")
    endif()
endif()