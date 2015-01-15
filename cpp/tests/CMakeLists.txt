SET(COMMON_PATH ${PROJECT_SOURCE_DIR}/common)
SET(KRUSKAL_PATH ${PROJECT_SOURCE_DIR}/cpp/kruskal)
SET(BORUVKA_PATH ${PROJECT_SOURCE_DIR}/cpp/boruvka)

SET(TEST_PATH ${PROJECT_SOURCE_DIR}/cpp/tests)

INCLUDE_DIRECTORIES(
    ${COMMON_PATH}
    ${PROJECT_SOURCE_DIR}/cpp
    ${PROJECT_SOURCE_DIR}/tools
    )

SET(KRUSKAL_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${PROJECT_SOURCE_DIR}/tools/generator/GraphGenerator.cpp
    ${KRUSKAL_PATH}/Kruskal.cpp
    ${TEST_PATH}/kruskal_test.cpp
    )

SET(BORUVKA_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${PROJECT_SOURCE_DIR}/tools/generator/GraphGenerator.cpp
    ${BORUVKA_PATH}/Boruvka.cpp
    ${TEST_PATH}/boruvka_test.cpp
    )

SET(MST_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${KRUSKAL_PATH}/Kruskal.cpp
    ${BORUVKA_PATH}/Boruvka.cpp
    ${TEST_PATH}/mst_test.cpp
    )

SET(LIST_SOURCES
    ${TEST_PATH}/list_test.cpp
    )

SET(VECTOR_SOURCES
    ${TEST_PATH}/vector_test.cpp
    )

SET(QUICKSORT_SOURCES
    ${TEST_PATH}/quicksort_test.cpp
)

ADD_EXECUTABLE(${TARGET_KRUSKAL} ${KRUSKAL_SOURCES})
ADD_EXECUTABLE(${TARGET_BORUVKA} ${BORUVKA_SOURCES})
ADD_EXECUTABLE(${TARGET_MST} ${MST_SOURCES})
ADD_EXECUTABLE(${TARGET_LIST} ${LIST_SOURCES})
ADD_EXECUTABLE(${TARGET_VECTOR} ${VECTOR_SOURCES})
ADD_EXECUTABLE(${TARGET_QUICKSORT} ${QUICKSORT_SOURCES})
