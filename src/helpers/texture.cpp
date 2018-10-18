#include "texture.hpp"
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

namespace texture {

unsigned int load(const string &path) {
  unsigned int textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(path.data(), &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture: " << path << endl;
    glDeleteTextures(1, &textureId);
    textureId = 0;
  }
  stbi_image_free(data);

  return textureId;
}

void free(unsigned int textureId) { glDeleteTextures(1, &textureId); }

} // namespace texture
