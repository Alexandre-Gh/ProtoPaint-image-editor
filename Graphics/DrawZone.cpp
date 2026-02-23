/*
** ProtoPaint
** File description:
** DrawZone
*/

#include "DrawZone.hpp"
#include <algorithm>

Graphic::DrawZone::DrawZone(unsigned int w, unsigned int h)
{
    this->_zone.create(w, h);
    this->_displayer.setOrigin(0, 0);
    this->_zone.clear(GlobalData.getSecondColor());
    this->_displayer.setTexture(this->_zone.getTexture(), true);
    this->setSize(w, h);
    this->fill({0, 0}, sf::Color::Transparent);
}

Graphic::DrawZone::DrawZone(const Graphic::DrawZone& other)
{
    this->_zone.create(other._size.x, other._size.y);
    this->_zone.clear(sf::Color::Transparent);
    this->setSize(other._size.x, other._size.y);
    this->addSprite(other._displayer);
    this->_size = other._size;
    this->_displayer = other._displayer;
    this->_displayer.setTexture(this->_zone.getTexture(), true);
}

Graphic::DrawZone::~DrawZone()
{

}

const sf::Sprite &Graphic::DrawZone::getSprite()
{
    return this->_displayer;
}

const sf::RenderTexture &Graphic::DrawZone::getRenderTexture()
{
    return this->_zone;
}


void Graphic::DrawZone::setPixel(sf::Vector2f pos, sf::Color color)
{
    sf::RectangleShape pixel({1, 1});
    pixel.setPosition(pos);
    pixel.setOrigin(0.5f, 0.5f);
    pixel.setFillColor(color);
    this->_zone.draw(pixel);
}

void Graphic::DrawZone::setFromFile(std::string filepath)
{
    sf::Texture fileText;
    if (fileText.loadFromFile(filepath)) {
        GlobalData.setCanvasSize(fileText.getSize().x, fileText.getSize().y);
        this->setSize(fileText.getSize().x, fileText.getSize().y);
        this->_zone.draw(sf::Sprite(fileText));
    }
}

void Graphic::DrawZone::addFromFile(std::string filepath)
{
    sf::Texture fileText;
    if (fileText.loadFromFile(filepath)) {
        this->_zone.draw(sf::Sprite(fileText));
    }
}

void Graphic::DrawZone::saveToFile(std::string filepath)
{
    sf::Image im = this->_zone.getTexture().copyToImage();
    im.saveToFile(filepath);
}

const sf::Color &Graphic::DrawZone::getPixel(sf::Vector2f pos)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    const sf::Color &targetColor = image.getPixel(pos.x, pos.y);

    return targetColor;
}

void Graphic::DrawZone::addDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable);
}

void Graphic::DrawZone::setDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable, sf::BlendNone);
}

void Graphic::DrawZone::addSprite(const sf::Sprite &spr)
{
    this->_zone.draw(sf::Sprite(*spr.getTexture()));
}

void Graphic::DrawZone::fill(sf::Vector2f pos, sf::Color color)
{
    sf::Image image = this->_zone.getTexture().copyToImage();

    sf::Color targetColor = image.getPixel(pos.x, pos.y);
    if (targetColor == color) {
        return;
    }

    std::stack<sf::Vector2i> pixels;
    pixels.push(sf::Vector2i(pos.x, pos.y));
    sf::Vector2u imSize = image.getSize();

    while (!pixels.empty()) {
        sf::Vector2i p = pixels.top();
        pixels.pop();

        if (p.x < 0 || p.x >= imSize.x || p.y < 0 || p.y >= imSize.y)
            continue;

        if (image.getPixel(p.x, p.y) != targetColor)
            continue;

        image.setPixel(p.x, p.y, color);

        pixels.push(sf::Vector2i(p.x + 1, p.y));
        pixels.push(sf::Vector2i(p.x - 1, p.y));
        pixels.push(sf::Vector2i(p.x, p.y + 1));
        pixels.push(sf::Vector2i(p.x, p.y - 1));
    }
    sf::Texture final;
    final.loadFromImage(image);
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}

void Graphic::DrawZone::drawCheckeredBackground() {
    sf::Color lightGray(200, 200, 200);
    sf::Color darkGray(150, 150, 150);


    int squareSize = this->_size.x / 20;
    if (squareSize < 1) {
        return;
    }

    for (int x = 0; x < this->_size.x; x += squareSize) {
        for (int y = 0; y < this->_size.y; y += squareSize) {
            sf::Color color = ((x / squareSize) % 2 == (y / squareSize) % 2) ? lightGray : darkGray;

            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setFillColor(color);
            square.setPosition(x, y);
            this->_zone.draw(square);
        }
    }
}


void Graphic::DrawZone::setPosition(int x, int y)
{
    this->_displayer.setPosition(x, y);
}

const sf::Vector2f &Graphic::DrawZone::getPosition()
{
    return this->_displayer.getPosition();
}

sf::Vector2f Graphic::DrawZone::getRelatedPosition(sf::Vector2f pos)
{
    return this->getSprite().getInverseTransform().transformPoint(pos);
}

bool Graphic::DrawZone::isInZone(sf::Vector2f pos)
{
    return this->getSprite().getGlobalBounds().contains(pos);
}

void Graphic::DrawZone::setSize(unsigned int w, unsigned int h, bool content)
{
    // Store the old size
    sf::Vector2u oldSize = this->_zone.getSize();

    // Create a temporary RenderTexture to hold the old content
    sf::RenderTexture tempZone;
    tempZone.create(oldSize.x, oldSize.y);
    tempZone.clear(sf::Color::Transparent);

    // Draw the old content to the temporary RenderTexture
    sf::Sprite oldSpr(this->_zone.getTexture());
    tempZone.draw(oldSpr);
    tempZone.display();

    // Create a new RenderTexture with the new size
    this->_zone.create(w, h);
    this->_zone.clear(sf::Color::Transparent);

    // Create a sprite from the temporary RenderTexture and scale it to the new size
    sf::Sprite newSpr(tempZone.getTexture());
    if (content) {
        newSpr.setScale(static_cast<float>(w) / oldSize.x, static_cast<float>(h) / oldSize.y);
    }
    this->_zone.draw(newSpr);


    // Finalize the drawing
    this->_zone.display();

    // Update the displayer with the new texture
    this->_displayer.setTexture(this->_zone.getTexture(), true);

    // Update the size member variable
    this->_size.x = w;
    this->_size.y = h;
}

void Graphic::DrawZone::flip(bool vertical)
{
    sf::Texture texture = this->_zone.getTexture();
    this->_zone.clear(sf::Color::Transparent);
    sf::Sprite sprite(texture);
    sf::Transform flip;
    if (vertical) {
        flip.scale(1, -1);
        flip.translate(0, -(this->_size.y));
    } else {
        flip.scale(-1, 1);
        flip.translate(-(this->_size.x), 0);
    }
    this->_zone.draw(sprite, flip);
}

void Graphic::DrawZone::setSize(sf::Vector2f size, bool content)
{
    this->setSize(size.x, size.y, content);
}

const sf::Vector2f &Graphic::DrawZone::getSize()
{
    return this->_size;
}

void Graphic::DrawZone::clear()
{
    this->_zone.clear(sf::Color::Transparent);
}

void Graphic::DrawZone::rotate(float angle)
{
    sf::Texture texture = this->_zone.getTexture();
    this->_zone.clear(sf::Color::Transparent);
    sf::Sprite sprite(texture);
    sprite.setOrigin(this->_size.x / 2, this->_size.y / 2);
    sprite.setRotation(angle);
    if (angle == 90 || angle == 270) {
        this->setSize(this->_size.y, this->_size.x);
    }
    sf::Transform rot;
    rot.rotate(angle, this->_size.x / 2, this->_size.y / 2);
    sprite.setPosition(this->_size.x / 2, this->_size.y / 2);
    this->_zone.draw(sprite);
}

void Graphic::DrawZone::reset(int w, int h)
{
    this->_zone.create(w, h);
    this->_displayer.setOrigin(0, 0);
    this->_zone.clear(GlobalData.getSecondColor());
    this->_displayer.setTexture(this->_zone.getTexture(), true);
    this->setSize(w, h);
    this->fill({0, 0}, sf::Color::Transparent);
}

void Graphic::DrawZone::invert()
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    sf::Color color;

    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            color = image.getPixel(x, y);

            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;

            image.setPixel(x, y, color);
        }
    }
    sf::Texture final;
    final.loadFromImage(image);
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}


void Graphic::DrawZone::changeLighting(float f)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    sf::Color color;
    float factor;

    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            color = image.getPixel(x, y);

            float factor = f / 10.0f;  // Normalized to a range from -1.0 to 1.0

            color.r = static_cast<sf::Uint8>(std::clamp(color.r + (color.r) * factor, 0.0f, 255.0f));
            color.g = static_cast<sf::Uint8>(std::clamp(color.g + (color.g) * factor, 0.0f, 255.0f));
            color.b = static_cast<sf::Uint8>(std::clamp(color.b + (color.b) * factor, 0.0f, 255.0f));

            image.setPixel(x, y, color);
        }
    }
    sf::Texture final;
    final.loadFromImage(image);
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}

void Graphic::DrawZone::changeContrast(float f)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    sf::Color color;
    float factor = f / 10.0f;  // Normalize the factor (range -1 to 1)
    const float midpoint = 128.0f;  // Midpoint for contrast calculation

    // Adjust contrast for each pixel
    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            color = image.getPixel(x, y);

            // Adjust contrast for each channel using the corrected formula
            color.r = static_cast<sf::Uint8>(std::clamp(midpoint + (color.r - midpoint) * (1 + factor), 0.0f, 255.0f));
            color.g = static_cast<sf::Uint8>(std::clamp(midpoint + (color.g - midpoint) * (1 + factor), 0.0f, 255.0f));
            color.b = static_cast<sf::Uint8>(std::clamp(midpoint + (color.b - midpoint) * (1 + factor), 0.0f, 255.0f));

            image.setPixel(x, y, color);
        }
    }

    // Create a new texture from the modified image
    sf::Texture final;
    final.loadFromImage(image);

    // Clear the previous content and draw the new adjusted image
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}

void Graphic::DrawZone::castShadows(float strength, float orientationX, float orientationY)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    sf::Color color;

    // Normalize the shadow strength
    float shadowStrength = std::clamp(strength, 0.0f, 10.0f);

    // Calculate direction of shadow based on the light orientation
    int dx = static_cast<int>(orientationX * 10);  // Horizontal offset (right/left)
    int dy = static_cast<int>(orientationY * 10);  // Vertical offset (up/down)

    // Loop through every pixel and apply shadows
    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            color = image.getPixel(x, y);

            // If the pixel has color (non-transparent)
            if (color.a > 0) {
                int shadowX = x + dx;
                int shadowY = y + dy;

                // Only apply the shadow if it's within the bounds of the image
                if (shadowX >= 0 && shadowX < image.getSize().x && shadowY >= 0 && shadowY < image.getSize().y) {
                    // Get the existing pixel color at the shadow location
                    sf::Color shadowPixel = image.getPixel(shadowX, shadowY);

                    // Only apply shadow if the shadow pixel is transparent
                    if (shadowPixel.a == 0) {
                        // Darken the color for the shadow pixel
                        int shadowAlpha = static_cast<int>(color.a * shadowStrength / 10.0f);
                        shadowAlpha = std::max(0, shadowAlpha);  // Ensure non-negative alpha value
                        
                        sf::Color shadowColor(
                            static_cast<sf::Uint8>(color.r),
                            static_cast<sf::Uint8>(color.g),
                            static_cast<sf::Uint8>(color.b),
                            static_cast<sf::Uint8>(shadowAlpha)
                        );

                        // Apply shadow color to the target position (the shadow pixel)
                        image.setPixel(shadowX, shadowY, shadowColor);
                    }
                }
            }
        }
    }

    // Create a new texture from the shadowed image
    sf::Texture final;
    final.loadFromImage(image);

    // Clear the previous content and draw the image with shadows
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}

void Graphic::DrawZone::castLightAtPoint(float strength, unsigned int lightX, unsigned int lightY)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    sf::Color color;

    // Loop through every pixel and apply lighting
    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            color = image.getPixel(x, y);

            // Calculate the distance from the light source (lightX, lightY)
            float dx = static_cast<float>(x - lightX);
            float dy = static_cast<float>(y - lightY);
            float distance = std::sqrt(dx * dx + dy * dy);  // Euclidean distance, works in all directions

            // Calculate the intensity of the light at this distance
            // The intensity should diminish as the distance increases
            float intensity = std::max(0.0f, 1.0f - (distance / strength)); // Light intensity diminishes with distance

            // Apply the light intensity to the pixel color
            int newR = static_cast<int>(color.r + (255 - color.r) * intensity);  // Increase towards white (255)
            int newG = static_cast<int>(color.g + (255 - color.g) * intensity);
            int newB = static_cast<int>(color.b + (255 - color.b) * intensity);

            // Clamp values to the 0-255 range
            newR = std::clamp(newR, 0, 255);
            newG = std::clamp(newG, 0, 255);
            newB = std::clamp(newB, 0, 255);

            // Set the new color at the pixel position
            sf::Color newColor(newR, newG, newB, color.a);
            image.setPixel(x, y, newColor);
        }
    }

    // Create a new texture from the illuminated image
    sf::Texture final;
    final.loadFromImage(image);

    // Clear the previous content and draw the image with lighting effect
    this->_zone.clear(sf::Color::Transparent);
    this->_zone.draw(sf::Sprite(final));
}
