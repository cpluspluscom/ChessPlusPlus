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
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/Err.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include <cstdlib>
#include <cstring>


namespace
{
    // FreeType callbacks that operate on a sf::InputStream
    unsigned long read(FT_Stream rec, unsigned long offset, unsigned char* buffer, unsigned long count)
    {
        sf::InputStream* stream = static_cast<sf::InputStream*>(rec->descriptor.pointer);
        if (static_cast<unsigned long>(stream->seek(offset)) == offset)
        {
            if (count > 0)
                return static_cast<unsigned long>(stream->read(reinterpret_cast<char*>(buffer), count));
            else
                return 0;
        }
        else
            return count > 0 ? 0 : 1; // error code is 0 if we're reading, or nonzero if we're seeking
    }
    void close(FT_Stream)
    {
    }
}


namespace sf
{
////////////////////////////////////////////////////////////
Font::Font() :
m_library  (NULL),
m_face     (NULL),
m_streamRec(NULL),
m_refCount (NULL)
{

}


////////////////////////////////////////////////////////////
Font::Font(const Font& copy) :
m_library    (copy.m_library),
m_face       (copy.m_face),
m_streamRec  (copy.m_streamRec),
m_refCount   (copy.m_refCount),
m_pages      (copy.m_pages),
m_pixelBuffer(copy.m_pixelBuffer)
{
    // Note: as FreeType doesn't provide functions for copying/cloning,
    // we must share all the FreeType pointers

    if (m_refCount)
        (*m_refCount)++;
}


////////////////////////////////////////////////////////////
Font::~Font()
{
    cleanup();
}


////////////////////////////////////////////////////////////
bool Font::loadFromFile(const std::string& filename)
{
    // Cleanup the previous resources
    cleanup();
    m_refCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        err() << "Failed to load font \"" << filename << "\" (failed to initialize FreeType)" << std::endl;
        return false;
    }
    m_library = library;

    // Load the new font face from the specified file
    FT_Face face;
    if (FT_New_Face(static_cast<FT_Library>(m_library), filename.c_str(), 0, &face) != 0)
    {
        err() << "Failed to load font \"" << filename << "\" (failed to create the font face)" << std::endl;
        return false;
    }

    // Select the unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        err() << "Failed to load font \"" << filename << "\" (failed to set the Unicode character set)" << std::endl;
        return false;
    }

    // Store the loaded font in our ugly void* :)
    m_face = face;

    return true;
}


////////////////////////////////////////////////////////////
bool Font::loadFromMemory(const void* data, std::size_t sizeInBytes)
{
    // Cleanup the previous resources
    cleanup();
    m_refCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        err() << "Failed to load font from memory (failed to initialize FreeType)" << std::endl;
        return false;
    }
    m_library = library;

    // Load the new font face from the specified file
    FT_Face face;
    if (FT_New_Memory_Face(static_cast<FT_Library>(m_library), reinterpret_cast<const FT_Byte*>(data), static_cast<FT_Long>(sizeInBytes), 0, &face) != 0)
    {
        err() << "Failed to load font from memory (failed to create the font face)" << std::endl;
        return false;
    }

    // Select the unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        err() << "Failed to load font from memory (failed to set the Unicode character set)" << std::endl;
        return false;
    }

    // Store the loaded font in our ugly void* :)
    m_face = face;

    return true;
}


////////////////////////////////////////////////////////////
bool Font::loadFromStream(InputStream& stream)
{
    // Cleanup the previous resources
    cleanup();
    m_refCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        err() << "Failed to load font from stream (failed to initialize FreeType)" << std::endl;
        return false;
    }
    m_library = library;

    // Prepare a wrapper for our stream, that we'll pass to FreeType callbacks
    FT_StreamRec* rec = new FT_StreamRec;
    std::memset(rec, 0, sizeof(*rec));
    rec->base               = NULL;
    rec->size               = static_cast<unsigned long>(stream.getSize());
    rec->pos                = 0;
    rec->descriptor.pointer = &stream;
    rec->read               = &read;
    rec->close              = &close;

    // Setup the FreeType callbacks that will read our stream
    FT_Open_Args args;
    args.flags  = FT_OPEN_STREAM;
    args.stream = rec;
    args.driver = 0;

    // Load the new font face from the specified stream
    FT_Face face;
    if (FT_Open_Face(static_cast<FT_Library>(m_library), &args, 0, &face) != 0)
    {
        err() << "Failed to load font from stream (failed to create the font face)" << std::endl;
        return false;
    }

    // Select the unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        err() << "Failed to load font from stream (failed to set the Unicode character set)" << std::endl;
        return false;
    }

    // Store the loaded font in our ugly void* :)
    m_face = face;
    m_streamRec = rec;

    return true;
}


////////////////////////////////////////////////////////////
const Glyph& Font::getGlyph(Uint32 codePoint, unsigned int characterSize, bool bold) const
{
    // Get the page corresponding to the character size
    GlyphTable& glyphs = m_pages[characterSize].glyphs;

    // Build the key by combining the code point and the bold flag
    Uint32 key = ((bold ? 1 : 0) << 31) | codePoint;

    // Search the glyph into the cache
    GlyphTable::const_iterator it = glyphs.find(key);
    if (it != glyphs.end())
    {
        // Found: just return it
        return it->second;
    }
    else
    {
        // Not found: we have to load it
        Glyph glyph = loadGlyph(codePoint, characterSize, bold);
        return glyphs.insert(std::make_pair(key, glyph)).first->second;
    }
}


////////////////////////////////////////////////////////////
int Font::getKerning(Uint32 first, Uint32 second, unsigned int characterSize) const
{
    // Special case where first or second is 0 (null character)
    if (first == 0 || second == 0)
        return 0;

    FT_Face face = static_cast<FT_Face>(m_face);

    if (face && FT_HAS_KERNING(face) && setCurrentSize(characterSize))
    {
        // Convert the characters to indices
        FT_UInt index1 = FT_Get_Char_Index(face, first);
        FT_UInt index2 = FT_Get_Char_Index(face, second);

        // Get the kerning vector
        FT_Vector kerning;
        FT_Get_Kerning(face, index1, index2, FT_KERNING_DEFAULT, &kerning);

        // Return the X advance
        return kerning.x >> 6;
    }
    else
    {
        // Invalid font, or no kerning
        return 0;
    }
}


////////////////////////////////////////////////////////////
int Font::getLineSpacing(unsigned int characterSize) const
{
    FT_Face face = static_cast<FT_Face>(m_face);

    if (face && setCurrentSize(characterSize))
    {
        return (face->size->metrics.height >> 6);
    }
    else
    {
        return 0;
    }
}


////////////////////////////////////////////////////////////
const Texture& Font::getTexture(unsigned int characterSize) const
{
    return m_pages[characterSize].texture;
}


////////////////////////////////////////////////////////////
Font& Font::operator =(const Font& right)
{
    Font temp(right);

    std::swap(m_library,     temp.m_library);
    std::swap(m_face,        temp.m_face);
    std::swap(m_pages,       temp.m_pages);
    std::swap(m_pixelBuffer, temp.m_pixelBuffer);
    std::swap(m_refCount,    temp.m_refCount);

    return *this;
}


////////////////////////////////////////////////////////////
void Font::cleanup()
{
    // Check if we must destroy the FreeType pointers
    if (m_refCount)
    {
        // Decrease the reference counter
        (*m_refCount)--;

        // Free the resources only if we are the last owner
        if (*m_refCount == 0)
        {
            // Delete the reference counter
            delete m_refCount;

            // Destroy the font face
            if (m_face)
                FT_Done_Face(static_cast<FT_Face>(m_face));

            // Destroy the stream rec instance, if any (must be done after FT_Done_Face!)
            if (m_streamRec)
                delete static_cast<FT_StreamRec*>(m_streamRec);

            // Close the library
            if (m_library)
                FT_Done_FreeType(static_cast<FT_Library>(m_library));
        }
    }

    // Reset members
    m_library   = NULL;
    m_face      = NULL;
    m_streamRec = NULL;
    m_refCount  = NULL;
    m_pages.clear();
    m_pixelBuffer.clear();
}


////////////////////////////////////////////////////////////
Glyph Font::loadGlyph(Uint32 codePoint, unsigned int characterSize, bool bold) const
{
    // The glyph to return
    Glyph glyph;

    // First, transform our ugly void* to a FT_Face
    FT_Face face = static_cast<FT_Face>(m_face);
    if (!face)
        return glyph;

    // Set the character size
    if (!setCurrentSize(characterSize))
        return glyph;

    // Load the glyph corresponding to the code point
    if (FT_Load_Char(face, codePoint, FT_LOAD_TARGET_NORMAL) != 0)
        return glyph;

    // Retrieve the glyph
    FT_Glyph glyphDesc;
    if (FT_Get_Glyph(face->glyph, &glyphDesc) != 0)
        return glyph;

    // Apply bold if necessary -- first technique using outline (highest quality)
    FT_Pos weight = 1 << 6;
    bool outline = (glyphDesc->format == FT_GLYPH_FORMAT_OUTLINE);
    if (bold && outline)
    {
        FT_OutlineGlyph outlineGlyph = (FT_OutlineGlyph)glyphDesc;
        FT_Outline_Embolden(&outlineGlyph->outline, weight);
    }

    // Convert the glyph to a bitmap (i.e. rasterize it)
    FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyphDesc;
    FT_Bitmap& bitmap = bitmapGlyph->bitmap;

    // Apply bold if necessary -- fallback technique using bitmap (lower quality)
    if (bold && !outline)
    {
        FT_Bitmap_Embolden(static_cast<FT_Library>(m_library), &bitmap, weight, weight);
    }

    // Compute the glyph's advance offset
    glyph.advance = glyphDesc->advance.x >> 16;
    if (bold)
        glyph.advance += weight >> 6;

    int width  = bitmap.width;
    int height = bitmap.rows;
    if ((width > 0) && (height > 0))
    {
        // Leave a small padding around characters, so that filtering doesn't
        // pollute them with pixels from neighbours
        const unsigned int padding = 1;

        // Get the glyphs page corresponding to the character size
        Page& page = m_pages[characterSize];

        // Find a good position for the new glyph into the texture
        glyph.textureRect = findGlyphRect(page, width + 2 * padding, height + 2 * padding);

        // Compute the glyph's bounding box
        glyph.bounds.left   = bitmapGlyph->left - padding;
        glyph.bounds.top    = -bitmapGlyph->top - padding;
        glyph.bounds.width  = width + 2 * padding;
        glyph.bounds.height = height + 2 * padding;

        // Extract the glyph's pixels from the bitmap
        m_pixelBuffer.resize(width * height * 4, 255);
        const Uint8* pixels = bitmap.buffer;
        if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
        {
            // Pixels are 1 bit monochrome values
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = (x + y * width) * 4 + 3;
                    m_pixelBuffer[index] = ((pixels[x / 8]) & (1 << (7 - (x % 8)))) ? 255 : 0;
                }
                pixels += bitmap.pitch;
            }
        }
        else
        {
            // Pixels are 8 bits gray levels
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = (x + y * width) * 4 + 3;
                    m_pixelBuffer[index] = pixels[x];
                }
                pixels += bitmap.pitch;
            }
        }

        // Write the pixels to the texture
        unsigned int x = glyph.textureRect.left + padding;
        unsigned int y = glyph.textureRect.top + padding;
        unsigned int w = glyph.textureRect.width - 2 * padding;
        unsigned int h = glyph.textureRect.height - 2 * padding;
        page.texture.update(&m_pixelBuffer[0], w, h, x, y);
    }

    // Delete the FT glyph
    FT_Done_Glyph(glyphDesc);

    // Done :)
    return glyph;
}


////////////////////////////////////////////////////////////
IntRect Font::findGlyphRect(Page& page, unsigned int width, unsigned int height) const
{
    // Find the line that fits well the glyph
    Row* row = NULL;
    float bestRatio = 0;
    for (std::vector<Row>::iterator it = page.rows.begin(); it != page.rows.end() && !row; ++it)
    {
        float ratio = static_cast<float>(height) / it->height;

        // Ignore rows that are either too small or too high
        if ((ratio < 0.7f) || (ratio > 1.f))
            continue;

        // Check if there's enough horizontal space left in the row
        if (width > page.texture.getSize().x - it->width)
            continue;

        // Make sure that this new row is the best found so far
        if (ratio < bestRatio)
            continue;

        // The current row passed all the tests: we can select it
        row = &*it;
        bestRatio = ratio;
    }

    // If we didn't find a matching row, create a new one (10% taller than the glyph)
    if (!row)
    {
        int rowHeight = height + height / 10;
        while (page.nextRow + rowHeight >= page.texture.getSize().y)
        {
            // Not enough space: resize the texture if possible
            unsigned int textureWidth  = page.texture.getSize().x;
            unsigned int textureHeight = page.texture.getSize().y;
            if ((textureWidth * 2 <= Texture::getMaximumSize()) && (textureHeight * 2 <= Texture::getMaximumSize()))
            {
                // Make the texture 2 times bigger
                Image newImage;
                newImage.create(textureWidth * 2, textureHeight * 2, Color(255, 255, 255, 0));
                newImage.copy(page.texture.copyToImage(), 0, 0);
                page.texture.loadFromImage(newImage);
            }
            else
            {
                // Oops, we've reached the maximum texture size...
                err() << "Failed to add a new character to the font: the maximum texture size has been reached" << std::endl;
                return IntRect(0, 0, 2, 2);
            }
        }

        // We can now create the new row
        page.rows.push_back(Row(page.nextRow, rowHeight));
        page.nextRow += rowHeight;
        row = &page.rows.back();
    }

    // Find the glyph's rectangle on the selected row
    IntRect rect(row->width, row->top, width, height);

    // Update the row informations
    row->width += width;

    return rect;
}


////////////////////////////////////////////////////////////
bool Font::setCurrentSize(unsigned int characterSize) const
{
    // FT_Set_Pixel_Sizes is an expensive function, so we must call it
    // only when necessary to avoid killing performances

    FT_Face face = static_cast<FT_Face>(m_face);
    FT_UShort currentSize = face->size->metrics.x_ppem;

    if (currentSize != characterSize)
    {
        return FT_Set_Pixel_Sizes(face, 0, characterSize) == 0;
    }
    else
    {
        return true;
    }
}


////////////////////////////////////////////////////////////
Font::Page::Page() :
nextRow(2)
{
    // Make sure that the texture is initialized by default
    sf::Image image;
    image.create(128, 128, Color(255, 255, 255, 0));

    // Reserve a 2x2 white square for texturing underlines
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            image.setPixel(x, y, Color(255, 255, 255, 255));

    // Create the texture
    texture.loadFromImage(image);
    texture.setSmooth(true);
}

} // namespace sf
