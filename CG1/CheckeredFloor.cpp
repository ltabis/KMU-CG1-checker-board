#include "CheckeredFloor.hpp"

CG::CheckeredFloor::CheckeredFloor(int size, int nsquare)
	: m_Size	{ size    }
	, m_Nsquare { nsquare }
{
	float squareSize = m_Size / m_Nsquare;

	//for (int n = 0; n < m_Nsquare; ++n) {
	//	_planes.push_back(Plane(
	//		glm::vec3(n, 0.f, 1.f),
	//		glm::vec3(0.f, 0.f, 0.f),
	//		glm::vec3(squareSize, 0.f, 1.f)
	//	));
	//}
}

const std::vector<CG::Plane>& CG::CheckeredFloor::board() const
{
	return _planes;
}