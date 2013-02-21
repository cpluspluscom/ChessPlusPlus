////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Err.hpp>
#include <cmath>


namespace
{
    // Compute the normal of a segment
    sf::Vector2f computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
        float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        if (length != 0.f)
            normal /= length;
        return normal;
    }
}


namespace sf
{
////////////////////////////////////////////////////////////
Shape::~Shape()
{
}


////////////////////////////////////////////////////////////
void Shape::setTexture(const Texture* texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no texture before
    if (texture && (resetRect || !m_texture))
        setTextureRect(IntRect(0, 0, texture->getSize().x, texture->getSize().y));

    // Assign the new texture
    m_texture = texture;
}


////////////////////////////////////////////////////////////
const Texture* Shape::getTexture() const
{
    return m_texture;
}


////////////////////////////////////////////////////////////
void Shape::setTextureRect(const IntRect& rect)
{
    m_textureRect = rect;
    updateTexCoords();
}


////////////////////////////////////////////////////////////
const IntRect& Shape::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
void Shape::setFillColor(const Color& color)
{
    m_fillColor = color;
    updateFillColors();
}


////////////////////////////////////////////////////////////
const Color& Shape::getFillColor() const
{
    return m_fillColor;
}


////////////////////////////////////////////////////////////
void Shape::setOutlineColor(const Color& color)
{
    m_outlineColor = color;
    updateOutlineColors();
}


////////////////////////////////////////////////////////////
const Color& Shape::getOutlineColor() const
{
    return m_outlineColor;
}


////////////////////////////////////////////////////////////
void Shape::setOutlineThickness(float thickness)
{
    m_outlineThickness = thickness;
    update(); // recompute everything because the whole shape must be offset
}


////////////////////////////////////////////////////////////
float Shape::getOutlineThickness() const
{
    return m_outlineThickness;
}


////////////////////////////////////////////////////////////
FloatRect Shape::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
FloatRect Shape::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
Shape::Shape() :
m_texture         (NULL),
m_textureRect     (),
m_fillColor       (255, 255, 255),
m_outlineColor    (255, 255, 255),
m_outlineThickness(0),
m_vertices        (TrianglesFan),
m_outlineVertices (TrianglesStrip),
m_insideBounds    (),
m_bounds          ()
{
}


////////////////////////////////////////////////////////////
void Shape::update()
{
    // Get the total number of points of the shape
    unsigned int count = getPointCount();
    if (count < 3)
    {
        m_vertices.resize(0);
        m_outlineVertices.resize(0);
        return;
    }

    m_vertices.resize(count + 2); // + 2 for center and repeated first point

    // Position
    for (unsigned int i = 0; i < count; ++i)
        m_vertices[i + 1].position = getPoint(i);
    m_vertices[count + 1].position = m_vertices[1].position;

    // Update the bounding rectangle
    m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
    m_insideBounds = m_vertices.getBounds();

    // Compute the center and make it the first vertex
    m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
    m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;

    // Color
    updateFillColors();

    // Texture coordinates
    updateTexCoords();

    // Outline
    updateOutline();
}


////////////////////////////////////////////////////////////
void Shape::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();

    // Render the inside
    states.texture = m_texture;
    target.draw(m_vertices, states);

    // Render the outline
    if (m_outlineThickness != 0)
    {
        states.texture = NULL;
        target.draw(m_outlineVertices, states);
    }
}


////////////////////////////////////////////////////////////
void Shape::updateFillColors()
{
    for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
        m_vertices[i].color = m_fillColor;
}


////////////////////////////////////////////////////////////
void Shape::updateTexCoords()
{
    for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
    {
        float xratio = (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width;
        float yratio = (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height;
        m_vertices[i].texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
        m_vertices[i].texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
    }
}


////////////////////////////////////////////////////////////
void Shape::updateOutline()
{
    unsigned int count = m_vertices.getVertexCount() - 2;
    m_outlineVertices.resize((count + 1) * 2);

    for (unsigned int i = 0; i < count; ++i)
    {
        unsigned int index = i + 1;

        // Get the two segments shared by the current point
        Vector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
        Vector2f p1 = m_vertices[index].position;
        Vector2f p2 = m_vertices[index + 1].position;

        // Compute their normal
        Vector2f n1 = computeNormal(p0, p1);
        Vector2f n2 = computeNormal(p1, p2);

        // Combine them to get the extrusion direction
        float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
        Vector2f normal = -(n1 + n2) / factor;

        // Update the outline points
        m_outlineVertices[i * 2 + 0].position = p1;
        m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
    }

    // Duplicate the first point at the end, to close the outline
    m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
    m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

    // Update outline colors
    updateOutlineColors();

    // Update the shape's bounds
    m_bounds = m_outlineVertices.getBounds();
}


////////////////////////////////////////////////////////////
void Shape::updateOutlineColors()
{
    for (unsigned int i = 0; i < m_outlineVertices.getVertexCount(); ++i)
        m_outlineVertices[i].color = m_outlineColor;
}

} // namespace sf
