#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "Object.hpp"

namespace Engine
{
	class Buffer;
	class DepthMap;
	class ShaderProgram;
	class GBuffer;
	class PerspCamera;

	class DLLAPI Light : public Object
	{
	protected:
		struct
		{
			glm::mat4 IVPMatrix;
			glm::uvec2 ALIGN(16) screen;
			glm::vec3 ALIGN(16) camPosition;
		} _mainInfo;

		Buffer *_vertexBuffer;
		Buffer *_mainInfoBuffer;
		Buffer *_lightInfoBuffer;
		ShaderProgram *_program;
		GLuint _idVAO;
		glm::mat4 *_projectionMatrix;
		glm::mat4 *_viewMatrix;
		glm::mat4 *_VPMatrix;
	public:
		Light(ShaderProgram *program);
		~Light(void);
		virtual void display(GBuffer *gbuf, PerspCamera *cam) = 0;
		virtual void display(GBuffer *gbuf, DepthMap *dmap, PerspCamera *cam) = 0;
	};
}

#endif
