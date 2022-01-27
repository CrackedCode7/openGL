/* KEEP IN MIND THAT TRANSFORMATIONS ARE APPLIED IN REVERSE ORDER TO HOW THEY ARE CODED.
   FOR EXAMPLE, IF WE SET TRANS = GLM::TRANSLATE THEN TRANS = GLM::ROTATE, THEN THE
   ROTATION IS APPLIED FIRST, THEN TRANSLATED
*/


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


int main()
{
    // Create vector 1, 0, 0 (fourth is w value)
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    // Create tramsformation matrix initialized to identity matrix
    glm::mat4 trans = glm::mat4(1.0f);

    // Adjust transformation matrix to translate by 1, 1, 0
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

    // Translate vector vec by multiplying with transofrmation matrix
    vec = trans * vec;

    // Output result vector (should be (2, 1, 0))
    std::cout << vec.x << vec.y << vec.z << std::endl;

    return 0;
}