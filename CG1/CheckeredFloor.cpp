#include "CheckeredFloor.hpp"

CG::CheckeredFloor::CheckeredFloor(int size, int nsquare)
	: m_Size	{ size    }
	, m_Nsquare { nsquare }
{
	float squareSize = m_Size / m_Nsquare;

	CG_LOG_INFO("number of squares: {} x {}", squareSize, squareSize);
	CG_LOG_INFO("square size: {}", squareSize);

	for (int x = 0; x < m_Nsquare; ++x) {
		for (int z = 0; z < m_Nsquare; ++z) {
			_planes.push_back(std::make_unique<Plane>(
				glm::vec3(x * 3, 0.f, z * 3),
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