# include "../include/main_library.hpp"

void draw()
{
	std::cout << "need to read about SFML" << std::endl;
}

// const int WINDOW_WIDTH = 800;
// const int WINDOW_HEIGHT = 600;

// const float X_MIN = -10.f;
// const float X_MAX = 10.f;
// const float Y_MIN = -1.f;
// const float Y_MAX = 1.f;

// const int NUM_POINTS = 200;

// float f(float x)
// {
//     return std::sin(x);
// }

// void draw()
// {
//     // Создаем окно размером 800x600 пикселей
//     sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Window");

//     // Создаем массив вершин
//     sf::VertexArray curve(sf::LineStrip, NUM_POINTS);

//     // Заполняем массив вершин
//     float x_step = (X_MAX - X_MIN) / (NUM_POINTS - 1);
//     for (int i = 0; i < NUM_POINTS; i++)
//     {
//         float x = X_MIN + i * x_step;
//         float y = f(x);

//         // Преобразуем координаты в пиксели
//         float x_pixels = (x - X_MIN) / (X_MAX - X_MIN) * WINDOW_WIDTH;
//         float y_pixels = (y - Y_MIN) / (Y_MAX - Y_MIN) * WINDOW_HEIGHT;

//         curve[i].position = sf::Vector2f(x_pixels, y_pixels);
//         curve[i].color = sf::Color::White;
//     }

//     // Цикл отображения окна
//     while (window.isOpen())
//     {
//         // Обрабатываем события в цикле
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // Закрываем окно при нажатии на кнопку "закрыть"
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // Очищаем экран черным цветом
//         window.clear(sf::Color::Black);

//         // Рисуем кривую на экране
//         window.draw(curve);

//         // Отображаем нарисованное на экране
//         window.display();
//     }
// 	// sf::Context::destroy(window);
// }
