#ifndef HMI_BITS_WINDOW_H
#define HMI_BITS_WINDOW_H

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "renderer.h"
#include "vec.h"
#include "window_events.h"

struct SDL_Window; // implementation detail

namespace hmi {

  enum class window_flags { // BitmakType
    none        = 0b0000,
    resizable   = 0b0001,
    visible     = 0b0010,
    decorated   = 0b0100,
    fullscreen  = 0b1000,
  };

  constexpr window_flags operator&(window_flags lhs, window_flags rhs) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(static_cast<U>(lhs) & static_cast<U>(rhs));
  }

  constexpr window_flags operator|(window_flags lhs, window_flags rhs) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(static_cast<U>(lhs) | static_cast<U>(rhs));
  }

  constexpr window_flags operator^(window_flags lhs, window_flags rhs) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
  }

  constexpr window_flags operator~(window_flags flags) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<window_flags>(~ static_cast<U>(flags));
  }

  constexpr window_flags& operator&=(window_flags& lhs, window_flags rhs) {
    return lhs = lhs & rhs;
  }

  constexpr window_flags& operator|=(window_flags& lhs, window_flags rhs) {
    return lhs = lhs | rhs;
  }

  constexpr window_flags& operator^=(window_flags& lhs, window_flags rhs) {
    return lhs = lhs ^ rhs;
  }

  constexpr bool operator==(window_flags lhs, window_flags rhs) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<U>(lhs) == static_cast<U>(rhs);
  }

  constexpr bool operator!=(window_flags lhs, window_flags rhs) {
    using U = std::underlying_type_t<window_flags>;
    return static_cast<U>(lhs) != static_cast<U>(rhs);
  }

  inline constexpr window_flags default_window_flags = window_flags::resizable | window_flags::visible | window_flags::decorated;

  class window {
  public:
    window(std::string_view title, vec2i size, window_flags hints = default_window_flags);

    ~window();

    window(const window&) = delete;

    window& operator=(const window&) = delete;

    window(window&& other);

    window& operator=(window&& other);

    // lifetime

    bool is_open() const;

    void close();

    // properties

    std::string_view get_title() const;

    void set_title(std::string_view title);

    vec2i get_position() const;

    void set_position(vec2i position);

    vec2i get_size() const;

    void set_size(vec2i size);

    window_flags get_flags() const;

    void set_resizable(bool resizable = true);

    void set_visible(bool visible = true);

    void set_decorated(bool decorated = true);

    void set_fullscreen(bool fullscreen = true);

    // state

    bool is_minimized() const;

    void minimize();

    bool is_maximized() const;

    void mazimize();

    void restore();

    // events

    std::optional<window_event> poll_event();

    std::optional<window_event> wait_event();

    // renderer

    renderer get_renderer();

  private:
    SDL_Window *m_window;
    bool m_should_close;
  };


}

#endif // HMI_BITS_WINDOW_H
