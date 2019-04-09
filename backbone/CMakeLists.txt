project(backbone)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5
    COMPONENTS
        Core QuickControls2
    REQUIRED)
find_package(portable_concurrency REQUIRED)

add_library(${PROJECT_NAME}
    include/backbone/appcontroller.h
    include/backbone/applicationframe.h
    include/backbone/block.h
    include/backbone/container.h
    include/backbone/context.h
    include/backbone/global.h
    include/backbone/incubator.h
    include/backbone/page.h
    include/backbone/pagepresenter.h
    include/backbone/presenter.h
    include/backbone/qmlcomponentscache.h
    include/backbone/qmlglobalscope.h
    include/backbone/injectorbuilder.h
    include/backbone/injector.h
    include/backbone/router.h
    include/backbone/executors.h
    include/backbone/fwd.h
    include/backbone/delegatebuilder.h
    include/backbone/injectorblock.h
    include/backbone/scope.h

    src/appcontroller.cpp
    src/applicationframe.cpp
    src/block.cpp
    src/container.cpp
    src/context.cpp
    src/global.cpp
    src/incubator.cpp
    src/page.cpp
    src/pagepresenter.cpp
    src/presenter.cpp
    src/qmlcomponentscache.cpp
    src/qmlglobalscope.cpp
    src/injectorbuilder.cpp
    src/injector.cpp
    src/router.cpp
    src/executors.cpp
    src/delegatebuilder.cpp
    src/injectorblock.cpp
    src/scope.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::QuickControls2
        portable_concurrency::portable_concurrency
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

if (USE_PRIVATE_HEADERS)
    message(STATUS "we use private Qt headers.")

    add_definitions(${PROJECT_NAME} -DSTACK_VIEW_ENABLE)

    find_package(Qt5
        COMPONENTS
            QuickTemplates2
        REQUIRED)

    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            Qt5::QuickTemplates2
    )

    target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include

        PRIVATE
            ${Qt5Core_PRIVATE_INCLUDE_DIRS}
            ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
            ${Qt5Qml_PRIVATE_INCLUDE_DIRS}
            ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
            ${Qt5QuickControls2_PRIVATE_INCLUDE_DIRS}
            ${Qt5QuickTemplates2_PRIVATE_INCLUDE_DIRS}
    )
endif()


target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)


