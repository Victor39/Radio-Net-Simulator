#include <math.h>
#include "point2d.h"


Point2D::Point2D(int32_t x, int32_t y) : m_x(x), m_y(y)
{

}

const int32_t &Point2D::x() const
{
    return m_x;
}

int32_t &Point2D::x()
{
    return m_x;
}

const int32_t &Point2D::y() const
{
    return m_y;
}

int32_t &Point2D::y()
{
    return m_y;
}

uint32_t Point2D::distance(const Point2D &point) const
{
    return static_cast<uint32_t>(sqrt((m_x - point.x())*(m_x - point.x()) + (m_y - point.y())*(m_y - point.y())));
}
