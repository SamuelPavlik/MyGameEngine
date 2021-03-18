#include "Window.hpp"

Window::Window(const std::string& windowName)
    : window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar) {
    window.setVerticalSyncEnabled(true);
}

void Window::Update() {
    sf::Event event;
    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Window::BeginDraw()
{
    window.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

void Window::EndDraw() {
    window.display();
}

bool Window::IsOpen() const {
    return window.isOpen();
}

sf::Vector2u Window::GetCentre() const {
    return window.getSize() / 2u;
}

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type) {
    window.draw(vertices, vertexCount, type);
}
