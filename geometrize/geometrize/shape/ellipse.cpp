#include "ellipse.h"

#include <cstdint>
#include <memory>
#include <sstream>

#include "shape.h"
#include "../model.h"
#include "../commonutil.h"

namespace geometrize
{

Ellipse::Ellipse(const geometrize::Model& model) : m_model{model}
{
    const std::int32_t xBound{m_model.getWidth()};
    const std::int32_t yBound{m_model.getHeight()};

    m_x = commonutil::randomRange(0, xBound - 1);
    m_y = commonutil::randomRange(0, yBound - 1);
    m_rx = commonutil::randomRange(0, commonutil::randomRange(0, 32) + 1);
    m_ry = commonutil::randomRange(0, commonutil::randomRange(0, 32) + 1);
}

std::shared_ptr<geometrize::Shape> Ellipse::clone() const
{
    std::shared_ptr<geometrize::Ellipse> ellipse{std::make_shared<geometrize::Ellipse>(m_model)};
    ellipse->m_x = m_x;
    ellipse->m_y = m_y;
    ellipse->m_rx = m_rx;
    ellipse->m_ry = m_ry;
    return ellipse;
}

std::vector<geometrize::Scanline> Ellipse::rasterize() const
{
    std::vector<geometrize::Scanline> lines;

    const float aspect{static_cast<float>(m_rx) / static_cast<float>(m_ry)};

    const std::int32_t w{m_model.getWidth()};
    const std::int32_t h{m_model.getHeight()};

    for (std::int32_t dy = 0; dy < m_ry; dy++) {
        const std::int32_t y1{m_y - dy};
        const std::int32_t y2{m_y + dy};

        if ((y1 < 0 || y1 >= h) && (y2 < 0 || y2 >= h)) {
            continue;
        }

        const std::int32_t s{static_cast<std::int32_t>(std::sqrt(m_ry * m_ry - dy * dy) * aspect)};
        std::int32_t x1{m_x - s};
        std::int32_t x2{m_x + s};
        if (x1 < 0) {
            x1 = 0;
        }
        if (x2 >= w) {
            x2 = w - 1;
        }

        if (y1 >= 0 && y1 < h) {
            lines.push_back(Scanline(y1, x1, x2, 0xFFFF));
        }
        if (y2 >= 0 && y2 < h && dy > 0) {
            lines.push_back(Scanline(y2, x1, x2, 0xFFFF));
        }
    }

    return lines;
}

void Ellipse::mutate()
{
    const std::int32_t xBound{m_model.getWidth()};
    const std::int32_t yBound{m_model.getHeight()};

    const std::int32_t r{commonutil::randomRange(0, 2)};
    switch(r) {
        case 0:
        {
            m_x = commonutil::clamp(m_x + commonutil::randomRange(-16, 16), 0, xBound - 1);
            m_y = commonutil::clamp(m_y + commonutil::randomRange(-16, 16), 0, yBound - 1);
            break;
        }
        case 1:
        {
            m_rx = commonutil::clamp(m_rx + commonutil::randomRange(-16, 16), 1, xBound - 1);
            break;
        }
        case 2:
        {
            m_ry = commonutil::clamp(m_ry + commonutil::randomRange(-16, 16), 1, xBound - 1);
            break;
        }
    }
}

geometrize::shapes::ShapeTypes Ellipse::getType() const
{
    return geometrize::shapes::ShapeTypes::ELLIPSE;
}

std::vector<std::int32_t> Ellipse::getRawShapeData() const
{
    return { m_x, m_y, m_rx, m_ry };
}

std::string Ellipse::getSvgShapeData() const
{
    std::stringstream s;
    s << "<ellipse "
      << "cx=\"" << m_x << "\" "
      << "cy=\"" << m_y << "\" "
      << "rx=\"" << m_rx << "\" "
      << "ry=\"" << m_ry << "\" "
      << SVG_STYLE_HOOK << " "
      << "/>";

    return s.str();
}

}
