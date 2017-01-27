project(neural-networks-tests)

set(SOURCES main.cpp
    XorTest.cpp
    MnistBenchmark.cpp
    Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNodeTest.cpp
    UnaryOperations/SigmoidUnaryOperationTest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    neural-networks-lib
    gtest
)
