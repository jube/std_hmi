#include <bits/renderer.h>

#include <cassert>
#include <iostream>
#include <memory>

#include <SDL.h>
#include <glad/glad.h>

#include <bits/color.h>
#include <bits/mat_ops.h>
#include <bits/vec_ops.h>

namespace hmi {

  namespace {

    constexpr const char *g_vertex_shader = R"shader(
      #version 100

      attribute vec2 a_position;
      attribute vec4 a_color;

      varying vec4 v_color;

      uniform mat3 u_transform;

      void main(void) {
        v_color = a_color;

        vec3 worldPosition = vec3(a_position, 1);
        vec3 normalizedPosition = worldPosition * u_transform;

        gl_Position = vec4(normalizedPosition.xy, 0, 1);
      }
    )shader";

    constexpr const char *g_fragment_shader = R"shader(
      #version 100

      precision mediump float;

      varying vec4 v_color;

      void main(void) {
        gl_FragColor = v_color;
      }
    )shader";

    GLuint compile_shader(const char *code, GLenum type) {
      GLuint id = glCreateShader(type);

      if (id == 0) {
        return 0;
      }

      // compile
      const char *source[1] = { code };
      glShaderSource(id, 1, source, nullptr);
      glCompileShader(id);

      // and check
      GLint compile_status = GL_FALSE;
      glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);

      if (compile_status == GL_FALSE) {
        GLint info_log_length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);

        assert(info_log_length > 0);
        std::unique_ptr<char[]> info_log(new char[info_log_length]);
        glGetShaderInfoLog(id, info_log_length, nullptr, info_log.get());

        std::cerr << "Error while compiling shader: " << info_log.get() << std::endl;
        return 0;
      }

      return id;
    }

    constexpr
    vec2f affine_transform(const mat3f& mat, vec2f point) {
      return { mat.xx * point.x + mat.xy * point.y + mat.xz, mat.yx * point.x + mat.yy * point.y + mat.yz };
    }

  }

  renderer::renderer(SDL_Window *window)
  : m_window(window)
  , m_context(nullptr)
  , m_program(0)
  {
    // create context

    m_context = SDL_GL_CreateContext(window);

    if (m_context == nullptr) {
      std::cerr << "Failed to create a context: " << SDL_GetError() << std::endl;
      return;
    }

    int err = SDL_GL_MakeCurrent(m_window, m_context);

    if (err != 0) {
      std::cerr << "Failed to make the context current: " << SDL_GetError() << std::endl;
    }

    // load GLES2 functions

    if (gladLoadGLES2Loader(SDL_GL_GetProcAddress) == 0) {
      std::cerr << "Failed to load GLES2" << std::endl;
    }

    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // create view

    m_view_size = get_size();
    m_view_center = m_view_size / 2.0f;

    // create shader

    m_program = glCreateProgram();

    GLuint vertex_shader_id = compile_shader(g_vertex_shader, GL_VERTEX_SHADER);
    glAttachShader(m_program, vertex_shader_id);
    glDeleteShader(vertex_shader_id); // the shader is still here because it is attached to the program

    GLuint fragment_shader_id = compile_shader(g_fragment_shader, GL_FRAGMENT_SHADER);
    glAttachShader(m_program, fragment_shader_id);
    glDeleteShader(fragment_shader_id); // the shader is still here because it is attached to the program

    glLinkProgram(m_program);

    GLint link_status = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &link_status);

    if (link_status == GL_FALSE) {
      GLint info_log_length;
      glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &info_log_length);

      assert(info_log_length > 0);
      std::unique_ptr<char[]> info_log(new char[info_log_length]);
      glGetProgramInfoLog(m_program, info_log_length, nullptr, info_log.get());

      std::cerr << "Error while linking the program: " << info_log.get() << std::endl;
    }

    // initialize the screen

    clear(color::black);
  }

  renderer::~renderer() {
    // delete shader

    if (m_program != 0) {
      glDeleteProgram(m_program);
    }

    // delete context

    if (m_context != nullptr) {
      SDL_GL_DeleteContext(m_context);
    }
  }

  vec2i renderer::get_size() {
    vec2i size;
    SDL_GL_GetDrawableSize(m_window, &size.x, &size.y);
    return size;
  }

  vec2f renderer::get_coords_from_position(vec2i position) {
    vec2f viewport_position = { 0.0f, 0.0f };
    vec2f viewport_size = get_size();

    vec2f normalized;
    normalized.x = 2.0f * (position.x - viewport_position.x) / viewport_size.width - 1;
    normalized.y = 1 - 2.0f * (position.y - viewport_position.y) / viewport_size.height;

    mat3f inverse_transform = invert(get_view_matrix());

    return affine_transform(inverse_transform, normalized);
  }

  void renderer::clear(color4f color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void renderer::fill_rectangle(vec2f coords, vec2f size, color4f color) {
    vertex vertices[4];

    vertices[0].position = { coords.x,              coords.y                };
    vertices[1].position = { coords.x,              coords.y + size.height  };
    vertices[2].position = { coords.x + size.width, coords.y                };
    vertices[3].position = { coords.x + size.width, coords.y + size.height  };

    vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;

    draw(&vertices[0], 4, GL_TRIANGLE_STRIP);
  }

  void renderer::draw_rectangle(vec2f coords, vec2f size, color4f color) {
    vertex vertices[4];

    vertices[0].position = { coords.x,              coords.y                };
    vertices[1].position = { coords.x,              coords.y + size.height  };
    vertices[2].position = { coords.x + size.width, coords.y + size.height  };
    vertices[3].position = { coords.x + size.width, coords.y                };

    vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;

    draw(&vertices[0], 4, GL_LINE_LOOP);
  }

  void renderer::fill_circle(vec2f center, float radius, color4f color) {
    static constexpr int POINT_COUNT = 50;
    static constexpr float PI = 3.14159265359f;

    vertex vertices[POINT_COUNT + 2];

    vertices[0].position = center;
    vertices[0].color = color;

    for (int i = 0; i < POINT_COUNT + 1; ++i) {
      float angle = 2 * PI * i / POINT_COUNT;
      vertices[i + 1].position = center + radius * vec2f(std::sin(angle), std::cos(angle));
      vertices[i + 1].color = color;
    }

    draw(&vertices[0], POINT_COUNT + 2, GL_TRIANGLE_FAN);
  }

  void renderer::draw_circle(vec2f center, float radius, color4f color) {
    static constexpr int POINT_COUNT = 50;
    static constexpr float PI = 3.14159265359f;

    vertex vertices[POINT_COUNT];

    for (int i = 0; i < POINT_COUNT; ++i) {
      float angle = 2 * PI * i / POINT_COUNT;
      vertices[i].position = center + radius * vec2f(std::sin(angle), std::cos(angle));
      vertices[i].color = color;
    }

    draw(&vertices[0], POINT_COUNT, GL_LINE_LOOP);
  }


  void renderer::display() {
    SDL_GL_SwapWindow(m_window);
  }

  mat3f renderer::get_view_matrix() const {
    mat3f scaling(
      2.0f / m_view_size.x, 0.0f,                   0.0f,
      0.0f,                 - 2.0f / m_view_size.y, 0.0f,
      0.0f,                 0.0f,                   1.0f
    );

    mat3f translation(
      1.0f, 0.0f, - m_view_center.x,
      0.0f, 1.0f, - m_view_center.y,
      0.0f, 0.0f, 1.0f
    );

    return scaling * translation;
  }

  void renderer::draw(const vertex *vertices, std::size_t count, int primitive) {
    // set viewport

    vec2i size = get_size();
    glViewport(0, 0, size.width, size.height);

    // set transformation matrix

    mat3f transform = get_view_matrix();

    GLint loc = glGetUniformLocation(m_program, "u_transform");

    if (loc == -1) {
      std::cerr << "Uniform not found" << std::endl;
      return;
    }

    glUniformMatrix3fv(loc, 1, GL_FALSE, &transform.data[0][0]);

    // send data

    glUseProgram(m_program);

    GLint position_loc = glGetAttribLocation(m_program, "a_position");

    if (loc == -1) {
      std::cerr << "Attribute not found: a_position" << std::endl;
      return;
    }

    GLint color_loc = glGetAttribLocation(m_program, "a_color");

    if (loc == -1) {
      std::cerr << "Attribute not found: a_color" << std::endl;
      return;
    }

    glEnableVertexAttribArray(position_loc);
    glEnableVertexAttribArray(color_loc);

    const void *position_pointer = &vertices[0].position;
    const void *color_pointer = &vertices[0].color;

    glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), position_pointer);
    glVertexAttribPointer(color_loc, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), color_pointer);

    glDrawArrays(primitive, 0, count);

    glDisableVertexAttribArray(position_loc);
    glDisableVertexAttribArray(color_loc);
  }

}
