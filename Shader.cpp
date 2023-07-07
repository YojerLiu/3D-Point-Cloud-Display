#include "Shader.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "helperFunc.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
  // Retrieve the vertex/fragment source code from file path
  std::string vertexCode, fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // Ensure ifstream objects can throw exception
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // Open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // Read file's buffer contents into stream
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // Close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (const std::ifstream::failure&) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // Compile shaders
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  checkStatus(vertex, "VERTEX");

  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  checkStatus(fragment, "FRAGMENT");

  // Shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkStatus(ID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
