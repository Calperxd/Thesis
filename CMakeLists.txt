cmake_minimum_required(VERSION 3.0)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)

project(NOME_DO_PROJETO C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
# Avoid known bug in linux giving:
#    arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(PART TM4C129ENCPDT)
set(CMAKE_C_FLAGS "-Wall -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -DPART_${PART} -Dgcc -O2")
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs -nostartfiles -T ${CMAKE_SOURCE_DIR}/linkerscripts/linker.ld -Wl,-Map=${PROJECT_NAME}.map")

include_directories(include)
include_directories($ENV{TIVAWARE_HOME})
include_directories($ENV{FREERTOS_HOME}/FreeRTOS/Source/include)
include_directories($ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/GCC/ARM_CM4F)
include_directories($ENV{TIVAWARE_HOME}/utils)

file(GLOB SOURCE "${CMAKE_SOURCE_DIR}/source/*.c")
file(GLOB DRIVERLIBSOURCE "$ENV{TIVAWARE_HOME}/driverlib/*.c" "$ENV{TIVAWARE_HOME}/utils/uartstdio.c")
file(GLOB FreeRTOSSource1 $ENV{FREERTOS_HOME}/FreeRTOS/Source/*.c)
file(GLOB FreeRTOSSource2 $ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/MemMang/heap_4.c)
file(GLOB FreeRTOSSource3 $ENV{FREERTOS_HOME}/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c)
set(FREERTOSSOURCE ${FreeRTOSSource1} ${FreeRTOSSource2} ${FreeRTOSSource3})


set(ELF_NAME ${PROJECT_NAME}.elf)
add_executable(${ELF_NAME} ${SOURCE} ${DRIVERLIBSOURCE} ${FREERTOSSOURCE})

target_link_libraries(${ELF_NAME} ${CMAKE_SOURCE_DIR}/lib/libfftw3.a)
target_link_libraries(${ELF_NAME} m)
target_compile_options(${ELF_NAME} PUBLIC -Wall)

set(BIN_NAME ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Converting ${ELF_NAME} to ${BIN_NAME}"
    VERBATIM)
