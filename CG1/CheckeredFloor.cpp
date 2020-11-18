#include "CheckeredFloor.hpp"

CG::CheckeredFloor::CheckeredFloor(int size, int nsquare)
	: m_Size	{ size    }
	, m_Nsquare { nsquare }
{
	float minX = -static_cast<float>(size) / 2, minZ = -static_cast<float>(size) / 2;
	float maxX =  static_cast<float>(size) / 2, maxZ =  static_cast<float>(size) / 2;

	float sizeX = (maxX - minX) / static_cast<float>(m_Nsquare);
	float sizeZ = (maxZ - minZ) / static_cast<float>(m_Nsquare);

	float squareSize = static_cast<float>(m_Size) / static_cast<float>(m_Nsquare);

	CG_LOG_INFO("number of squares: {} x {}", squareSize, squareSize);
	CG_LOG_INFO("square size: {}", squareSize);

	for (int x = 0; x < m_Nsquare; ++x) {
		for (int z = 0; z < m_Nsquare; ++z) {
			_planes.push_back(std::make_unique<Plane>(
				glm::vec3(x * sizeX, 0.f, z * sizeZ),
				glm::vec3(90.f, 0.f, 0.f),
				glm::vec3(squareSize, 0.f, squareSize)
			));
		}
	}
}

const std::vector<std::unique_ptr<CG::AShape>>& CG::CheckeredFloor::board() const
{
	return _planes;
}