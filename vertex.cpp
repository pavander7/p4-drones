// 1761414855B69983BD8035097EFBD312EB0527F0

#include "vertex.h"

using namespace std;

bool Vertex::operator==(Vertex const &other) const { return ((this->x == other.x) && (this->y == other.y)); }
bool Vertex::operator!=(Vertex const &other) const { return ((this->x != other.x) || (this->y != other.y)); }
int Vertex::area()
{
    if (x < 0 && y < 0)
        return 2;
    else if ((x == 0 && y < 0) || (y == 0 && x < 0))
        return 1;
    else
        return 0;
}
uint64_t Vertex::pow_dist(Vertex const &other) const
{
    int X = this->x - other.x;
    int Y = this->y - other.y;
    uint64_t X2 = uint64_t(X)*uint64_t(X);
    uint64_t Y2 = uint64_t(Y)*uint64_t(Y);
    uint64_t result = (X2 + Y2);
    return result;
}
bool Vertex::operator<(Vertex const &other) const
{
    if ((this->x == other.x) && (this->y == other.y))
        return true;
    else if (this->x == other.x)
    {
        if (this->y == other.y)
            return true;
        else
            return (this->y < other.y);
    }
    else
        return (this->x < other.x);
}