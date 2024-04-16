// 1761414855B69983BD8035097EFBD312EB0527F0

#include "vertex.h"

using namespace std;

bool Vertex::operator==(Vertex const &other) const { return (this->i == other.i); }
bool Vertex::operator!=(Vertex const &other) const { return (this->i != other.i); }
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
uint64_t Vertex::insert_dist(Vertex const &before, Vertex const &after) const
{
    uint64_t dist1 = before.pow_dist(after);
    uint64_t dist2 = this->pow_dist(before) + this->pow_dist(after);
    return (dist2 - dist1);
}
bool Vertex::operator<(Vertex const &other) const
{
    if (this->i == other.i)
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
bool VertexComp::operator()(const Vertex &a, const Vertex &b) const
{
    if (a.i == b.i)
        return true;
    else if (a.x == b.x)
    {
        if (a.y == b.y)
            return true;
        else
            return (a.y < b.y);
    }
    else
        return (a.x < b.x);
}