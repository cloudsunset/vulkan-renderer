add_executable (vulkan_renderer "main.cpp"  "core.hpp" "core.cpp" "window.cpp"  "device.cpp" "instance.cpp" "vlayers.hpp" "vlayers.cpp" "swapchain.cpp" "pipeline.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET vulkan_renderer PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD 20)

find_package(vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

target_include_directories(vulkan_renderer PRIVATE stb)

include_directories("${PROJECT_SOURCE_DIR}/external/stb/stb_image.h")

target_link_libraries(vulkan_renderer PRIVATE glfw)
target_link_libraries(vulkan_renderer PRIVATE glm::glm)
target_link_libraries(vulkan_renderer PRIVATE Vulkan::Vulkan)
target_link_libraries(vulkan_renderer PRIVATE tinyobjloader::tinyobjloader)
