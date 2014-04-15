#include <Engine/GLcontext.hpp>

engine::GLcontext::GLcontext(void)
{
  _program = NULL;
  _cam = NULL;
  _dlight = NULL;
  _slight = NULL;
}

engine::GLcontext::~GLcontext(void)
{
}

void engine::GLcontext::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  
  MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
  modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
  normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
  
  matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  
  camPositionLocation = glGetUniformLocation(_program->getId(), "camPosition");
  
  dirLightDirectionLocation = glGetUniformLocation(_program->getId(), "dirLightDirection");
  dirLightAmbientLocation = glGetUniformLocation(_program->getId(), "dirLightAmbient");
  dirLightDiffuseLocation = glGetUniformLocation(_program->getId(), "dirLightDiffuse");
  dirLightSpecularLocation = glGetUniformLocation(_program->getId(), "dirLightSpecular");
  dirShadowMVPLocation = glGetUniformLocation(_program->getId(), "dirShadowMVP");
  dirShadowMapLocation = glGetUniformLocation(_program->getId(), "dirShadowMap");
  
  spotLightPositionLocation = glGetUniformLocation(_program->getId(), "spotLightPosition");
  spotLightDirectionLocation = glGetUniformLocation(_program->getId(), "spotLightDirection");
  spotLightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "spotLightCutOff");
  spotLightAmbientLocation = glGetUniformLocation(_program->getId(), "spotLightAmbient");
  spotLightDiffuseLocation = glGetUniformLocation(_program->getId(), "spotLightDiffuse");
  spotLightSpecularLocation = glGetUniformLocation(_program->getId(), "spotLightSpecular");
  spotShadowMVPLocation = glGetUniformLocation(_program->getId(), "spotShadowMVP");
  spotShadowMapLocation = glGetUniformLocation(_program->getId(), "spotShadowMap");
  
  textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
}

void engine::GLcontext::setCamera(Camera *cam)
{
  _cam = cam;
}

void engine::GLcontext::setDirLight(DirLight *light)
{
  _dlight = light;
}

void engine::GLcontext::setSpotLight(SpotLight *light)
{
  _slight = light;
}

GLuint engine::GLcontext::getProgramId(void)
{
  return _program->getId();
}

engine::Camera *engine::GLcontext::getCamera(void)
{
  return _cam;
}

engine::DirLight *engine::GLcontext::getDirLight(void) const
{
  return _dlight;
}

engine::SpotLight *engine::GLcontext::getSpotLight(void) const
{
  return _slight;
}

void engine::GLcontext::newLoop(void)
{
  if(_cam==NULL)
    {
      std::cerr << "You need to set a camera first\n" << std::endl;
      return;
    }
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, _cam->getWidth(), _cam->getHeight());
  GLfloat camera[] = {_cam->getPositionCamera()._x, _cam->getPositionCamera()._y, _cam->getPositionCamera()._z};
  
  glUseProgram(_program->getId());
  
  glUniform3fv(camPositionLocation, 1, camera);
  
  if(_dlight!=NULL)
    {
      glUniform3fv(dirLightDirectionLocation, 1, _dlight->getDirection());
      glUniform4fv(dirLightAmbientLocation, 1, _dlight->getAmbient());
      glUniform4fv(dirLightDiffuseLocation, 1, _dlight->getDiffuse());
      glUniform4fv(dirLightSpecularLocation, 1, _dlight->getSpecular());
    }

  if(_slight!=NULL)
    {
      glUniform3fv(spotLightPositionLocation, 1, _slight->getPosition());
      glUniform3fv(spotLightDirectionLocation, 1, _slight->getDirection());
      glUniform1fv(spotLightSpotCutOffLocation, 1, _slight->getSpotCutOff());
      glUniform4fv(spotLightAmbientLocation, 1, _slight->getAmbient());
      glUniform4fv(spotLightDiffuseLocation, 1, _slight->getDiffuse());
      glUniform4fv(spotLightSpecularLocation, 1, _slight->getSpecular());
    }
  
  glUseProgram(0);
}
