#include "maths_utils.h"

const float MathsUtils::x(const vertex *v)
{
    return (*v)[0];
}

const float MathsUtils::y(const vertex *v)
{
    return (*v)[1];
}

const float MathsUtils::z(const vertex *v)
{
    return (*v)[2];
}

const float MathsUtils::r(const vertex *v)
{
    return (*v)[3];
}

const float MathsUtils::g(const vertex *v)
{
    return (*v)[4];
}

const float MathsUtils::b(const vertex *v)
{
    return (*v)[5];
}

const unsigned int MathsUtils::getNbVertex(const MathsUtils::vertex vertices[])
{
    return (unsigned int)(sizeof(*vertices) / MathsUtils::VERTEX_ELEMENTS_NB);
}

const unsigned int MathsUtils::getNbElements(const MathsUtils::vertex vertices[])
{
    return MathsUtils::getNbVertex(vertices) * VERTEX_ELEMENTS_NB;
}
