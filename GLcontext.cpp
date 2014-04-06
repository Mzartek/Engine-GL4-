#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  matrixLoadBias(_biasMatrix);
  _program = NULL;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::config(const GLuint &width, const GLuint &height, const GLfloat &near, const GLfloat &far, ShaderProgram *program)
{
  _width = width;
  _height = height;
  _near = near;
  _far = far;
  _program = program;

  glUseProgram(_program->getId());
  glUniformMatrix4fv(glGetUniformLocation(_program->getId(), "biasMatrix"), 1, GL_FALSE, _biasMatrix);
  glUseProgram(0);
  
  projectionMatrixLocation = glGetUniformLocation(_program->getId(), "projectionMatrix");
  viewMatrixLocation = glGetUniformLocation(_program->getId(), "viewMatrix");
  modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
  depthProjectionMatrixLocation = glGetUniformLocation(_program->getId(), "depthProjectionMatrix");
  depthViewMatrixLocation = glGetUniformLocation(_program->getId(), "depthViewMatrix");
  matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
  lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
  lightSpotDirectionLocation = glGetUniformLocation(_program->getId(), "lightSpotDirection");
  lightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "lightSpotCutOff");
  lightAmbientLocation = glGetUniformLocation(_program->getId(), "lightAmbient");
  lightDiffuseLocation = glGetUniformLocation(_program->getId(), "lightDiffuse");
  lightSpecularLocation = glGetUniformLocation(_program->getId(), "lightSpecular");
  textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
  shadowTextureLocation = glGetUniformLocation(_program->getId(), "shadowMap");
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glViewport(0, 0, _width, _height);
}

GLuint engine::GLcontext::getProgramId(void)
{
  return _program->getId();
}

GLuint engine::GLcontext::getWidth(void)
{
  return _width;
}

GLuint engine::GLcontext::getHeight(void)
{
  return _height;
}

GLfloat engine::GLcontext::getNear(void)
{
  return _near;
}

GLfloat engine::GLcontext::getFar(void)
{
  return _far;
}

void engine::GLcontext::clear(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, _width, _height);
}
