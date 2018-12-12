#ifndef POINT2D_H
#define POINT2D_H

#include <stdint.h>

class Point2D
{
public:
    Point2D(int32_t x, int32_t y);

    const int32_t & x() const;
    int32_t & x();
    const int32_t & y() const;
    int32_t & y();

    uint32_t distance(const Point2D & point) const;

private:
    int32_t m_x;
    int32_t m_y;
};

#endif // POINT2D_H
