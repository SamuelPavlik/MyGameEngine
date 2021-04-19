#include "Debug.hpp"
#include "Window.hpp"

std::vector<sf::RectangleShape> Debug::rects = {};
std::vector<std::array<sf::Vertex, 2>> Debug::lines = {};

void Debug::Draw(Window& window) {
    for (const auto& r : rects) {
        window.Draw(r);
    }
    rects.clear();

    for (const auto& l : lines) {
        sf::Vertex line[2] = { l.at(0), l.at(1) };
        window.Draw(line, 2, sf::Lines);
    }
    lines.clear();
}

void Debug::DrawRect(const sf::FloatRect& rect, const sf::Color& colour) {
    sf::Vector2f size(rect.width, rect.height);
    sf::Vector2f pos(rect.left, rect.top);
    sf::RectangleShape shape(size);
    shape.setPosition(pos);
    shape.setOutlineColor(colour);
    shape.setOutlineThickness(3.f);
    shape.setFillColor(sf::Color::Transparent);
    rects.push_back(shape);
}

void Debug::DrawLine(const sf::Vector2f& from,
    const sf::Vector2f& to, const sf::Color& colour) {
    lines.push_back({ sf::Vertex(from, colour), sf::Vertex(to, colour) });
}

void Debug::Log(const std::string& msg) {
    std::cout << msg << std::endl;
}

void Debug::LogWarning(const std::string& msg) {
    std::cout << "WARNING: " << msg << std::endl;
}

void Debug::LogError(const std::string& msg) {
    std::cout << "ERROR: " << msg << std::endl;
}