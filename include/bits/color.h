#ifndef HMI_BITS_COLOR_H
#define HMI_BITS_COLOR_H

#include "vec.h"

namespace hmi {

  namespace color {

    inline constexpr color4f white(1.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr color4f black(0.0f, 0.0f, 0.0f, 1.0f);

    inline constexpr color4f red(1.0f, 0.0f, 0.0f, 1.0f);
    inline constexpr color4f green(0.0f, 1.0f, 0.0f, 1.0f);
    inline constexpr color4f blue(0.0f, 0.0f, 1.0f, 1.0f);

    inline constexpr color4f cyan(0.0f, 1.0f, 1.0f, 1.0f);
    inline constexpr color4f magenta(1.0f, 0.0f, 1.0f, 1.0f);
    inline constexpr color4f yellow(1.0f, 1.0f, 0.0f, 1.0f);

    inline constexpr color4f orange(1.0f, 0.5f, 0.0f, 1.0f);
    inline constexpr color4f rose(1.0f, 0.0f, 0.5f, 1.0f);
    inline constexpr color4f chartreuse(0.5f, 1.0f, 0.0f, 1.0f);
    inline constexpr color4f spring(0.0f, 1.0f, 0.5f, 1.0f);
    inline constexpr color4f violet(0.5f, 0.0f, 1.0f, 1.0f);
    inline constexpr color4f azure(0.0f, 0.5f, 1.0f, 1.0f);

  }

}


#endif // HMI_BITS_COLOR_H
