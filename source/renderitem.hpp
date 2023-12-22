#include <vulkan/vulkan.h>
#include <array>
#include <vector>
#include <glm/glm.hpp>

class renderitem
{
public:

	struct Vertex
	{
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescriptions();
		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
	};

	const std::vector<Vertex> vertices =
	{
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
	};

private:




};