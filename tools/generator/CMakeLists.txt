SET(COMMON_PATH ${PROJECT_SOURCE_DIR}/common)
SET(CPP_PATH ${PROJECT_SOURCE_DIR}/cpp)
SET(GENERATOR_PATH ${PROJECT_SOURCE_DIR}/tools/generator)

SET(GENERATOR_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${GENERATOR_PATH}/GraphGenerator.cpp
    ${GENERATOR_PATH}/generator.cpp)

INCLUDE_DIRECTORIES(
    ${GENERATOR_PATH}
    ${COMMON_PATH}
    ${CPP_PATH}
    )

ADD_EXECUTABLE(${TARGET_GENERATOR} ${GENERATOR_SOURCES})
