#include "..\include\light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntennsity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntennsity = dIntensity;
}


void Light::UseLight(GLfloat ambientIntensityLocatioin, GLfloat ambientColourLocation,
	GLfloat diffuseInteensitylocation, GLfloat directionlocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocatioin, ambientIntensity);

	glUniform3f(directionlocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseInteensitylocation, diffuseIntennsity);
}

Light::~Light()
{
}
