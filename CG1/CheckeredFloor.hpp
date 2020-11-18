#pragma once

#include <glm/gtx/string_cast.hpp>

#include "WorldObjects/Primitives/Plane.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "NoClipCameraController.hpp"

namespace CG {
	class CheckeredFloor
	{
	public:
		// size: full size of the checkered floor.
		// nsquare: number of squares for each side.
		CheckeredFloor(int size, int nsquare);

		const std::vector<std::unique_ptr<AShape>>& board() const;
		int size() const    { return m_Size;    }
		int nsquare() const { return m_Nsquare; }
	private:
		int m_Size;
		int m_Nsquare;

		std::vector<std::unique_ptr<AShape>> _planes;
	};
}
