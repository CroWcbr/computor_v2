# include "../include/draw_curve.hpp"

static double _ft_abs_rat(double const tmp) { return tmp < 0 ? -1 * tmp : tmp; }

void draw(std::vector<double> &x, std::vector<double> &y)
{
	int		width = 800;
	int		height = width;
	float	x_min = x.front();
	float	x_max = x.back();
	float	y_max = y[0];
	float	y_min;
	for (auto i : y)
		if (_ft_abs_rat(i) > y_max)
			y_max = _ft_abs_rat(i);
	y_min = -y_max;

	sf::RenderWindow window(sf::VideoMode(width, height), "Graph");
	sf::View view(sf::FloatRect(x_min, y_min, x_max - x_min, y_max - y_min));
	window.setView(view);

	sf::VertexArray graph(sf::LinesStrip);
	graph.setPrimitiveType(sf::LinesStrip);
	graph.resize(x.size());

	double y_scale = view.getSize().y / (y_max - y_min);
	for (size_t i = 0; i < x.size(); i++)
	{
		graph[i].position = sf::Vector2f(x[i], -y[i] * y_scale);
		graph[i].color = sf::Color::Green;
	}
	sf::VertexArray axes(sf::Lines);
	axes.append(sf::Vertex(sf::Vector2f(x_min, 0), sf::Color::Black));
	axes.append(sf::Vertex(sf::Vector2f(x_max, 0), sf::Color::Black));
	axes.append(sf::Vertex(sf::Vector2f(0, y_min), sf::Color::Black));
	axes.append(sf::Vertex(sf::Vector2f(0, y_max), sf::Color::Black));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color::White);
		window.draw(graph);
		window.draw(axes);
		window.display();
	}
}
