#include <Engine/Model.hpp>

engine::Model::Model(void)
{
  _index = 0;
  _program = NULL;
  _modelMatrixLocation = -1;
  matIdentity();
}

engine::Model::~Model(void)
{
  unsigned i;
  for(i=0 ; i<_tObject.size(); i++)
    delete _tObject[i];
}

void engine::Model::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
}

unsigned engine::Model::createObject(const GLfloat *vertexArray, const GLuint &sizeVertexArray,
				     const GLuint *elementArray, const GLuint &sizeElementArray,
				     const std::string pathTexture,
				     const GLfloat *ambiant, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
  unsigned id;
  Object *newone = new Object();

  engine::initBufferObject(GL_ARRAY_BUFFER, sizeVertexArray, &id, (void *)vertexArray);
  newone->setIdObject(id);
  engine::initBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeElementArray, &id, (void *)elementArray);
  newone->setIdElementObject(id, sizeElementArray/sizeof(GLuint));
  engine::loadTex(pathTexture, &id);
  newone->setIdTextureObject(id);
  newone->setAmbiant(ambiant[0], ambiant[1], ambiant[2], ambiant[3]);
  newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
  newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
  newone->setShininess(shininess[0]);
  newone->setShaderProgram(_program);
  
  _tObject.push_back(newone);
  return _index++;
}

void engine::Model::matIdentity(void)
{
  matrixLoadIdentity(_modelMatrix);
}

void engine::Model::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixTranslate(_modelMatrix, x, y, z);
}

void engine::Model::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixRotate(_modelMatrix, angle*((GLfloat)M_PI/180), x, y, z);
}

void engine::Model::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
  matrixScale(_modelMatrix, x, y, z);
}
  
void engine::Model::display(void)
{
  unsigned i;
  
  _program->use();
  glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, _modelMatrix);
  
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->display();
}
