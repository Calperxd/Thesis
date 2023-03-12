cmake_minimum_required(VERSION 3.0)
project(MeuProjeto C)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(PART TM4C129ENCPDT)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-Wl,-no-dynamic-linker")
set(CMAKE_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linkerscripts/linker.ld)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-no-dynamic-linker -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -O2 -DPART_${PART}")

include_directories(include)
include_directories($ENV{TIVAWARE_HOME})
include_directories($ENV{FREERTOS_HOME}/FreeRTOS/Source/include)
include_directories($ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/GCC/ARM_CM4F)

file(GLOB SOURCES "source/*.c")
file(GLOB DriverLib $ENV{TIVAWARE_HOME}/driverlib/*.c)
file(GLOB FreeRTOSSource1 $ENV{FREERTOS_HOME}/FreeRTOS/Source/*.c)
file(GLOB FreeRTOSSource2 $ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/MemMang/heap_4.c)
file(GLOB FreeRTOSSource3 $ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c)
set(FreeRTOSSource ${FreeRTOSSource1} ${FreeRTOSSource2} ${FreeRTOSSource3})
set(SOURCES ${FreeRTOSSource} ${DriverLib} source/startup_gcc.c)
add_definitions(-Dgcc)

add_executable(main main.c ${SOURCES})
set_target_properties(main PROPERTIES OUTPUT_NAME "main.axf")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-no-dynamic-linker -T ${CMAKE_LINKER_SCRIPT} -Wl,-Map=main.map -nostartfiles --specs=nosys.specs -D__STARTUP_FROM_RESET_VECTOR__")

add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy main.axf main.bin
        COMMAND arm-none-eabi-size $<TARGET_FILE:main>
        )

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LINKER_SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/linkerscripts)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/build")
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/build")

file(COPY ${INCLUDE_DIR} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${LIB_DIR} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${LINKER_SCRIPT_DIR} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY ${SOURCE_DIR} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)