#pragma once

#include <glad/glad.h> // Include glad to get OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
	public:
	
		// Shader program id
		unsigned int ID;
		
		// Constructor to read and build shader
		// Takes path to vertex and fragment shader sources as args
		Shader(const char* vertexPath, const char* fragmentPath);
		
		// Function to activate (use) the shader
		void use();
		
		// Utility functions for shader uniforms
		// Here const at end of declarations prevents writing of member variables
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setMat4(const std::string &name, glm::mat4 value) const;
};