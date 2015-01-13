SET(COMMON_PATH ${PROJECT_SOURCE_DIR}/common)
SET(KRUSKAL_PATH ${PROJECT_SOURCE_DIR}/cpp/kruskal)
SET(BORUVKA_PATH ${PROJECT_SOURCE_DIR}/cpp/boruvka)

SET(PROFILER_PATH ${PROJECT_SOURCE_DIR}/cpp/profiler)

INCLUDE_DIRECTORIES(
    ${COMMON_PATH}
    ${PROJECT_SOURCE_DIR}/cpp
    )

SET(KRUSKAL_PROFILER_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${KRUSKAL_PATH}/Kruskal.cpp
    ${PROFILER_PATH}/kruskal_profiler.cpp
    )

SET(BORUVKA_PROFILER_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${BORUVKA_PATH}/Boruvka.cpp
    ${PROFILER_PATH}/boruvka_profiler.cpp
    )

ADD_EXECUTABLE(${TARGET_KRUSKAL_PROFILER} ${KRUSKAL_PROFILER_SOURCES})
ADD_EXECUTABLE(${TARGET_BORUVKA_PROFILER} ${BORUVKA_PROFILER_SOURCES})
