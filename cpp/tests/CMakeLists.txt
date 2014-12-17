SET(COMMON_PATH ${PROJECT_SOURCE_DIR}/common)
SET(KRUSKAL_PATH ${PROJECT_SOURCE_DIR}/cpp/kruskal)

SET(TEST_PATH ${PROJECT_SOURCE_DIR}/cpp/tests)

INCLUDE_DIRECTORIES(
    ${COMMON_PATH}
    ${PROJECT_SOURCE_DIR}/cpp
    )

SET(KRUSKAL_SOURCES
    ${COMMON_PATH}/graph/Graph.cpp
    ${COMMON_PATH}/serializer/GraphPrinter.cpp
    ${COMMON_PATH}/serializer/GraphSerialization.cpp
    ${KRUSKAL_PATH}/Kruskal.cpp
    ${TEST_PATH}/kruskal_test.cpp
    )

SET(LIST_SOURCES
    ${TEST_PATH}/list_test.cpp
    )

ADD_EXECUTABLE(${TARGET_KRUSKAL} ${KRUSKAL_SOURCES})
ADD_EXECUTABLE(${TARGET_LIST} ${LIST_SOURCES})
