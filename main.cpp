#include <SFML/Graphics.hpp>

#include <sstream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 400u, 400u }), "Test SFML PR #2519");
    window.setFramerateLimit(60);

    auto font = sf::Font();
    if (!font.loadFromFile("font.ttf"))
        throw std::runtime_error("Failed to load font");

    auto text = sf::Text(font, "", 24);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition({ 10, 5 });

    auto is_minimum_size_enforced = false;
    auto is_maximum_size_enforced = false;

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                window.setView(sf::View(sf::FloatRect(sf::Vector2f(), sf::Vector2f(event.size.width, event.size.height))));
                break;
            case sf::Event::KeyPressed:
                switch (event.key.scancode) {
                case sf::Keyboard::Scan::Q:
                    window.setMinimumSize(sf::Vector2u(400, 400));
                    is_minimum_size_enforced = true;
                    break;
                case sf::Keyboard::Scan::A:
                    window.setMinimumSize({});
                    is_minimum_size_enforced = false;
                    break;
                case sf::Keyboard::Scan::W:
                    window.setMaximumSize(sf::Vector2u(600, 600));
                    is_maximum_size_enforced = true;
                    break;
                case sf::Keyboard::Scan::S:
                    window.setMaximumSize({});
                    is_maximum_size_enforced = false;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        window.clear();

        auto text_builder = std::ostringstream();
        text_builder << "Controls:\n";
        text_builder << "\t" << getDescription(sf::Keyboard::Scan::Q).toAnsiString() << ": Set minimum size\n";
        text_builder << "\t" << getDescription(sf::Keyboard::Scan::A).toAnsiString() << ": Unset minimum size\n";
        text_builder << "\t" << getDescription(sf::Keyboard::Scan::W).toAnsiString() << ": Set maximum size\n";
        text_builder << "\t" << getDescription(sf::Keyboard::Scan::S).toAnsiString() << ": Unset maximum size\n";
        text_builder << "Minimum size ";
        if (!is_minimum_size_enforced)
            text_builder << "not ";
        text_builder << "enforced\n";
        text_builder << "Maximum size ";
        if (!is_maximum_size_enforced)
            text_builder << "not ";
        text_builder << "enforced\n";
        text_builder << "Window size: " << window.getSize().x << " x " << window.getSize().y;
        text.setString(text_builder.str());
        window.draw(text);

        window.display();
    }
}
