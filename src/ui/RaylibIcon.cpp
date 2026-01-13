#include "RaylibIcon.h"

namespace ymwm::ui::prv {
  struct RaylibImage {
    RaylibImage(const unsigned char* const raw_data,
                std::size_t icon_size,
                Color color)
        : m_img(LoadImageFromMemory(".png", raw_data, icon_size)) {

      ImageColorReplace(&m_img, BLACK, color);
    }

    inline const Image& handler() const noexcept { return m_img; }

    ~RaylibImage() { UnloadImage(m_img); }

  private:
    Image m_img;
  };

} // namespace ymwm::ui::prv

namespace ymwm::ui {
  RaylibIcon::RaylibIcon(const unsigned char* const raw_data,
                         std::size_t icon_size,
                         Color color) {
    prv::RaylibImage img(raw_data, icon_size, color);
    m_texture = LoadTextureFromImage(img.handler());
  }

  RaylibIcon::~RaylibIcon() { UnloadTexture(m_texture); }

} // namespace ymwm::ui
