#pragma once
#include <OpenGL/Math/Vector2.h>
#include <string>

class Texture {
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }

private:
    unsigned int m_id;
    int m_width, m_height;
};