#include <bits/window.h>

#include <cassert>
#include <atomic>
#include <iostream>

#include <SDL.h>

namespace hmi {

  namespace {

    Uint32 compute_sdl_flags(window_flags hints) {
      Uint32 flags = SDL_WINDOW_OPENGL;

      if ((hints & window_flags::resizable) != window_flags::none) {
        flags |= SDL_WINDOW_RESIZABLE;
      }

      if ((hints & window_flags::visible) != window_flags::none) {
        flags |= SDL_WINDOW_SHOWN;
      } else {
        flags |= SDL_WINDOW_HIDDEN;
      }

      if ((hints & window_flags::decorated) == window_flags::none) {
        flags |= SDL_WINDOW_BORDERLESS;
      }

      return flags;
    }

    window_flags compute_window_flags(Uint32 flags) {
      window_flags res = window_flags::none;

      if ((flags & SDL_WINDOW_RESIZABLE) != 0) {
        res |= window_flags::resizable;
      }

      if ((flags & SDL_WINDOW_SHOWN) != 0) {
        res |= window_flags::visible;
      }

      if ((flags & SDL_WINDOW_BORDERLESS) == 0) {
        res |= window_flags::decorated;
      }

      return res;
    }

    mouse_button compute_mouse_button(Uint8 button) {
      switch (button) {
        case SDL_BUTTON_LEFT:
          return mouse_button::left;
        case SDL_BUTTON_MIDDLE:
          return mouse_button::middle;
        case SDL_BUTTON_RIGHT:
          return mouse_button::right;
        case SDL_BUTTON_X1:
          return mouse_button::x1;
        case SDL_BUTTON_X2:
          return mouse_button::x2;
      }

      return mouse_button::other;
    }


    keyboard_modifiers compute_keyboard_modifiers(Uint16 mod) {
      keyboard_modifiers modifiers = keyboard_modifiers::none;

      if ((mod & KMOD_SHIFT) != 0) {
        modifiers |= keyboard_modifiers::shift;
      }

      if ((mod & KMOD_CTRL) != 0) {
        modifiers |= keyboard_modifiers::control;
      }

      if ((mod & KMOD_ALT) != 0) {
        modifiers |= keyboard_modifiers::alt;
      }

      if ((mod & KMOD_GUI) != 0) {
        modifiers |= keyboard_modifiers::super;
      }

      return modifiers;
    }


    std::atomic_int g_loaded{0};
  }

  window::window(std::string_view title, vec2i size, window_flags hints)
  : m_window(nullptr)
  , m_should_close(false)
  {
    if (g_loaded.fetch_add(1) == 0) { // we are the first
      if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << '\n';
        return;
      }

      // must be set before window creating
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    }

    std::string title_string(title);
    auto flags = compute_sdl_flags(hints);
    m_window = SDL_CreateWindow(title_string.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.width, size.height, flags);

    if (m_window == nullptr) {
      std::cerr << "Unable to create window: " << SDL_GetError() << '\n';
      return;
    }
  }

  window::~window() {
    if (m_window != nullptr) {
      SDL_DestroyWindow(m_window);
    }

    if (g_loaded.fetch_sub(1) == 1) { // we are the last
      SDL_Quit();
    }
  }

  window::window(window&& other)
  : m_window(std::exchange(other.m_window, nullptr))
  , m_should_close(other.m_should_close)
  {
    g_loaded.fetch_add(1);
  }

  window& window::operator=(window&& other) {
    std::swap(m_window, other.m_window);
    std::swap(m_should_close, other.m_should_close);
    g_loaded.fetch_add(1);
    return *this;
  }

  // lifetime

  bool window::is_open() const {
    return !m_should_close;
  }

  void window::close() {
    m_should_close = true;
  }

  // properties

  std::string_view window::get_title() const {
    return SDL_GetWindowTitle(m_window);
  }

  void window::set_title(std::string_view title) {
    std::string title_string(title);
    SDL_SetWindowTitle(m_window, title_string.data());
  }

  vec2i window::get_position() const {
    vec2i position;
    SDL_GetWindowPosition(m_window, &position.x, &position.y);
    return position;
  }

  void window::set_position(vec2i position) {
    SDL_SetWindowPosition(m_window, position.x, position.y);
  }

  vec2i window::get_size() const {
    vec2i size;
    SDL_GetWindowSize(m_window, &size.width, &size.height);
    return size;
  }

  void window::set_size(vec2i size) {
    SDL_SetWindowSize(m_window, size.width, size.height);
  }

  window_flags window::get_flags() const {
    auto flags = SDL_GetWindowFlags(m_window);
    return compute_window_flags(flags);
  }

  void window::set_resizable(bool resizable) {
    SDL_SetWindowResizable(m_window, resizable ? SDL_TRUE : SDL_FALSE);
  }

  void window::set_visible(bool visible) {
    if (visible) {
      SDL_ShowWindow(m_window);
    } else {
      SDL_HideWindow(m_window);
    }
  }

  void window::set_decorated(bool decorated) {
    SDL_SetWindowBordered(m_window, decorated ? SDL_TRUE : SDL_FALSE);
  }

  void window::set_fullscreen(bool fullscreen) {
    if (fullscreen) {
      SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
      SDL_SetWindowFullscreen(m_window, 0);
    }
  }

  // state

  bool window::is_minimized() const {
    auto flags = SDL_GetWindowFlags(m_window);
    return (flags & SDL_WINDOW_MINIMIZED) != 0;
  }

  void window::minimize() {
    SDL_MinimizeWindow(m_window);
  }

  bool window::is_maximized() const {
    auto flags = SDL_GetWindowFlags(m_window);
    return (flags & SDL_WINDOW_MAXIMIZED) != 0;
  }

  void window::mazimize() {
    SDL_MaximizeWindow(m_window);
  }

  void window::restore() {
    SDL_RestoreWindow(m_window);
  }

  // events

  namespace {

    std::optional<window_event> translate_event(Uint32 window_id, const SDL_Event& event) {
      switch (event.type) {
        case SDL_WINDOWEVENT:
          if (window_id != event.window.windowID) {
            return std::nullopt;
          }

          switch (event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
              window_events::resized data;
              data.size.width = event.window.data1;
              data.size.height = event.window.data2;
              return data;
            }

            case SDL_WINDOWEVENT_CLOSE:
              return window_events::closed{};

            case SDL_WINDOWEVENT_FOCUS_GAINED:
              return window_events::focus_gained{};

            case SDL_WINDOWEVENT_FOCUS_LOST:
              return window_events::focus_lost{};

            case SDL_WINDOWEVENT_ENTER:
              return window_events::mouse_entered{};

            case SDL_WINDOWEVENT_LEAVE:
              return window_events::mouse_left{};

            default:
              return std::nullopt;
          }
          break;

        case SDL_QUIT:
          return window_events::closed{};

        case SDL_KEYDOWN:
          assert(event.key.state == SDL_PRESSED);

          if (event.key.repeat == 0) {
            window_events::keyboard_key_pressed data;
            data.keycode = static_cast<keyboard_keycode>(event.key.keysym.sym);
            data.scancode = static_cast<keyboard_scancode>(event.key.keysym.scancode);
            data.modifiers = compute_keyboard_modifiers(event.key.keysym.mod);
            return data;
          } else {
            window_events::keyboard_key_repeated data;
            data.keycode = static_cast<keyboard_keycode>(event.key.keysym.sym);
            data.scancode = static_cast<keyboard_scancode>(event.key.keysym.scancode);
            data.modifiers = compute_keyboard_modifiers(event.key.keysym.mod);
            return data;
          }

          break;

        case SDL_KEYUP: {
          assert(event.key.state == SDL_RELEASED);
          window_events::keyboard_key_released data;
          data.keycode = static_cast<keyboard_keycode>(event.key.keysym.sym);
          data.scancode = static_cast<keyboard_scancode>(event.key.keysym.scancode);
          data.modifiers = compute_keyboard_modifiers(event.key.keysym.mod);
          return data;
        }

        case SDL_MOUSEWHEEL: {
          if (event.wheel.which == SDL_TOUCH_MOUSEID) {
            return std::nullopt;
          }

          window_events::mouse_wheel_scrolled data;
          data.offset.x = event.wheel.x;
          data.offset.y = event.wheel.y;
          return data;
        }

        case SDL_MOUSEBUTTONDOWN: {
          assert(event.button.state == SDL_PRESSED);

          if (event.button.which == SDL_TOUCH_MOUSEID) {
            return std::nullopt;
          }

          window_events::mouse_button_pressed data;
          data.button = compute_mouse_button(event.button.button);
          data.position.x = event.button.x;
          data.position.y = event.button.y;
          return data;
        }

        case SDL_MOUSEBUTTONUP: {
          assert(event.button.state == SDL_RELEASED);

          if (event.button.which == SDL_TOUCH_MOUSEID) {
            return std::nullopt;
          }

          window_events::mouse_button_released data;
          data.button = compute_mouse_button(event.button.button);
          data.position.x = event.button.x;
          data.position.y = event.button.y;
          return data;
        }

        case SDL_MOUSEMOTION: {
          if (event.motion.which == SDL_TOUCH_MOUSEID) {
            return std::nullopt;
          }

          window_events::mouse_moved data;
          data.position.x = event.motion.x;
          data.position.y = event.motion.y;
          return data;
        }

        default:
          break;
      }

      return std::nullopt;
    }

  }

  std::optional<window_event> window::poll_event() {
    Uint32 window_id = SDL_GetWindowID(m_window);

    for (;;) {
      SDL_Event event;
      int status = SDL_PollEvent(&event);

      if (status == 0) {
        return std::nullopt;
      }

      std::optional<window_event> event_maybe = translate_event(window_id, event);

      if (event_maybe) {
        return event_maybe;
      }
    }
  }

  std::optional<window_event> window::wait_event() {
    Uint32 window_id = SDL_GetWindowID(m_window);

    for (;;) {
      SDL_Event event;
      int status = SDL_WaitEvent(&event);

      if (status == 0) {
        return std::nullopt;
      }

      std::optional<window_event> event_maybe = translate_event(window_id, event);

      if (event_maybe) {
        return event_maybe;
      }
    }
  }

  // renderer

  renderer window::get_renderer() {
    return renderer(m_window);
  }

} // namespace hmi
