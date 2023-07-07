#include "helperFunc.h"

#include <glad/glad.h>

#include <iostream>
#include <string>

void checkStatus(unsigned int refID, const std::string& type) {
  int success;
  char infoLog[512];
  if (type.compare("VERTEX") == 0 || type.compare("FRAGMENT") == 0) {
    glGetShaderiv(refID, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(refID, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
                << infoLog << '\n';
    }
  } else if (type.compare("PROGRAM") == 0) {
    glGetProgramiv(refID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(refID, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::" << type << "::LINK_FAILED\n"
                << infoLog << '\n';
    }
  } else {
    std::cout << "Invalid type!\n";
  }
}