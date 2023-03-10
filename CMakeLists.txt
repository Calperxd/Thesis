project(HelloWorld)
cmake_minimum_required(VERSION 3.5)

#VARIABLES
set(LINKER_SCRIPT "linker/memory.ld")
set(TARGET_NAME hello_world)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CPU -mcpu=cortex-m4)
set(FPU -mfpu=fpv4-sp-d16 -mfloat-abi=hard)
set(AFLAGS -mthumb
            ${CPU}
            ${FPU}
            -MD
        )
set(CFLAGS -mthumb
            ${CPU}
            ${FPU}
            -ffunction-sections
            -fdata-sections
            -MD
            -std=c99
            -Wall
            -pedantic
            -c)

set(LDFLAGS --data-sections --specs=nosys.specs ${CPU} -g -mthumb -mfloat-abi=hard)

#Header files
include_directories(include)
include_directories($ENV{TIVAWARE_HOME})


#compiler options
add_compile_options(-mthumb
                    ${CPU}
                    ${FPU}
                    -ffunction-sections
                    -fdata-sections
                    -MD
                    -std=c99
                    -Wall
                    -pedantic
                    -DPART_${PART}
                    -c
                    -lnosys
                    )

#linker options
add_link_options(${LDFLAGS})

#Files that must be compiled
file(GLOB SourceFiles source/*.c)

#generate the bin file
add_executable(${TARGET_NAME} main.c ${SourceFiles})

#enable the pin maps from tivaware
target_compile_definitions(${TARGET_NAME} PRIVATE PART_TM4C129ENCPDT=1)


