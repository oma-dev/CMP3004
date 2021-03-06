#pragma once

#include "City.hpp"

#include <SFML/Graphics.hpp>
#include <fmt/format.hpp>
#include <vector>

class Program final
{
public:
	Program(const char* filename_of_city_data = "../data/cities.txt",
			const uint16_t win_width = 1280U,
			const uint16_t win_height = 900U);
	~Program();

	void setBackground(const sf::Color);
	bool run();

	sf::RenderWindow& window() { return m_window; }
	const sf::RenderWindow& window() const { return m_window; }

	std::vector<City>& cities() { return m_cities; }
	const std::vector<City>& cities() const { return m_cities; }

	const sf::Vector2<uint16_t>& topLeft() const { return m_top_left; }
	const sf::Vector2<uint16_t>& bottomRight() const { return m_bottom_right; }

	sf::VertexArray& vertexArray() { return m_vertex_array; }
	const sf::VertexArray& vertexArray() const { return m_vertex_array; }

	sf::VertexArray& vertexArray2() { return m_vertex_array_2; }
	const sf::VertexArray& vertexArray2() const { return m_vertex_array_2; }

private:
	void handleBackground();

	sf::RenderWindow m_window;
	sf::Color m_background_color;
	sf::Texture m_background_texture;
	sf::Sprite m_background_sprite;
	sf::VertexArray m_vertex_array;
	sf::VertexArray m_vertex_array_2;

	std::vector<City> m_cities;

	sf::Vector2<uint16_t> m_top_left {65534U, 65534U};
	sf::Vector2<uint16_t> m_bottom_right {0U, 0U};
};
