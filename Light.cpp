#include <Engine/Light.hpp>

engine::Light::Light(void)
{
  unsigned i;
  _lightPosition[0] = 0;
  _lightPosition[1] = 0;
  _lightPosition[2] = 0;
  for(i=0 ; i<4 ; i++)
    {
      _lightAmbient[i]=1.0;
      _lightDiffuse[i]=1.0;
      _lightSpecular[i]=1.0;
    }
  _lightSpotDirection[0] = 1.0;
  _lightSpotDirection[1] = 0;
  _lightSpotDirection[2] = 0;
  _lightSpotCutOff[0] = 180;
  _program = NULL;
}

engine::Light::Light(const float &x, const float &y, const float &z)
{
  unsigned i;
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
  for(i=0 ; i<4 ; i++)
    {
      _lightAmbient[i]=1.0;
      _lightDiffuse[i]=1.0;
      _lightSpecular[i]=1.0;
    }
  _lightSpotDirection[0] = 1.0;
  _lightSpotDirection[1] = 0;
  _lightSpotDirection[2] = 0;
  _lightSpotCutOff[0] = 180;
  _program = NULL;
}

engine::Light::~Light(void)
{
}

void engine::Light::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _lightPositionLocation = glGetUniformLocation(_program->getId(), "lightPosition");
  _lightSpotDirectionLocation = glGetUniformLocation(_program->getId(), "lightSpotDirection");
  _lightSpotCutOffLocation = glGetUniformLocation(_program->getId(), "lightSpotCutOff");
  _lightAmbientLocation = glGetUniformLocation(_program->getId(), "lightAmbient");
  _lightDiffuseLocation = glGetUniformLocation(_program->getId(), "lightDiffuse");
  _lightSpecularLocation = glGetUniformLocation(_program->getId(), "lightSpecular");
}

void engine::Light::setPosition(const float &x, const float &y, const float &z)
{
  _lightPosition[0] = x;
  _lightPosition[1] = y;
  _lightPosition[2] = z;
}

void engine::Light::setDirection(const float &x, const float &y, const float &z)
{
  _lightSpotDirection[0] = x;
  _lightSpotDirection[1] = y;
  _lightSpotDirection[2] = z;
}

void engine::Light::setCone(const float &x)
{
  _lightSpotCutOff[0] = x;
}

void engine::Light::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightAmbient[0] = x;
  _lightAmbient[1] = y;
  _lightAmbient[2] = z;
  _lightAmbient[3] = w;
}

void engine::Light::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightDiffuse[0] = x;
  _lightDiffuse[1] = y;
  _lightDiffuse[2] = z;
  _lightDiffuse[3] = w;
}

void engine::Light::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _lightSpecular[0] = x;
  _lightSpecular[1] = y;
  _lightSpecular[2] = z;
  _lightSpecular[3] = w;
}

engine::Vector3D<float> engine::Light::getPosition(void)
{
  engine::Vector3D<float> tmp;
  tmp._x = _lightPosition[0];
  tmp._y = _lightPosition[1];
  tmp._z = _lightPosition[2];
  return tmp;
}

void engine::Light::position(void)
{
  _program->use();
  glUniform3fv(_lightPositionLocation,  1, _lightPosition);
  glUniform3fv(_lightSpotDirectionLocation,  1, _lightSpotDirection);
  glUniform1fv(_lightSpotCutOffLocation,  1, _lightSpotCutOff);
  glUniform4fv(_lightAmbientLocation,  1, _lightAmbient);
  glUniform4fv(_lightDiffuseLocation,  1, _lightDiffuse);
  glUniform4fv(_lightSpecularLocation,  1, _lightSpecular);
  glUseProgram(0);
}
