#ifndef _MATHS_UTILS_H
#define _MATHS_UTILS_H

namespace MathsUtils
{

    const unsigned int VERTEX_ELEMENTS_NB = 6;

    /**
     * @brief Reassemble all elements of a vertex in a dedicated type
     * Contains, in the following order: x, y, z (position, in 3D), r, g, b (RGB colors)
     */
    typedef float vertex[VERTEX_ELEMENTS_NB];

    /**
     * @brief Returns the x position accessor in a 3 dimensional vector
     *
     * @param v - the vertex array
     * @return The x position
     */
    const float x(const vertex *v);

    /**
     * @brief Returns the y position accessor in a 3 dimensional vector
     *
     * @param v - the vertex array
     * @return The y position
     */
    const float y(const vertex *v);

    /**
     * @brief Returns the z position accessor in a 3 dimensional vector
     *
     * @param v - the vertex array
     * @return The z position
     */
    const float z(const vertex *v);

    /**
     * @brief Returns the red (in RGB) color accessor
     *
     * @param v - the vertex array
     * @return The red (in RGB) color accessor
     */
    const float r(const vertex *v);

    /**
     * @brief Returns the green (in RGB) color accessor
     *
     * @param v - the vertex array
     * @return The green (in RGB) color accessor
     */
    const float g(const vertex *v);

    /**
     * @brief Returns the blue (in RGB) color accessor
     *
     * @param v - the vertex array
     * @return The blue (in RGB) color accessor
     */
    const float b(const vertex *v);

    /**
     * @brief Returns the number of individual vertex arrays inside a vertices array
     *
     * @param vertices - an array of vertex
     * @return The number of the individual vertex arrays
     */
    const unsigned int getNbVertex(const vertex vertices[]);

    /**
     * @brief Sums and returns the number of individual elements stored in the vertices array
     *
     * @param vertices - an array of vertex
     * @return The sum of all individual elements stored in the vertices array
     */
    const unsigned int getNbElements(const vertex vertices[]);

}

#endif
