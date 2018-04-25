#ifndef HMI_BITS_WINDOW_EVENTS_H
#define HMI_BITS_WINDOW_EVENTS_H

#include <variant>

#include "vec.h"

namespace hmi {

  enum class keyboard_keycode {
    // TODO
  };

  enum class keyboard_scancode {
    // TODO
  };

  enum class keyboard_modifiers { // BitmakType
    none      = 0b0000,
    alt       = 0b0001,
    control   = 0b0010,
    shift     = 0b0100,
    super     = 0b1000,
  };

  constexpr keyboard_modifiers operator&(keyboard_modifiers lhs, keyboard_modifiers rhs) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<keyboard_modifiers>(static_cast<U>(lhs) & static_cast<U>(rhs));
  }

  constexpr keyboard_modifiers operator|(keyboard_modifiers lhs, keyboard_modifiers rhs) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<keyboard_modifiers>(static_cast<U>(lhs) | static_cast<U>(rhs));
  }

  constexpr keyboard_modifiers operator^(keyboard_modifiers lhs, keyboard_modifiers rhs) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<keyboard_modifiers>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
  }

  constexpr keyboard_modifiers operator~(keyboard_modifiers flags) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<keyboard_modifiers>(~ static_cast<U>(flags));
  }

  constexpr keyboard_modifiers& operator&=(keyboard_modifiers& lhs, keyboard_modifiers rhs) {
    return lhs = lhs & rhs;
  }

  constexpr keyboard_modifiers& operator|=(keyboard_modifiers& lhs, keyboard_modifiers rhs) {
    return lhs = lhs | rhs;
  }

  constexpr keyboard_modifiers& operator^=(keyboard_modifiers& lhs, keyboard_modifiers rhs) {
    return lhs = lhs ^ rhs;
  }

  constexpr bool operator==(keyboard_modifiers lhs, keyboard_modifiers rhs) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<U>(lhs) == static_cast<U>(rhs);
  }

  constexpr bool operator!=(keyboard_modifiers lhs, keyboard_modifiers rhs) {
    using U = std::underlying_type_t<keyboard_modifiers>;
    return static_cast<U>(lhs) != static_cast<U>(rhs);
  }

  enum class mouse_button {
    left,
    middle,
    right,
    x1,
    x2,
    other,
  };

  namespace window_events {

    struct resized {
      vec2i size;
    };

    struct closed {

    };

    struct focus_gained {

    };

    struct focus_lost {

    };

    struct keyboard_event_data {
      keyboard_keycode keycode;
      keyboard_scancode scancode;
      keyboard_modifiers modifiers;
    };

    struct keyboard_key_pressed : keyboard_event_data {

    };

    struct keyboard_key_repeated : keyboard_event_data {

    };

    struct keyboard_key_released : keyboard_event_data {

    };

    struct mouse_button_data {
      mouse_button button;
      vec2i position;
    };

    struct mouse_button_pressed : mouse_button_data {

    };

    struct mouse_button_released : mouse_button_data {

    };

    struct mouse_moved {
      vec2i position;
    };

    struct mouse_wheel_scrolled {
      vec2i offset;
    };

    struct mouse_entered {

    };

    struct mouse_left {

    };

  }

  using window_event = std::variant<
    window_events::resized,
    window_events::closed,
    window_events::focus_gained,
    window_events::focus_lost,
    window_events::keyboard_key_pressed,
    window_events::keyboard_key_repeated,
    window_events::keyboard_key_released,
    window_events::mouse_button_pressed,
    window_events::mouse_button_released,
    window_events::mouse_moved,
    window_events::mouse_wheel_scrolled,
    window_events::mouse_entered,
    window_events::mouse_left
  >;



}

#endif // HMI_BITS_WINDOW_EVENTS_H
