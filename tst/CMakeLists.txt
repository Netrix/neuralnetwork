project(neural-networks-tests)

set(SOURCES main.cpp
    XorTest.cpp
    Nodes/LayerNodes/PassThroughLayerNodeTest.cpp
    UnaryOperations/SigmoidUnaryOperationTest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    neural-networks-lib
    gtest
)
