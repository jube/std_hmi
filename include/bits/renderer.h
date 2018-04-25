#ifndef HMI_BITS_RENDERER_H
#define HMI_BITS_RENDERER_H

#include <cstdint>

#include "vec.h"
#include "mat.h"

struct SDL_Window; // implementation detail

namespace hmi {
  class window;

  class renderer {
  public:
    ~renderer();

    vec2i get_size();

    void set_view_center(vec2f center) {
      m_view_center = center;
    }

    vec2f get_view_center() const {
      return m_view_center;
    }

    void set_view_size(vec2f size) {
      m_view_size = size;
    }

    vec2f get_view_size() const {
      return m_view_size;
    }

    vec2f get_coords_from_position(vec2i position);

    void clear(color4f color);

    void fill_rectangle(vec2f coords, vec2f size, color4f color);

    void draw_rectangle(vec2f coords, vec2f size, color4f color);

    void fill_circle(vec2f center, float radius, color4f color);

    void draw_circle(vec2f center, float radius, color4f color);

    void display();


  private:
    struct vertex {
      vec2f position;
      color4f color;
    };

    mat3f get_view_matrix() const;
    void draw(const vertex *vertices, std::size_t count, int primitive);

  private:
    friend class window;
    renderer(SDL_Window *window);

    SDL_Window *m_window;
    void *m_context;

    vec2f m_view_center;
    vec2f m_view_size;

    uint32_t m_program;
  };

}

#endif // HMI_BITS_RENDERER_H
