#include <cstdlib>
#include <cstring>

#include <geometry>
#include <window>

static const char *g_hello_text[] = {
  "# # ### #   #   ###      ##             #   # ### ##  #   ## ",
  "# # #   #   #   # #     #    #   #      #   # # # # # #   # #",
  "### ##  #   #   # #     #   ### ###     # # # # # ##  #   # #",
  "# # #   #   #   # #     #    #   #      # # # # # # # #   # #",
  "# # ### ### ### ###      ##              ###  ### # # ### ## ",
};

int main() {
  hmi::window window("Beman's challenge", { 1024, 576 });

  auto renderer = window.get_renderer();

  hmi::vec2i hello_size = { static_cast<int>(std::strlen(g_hello_text[0])), 5 };
  hmi::vec2f pixel_size = { 10.0f, 10.0f * 3 / 5 * 1.61803398875f };
  hmi::vec2f size = hello_size * pixel_size;

  hmi::vec2f position = (window.get_size() - size) / 2;
  bool dragging = false;
  hmi::vec2f mouse_position = { 0, 0 };

  while (window.is_open()) {

    while (auto maybe_event = window.poll_event()) {
      auto& event = maybe_event.value();

      if (std::get_if<hmi::window_events::closed>(&event)) {
        window.close();
      } else if (auto pevent = std::get_if<hmi::window_events::mouse_button_pressed>(&event)) {
        hmi::vec2f cursor = renderer.get_coords_from_position(pevent->position);

        if (position.x <= cursor.x && cursor.x <= position.x + size.width && position.y <= cursor.y && cursor.y <= position.y + size.height) {
          dragging = true;
          mouse_position = pevent->position;
        }
      } else if (std::get_if<hmi::window_events::mouse_button_released>(&event)) {
        dragging = false;
      } else if (auto pevent = std::get_if<hmi::window_events::mouse_moved>(&event)) {
        if (dragging) {
          hmi::vec2f old_cursor = renderer.get_coords_from_position(mouse_position);
          hmi::vec2f new_cursor = renderer.get_coords_from_position(pevent->position);
          position += (new_cursor - old_cursor);
        }

        mouse_position = pevent->position;
      } else if (auto pevent = std::get_if<hmi::window_events::resized>(&event)) {
        renderer.set_view_size(pevent->size);
      }

    }

    renderer.clear(hmi::color::white);

    hmi::vec2i index;

    for (index.y = 0; index.y < hello_size.height; index.y++) {
      for (index.x = 0; index.x < hello_size.width; ++index.x) {
        if (g_hello_text[index.y][index.x] == '#') {
          hmi::vec2f pixel_position = position + index * pixel_size;
          renderer.fill_rectangle(pixel_position, pixel_size, hmi::color::red);
        }
      }
    }

    renderer.display();
  }

  return 0;
}
