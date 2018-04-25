#include <cstdlib>
#include <cstring>
#include <iostream>

#include <geometry>
#include <window>

int main() {
  constexpr float object_size = 200.0f;
  constexpr float object_padding = 50.0f;

  hmi::window window("Features", { 1024, 576 });

  auto renderer = window.get_renderer();

  while (window.is_open()) {

    while (auto maybe_event = window.poll_event()) {
      auto& event = maybe_event.value();

      if (std::get_if<hmi::window_events::closed>(&event)) {
        window.close();
      }

    }

    renderer.clear(hmi::color::white);

    renderer.fill_rectangle({ object_padding, object_padding }, { object_size, object_size }, hmi::color::orange);

    renderer.draw_rectangle({ object_size + 2 * object_padding, object_padding }, { object_size, object_size }, hmi::color::cyan);

    renderer.fill_circle({ object_padding + 0.5f * object_size, 1.5f * object_size + 2 * object_padding }, 0.5f * object_size, hmi::color::azure);

    renderer.draw_circle({ 1.5 * object_size + 2 * object_padding, 1.5f * object_size + 2 * object_padding }, 0.5f * object_size, hmi::color::magenta);

    renderer.display();
  }

  return 0;
}

