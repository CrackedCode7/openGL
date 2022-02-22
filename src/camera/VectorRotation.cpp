#include "VectorRotation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


glm::vec3 rotate_vec3(glm::vec3 v, glm::vec3 k, float theta)
{
    v = glm::normalize(v);
    k = glm::normalize(k);
    theta = glm::radians(theta);

    return v*glm::cos(theta) + (glm::cross(k, v))*glm::sin(theta) + k*(glm::dot(k, v))*(1-glm::cos(theta));
}