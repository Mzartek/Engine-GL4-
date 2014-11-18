#ifndef PLAYERCAM_HEADER
#define PLAYERCAM_HEADER

#include "MovableCamera.hpp"

namespace Engine
{
	class DLLAPI PlayerCam : public MovableCamera
	{
	public:
		PlayerCam(void);
		~PlayerCam(void);
		void keyboardMove(const GLboolean &f, const GLboolean &b, const GLboolean &l, const GLboolean &r);
	};
}

#endif
