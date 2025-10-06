#include "Configuration.h"
#include "Modules/Anime/AnimeModule.h"
#include "Modules/Anime/Components/Timer.h"
#include "Modules/Anime/Easing.h"
#include "SFE/GameService.h"
#include "SFE/Modules/Render/Components/RectangleRenderable.h"
#include "SFE/Modules/Render/Components/ZOrder.h"
#include "SFE/Modules/Render/RenderModule.h"

#include <SFE/Modules/Render/Components/CircleRenderable.h>
#include <SFE/Modules/Render/Components/Transform.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <flecs.h>
#include <tracy/Tracy.hpp>

int main()
{
    // --- Tracy Integration ---
    ZoneScoped;

    // --- Create the window mode ---
    const sf::VideoMode mode(Configuration::RESOLUTION);

    // --- Enable anti-aliasing ---
    sf::ContextSettings settings;
    settings.antiAliasingLevel = Configuration::ANTI_ALIASING_LEVEL;

    // --- Create the window ---
    auto window = sf::RenderWindow(mode, Configuration::WINDOW_TITLE, Configuration::WINDOW_STYLE, Configuration::WINDOW_STATE, settings);

    // --- Configure the window ---
    window.setFramerateLimit(Configuration::FRAMERATE_LIMIT);
    window.setVerticalSyncEnabled(Configuration::IS_VSYNC);
    window.setKeyRepeatEnabled(Configuration::ENABLE_KEY_REPEAT);

    // --- Initialize the Game Service Locator ---
    GameService::Initialize();
    GameService::Register<sf::RenderWindow>(window);

    // --- The Only One and Unique Flecs World ---
    flecs::world world;

    // --- Import all the modules needed ---
    world.import <Modules::AnimeModule>();
    world.import <Core::Modules::RenderModule>();

    // circle with 100-pixel radius, green fill
    const auto triangle = world.entity().set<CircleRenderable>({}).set<Transform>({.position = {20.f, 20.f}}).set<ZOrder>({1});
    auto& shape = triangle.get_mut<CircleRenderable>().shape;
    shape.setRadius(5.f);
    shape.setPointCount(3);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({5.f, 5.f});
    triangle.set<Anime::Timer>({.loop = true, .onUpdate = [](const flecs::entity e, const Anime::Timer&) {
                                    e.get_mut<Transform>().rotation += 180.f * e.world().delta_time();
                                }});

    // Animated square for testing
    const auto square = world.entity()
                            .set<RectangleRenderable>({})
                            .set<Transform>(
                                {.position = {Configuration::WINDOW_SIZE.x / 2.f - 250.f, Configuration::WINDOW_SIZE.y / 2.f}}
                            )
                            .set<ZOrder>({2});
    auto& rect = square.get_mut<RectangleRenderable>().shape;
    rect.setOrigin({50.f, 50.f});
    square.set<Anime::Timer>(
        {.duration = 1.f,
         .loop = true,
         .alternate = true,
         .onUpdate =
             [](const flecs::entity e, const Anime::Timer& timer) {
                 const float t = timer.elapsed / timer.duration;
                 const float easedT = Anime::Easing::elasticOut(t);

                 // Calculate the easing from the initial position
                 const float startX = Configuration::WINDOW_SIZE.x / 2.f - 250.f;
                                  
                 e.get_mut<Transform>().position.x = timer.reverse 
                                      ? startX + (1.0f - easedT) * 500.f 
                                      : startX + easedT * 500.f;
             }}
    );

    sf::Clock clock;
    while (window.isOpen())
    {
        const float elapsed = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        world.progress(elapsed);
        window.display();
    }

    return 0;
}
