cmake_minimum_required (VERSION 2.8)

project (PSPROJECTTEMPLATE)

file(GLOB PSPROJECTTEMPLATE_SRC
    "Source/*.h"
    "Source/*.cpp"
)

add_executable(PSPROJECTTEMPLATE ${PSPROJECTTEMPLATE_SRC})
