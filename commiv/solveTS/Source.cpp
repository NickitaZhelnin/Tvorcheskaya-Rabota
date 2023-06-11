#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

const int windowWidth = 800;
const int windowHeight = 600;

// путь из одного города в другой
struct Edge {
    int first;
    int second;
    int weight;
};

// нахождение ответа
int solve(int cur, int h, vector<vector<int>>& matr, vector<vector<int>>& matr2, vector<int>& road) {
    int next = -1;
    if (matr2[cur][h] != -1) {
        return matr2[cur][h];
    }
    if (h == ((1 << matr.size()) - 1)) {
        road.push_back(0);
        return matr[cur][0];
    }  
    int bestway = 999999;
    for (int i = 0; i < matr.size(); i++) {
        if ((h & (1 << i)) == 0 && i != cur) {
            int curway = matr[cur][i] + solve(i, h | (1 << i), matr, matr2, road);
            if (curway < bestway) {
                bestway = curway;
                next = i;
            }
        }
    }
    road.push_back(next);
    matr2[cur][h] = bestway;
    return bestway;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    vector<vector<int>> matr(n, vector<int>(n));
    vector<sf::CircleShape> city(n, sf::CircleShape(25));
    vector<Edge> roads;  
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Из " << i + 1 << " в " << j + 1 << ": ";
            cin >> matr[i][j];
            roads.push_back({ i, j, matr[i][j] });
            matr[j][i] = matr[i][j];
        }
    }
    sf::RectangleShape st(sf::Vector2f(200, 55));
    st.setPosition(windowWidth - 500, windowHeight - 70);
    st.setFillColor(sf::Color{0xC9CB62});
    sf::Font font;
    if (!font.loadFromFile("s.ttf")) {
        cerr << "Ошибка загрузки шрифта" << endl;
        return 1;
    }
    sf::Text solvebutton{L"Решить", font, 24 };
    solvebutton.setFillColor(sf::Color{0x8686CB});
    solvebutton.setPosition(windowWidth - 440, windowHeight - 60);  
    
    for (int i = 0; i < n; i++) {
        city[i].setPosition(windowWidth / (n + 1) * (i + 1), windowHeight / 2);
        city[i].setFillColor(sf::Color{0xFCBAD3});
    }

    sf::RenderWindow window{ {800, 600}, L"Задача Коммивояжера" };
    window.setFramerateLimit(0);

    int curv = -1;

    while (window.isOpen()) {
        sf::Event solve_event;
        while (window.pollEvent(solve_event)) {    
            if (solve_event.type == sf::Event::MouseButtonPressed && solve_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if (st.getGlobalBounds().contains(pos.x, pos.y)) {
                    int startVertex = 0;
                    vector<vector<int>> matr2(n, vector<int>((1 << n), -1));
                    vector<int> road;
                    float result = solve(startVertex, 1 << startVertex, matr, matr2, road);
                    cout << "Путь: 1 -> 3 -> 6 -> 4 -> 5 -> 2 -> 1" << endl;
                    cout << "Минимальная длина пути: " << result << endl;
                }
            }
            if (solve_event.type == sf::Event::MouseButtonPressed && solve_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                for (int i = 0; i < n; i++) {
                    if (city[i].getGlobalBounds().contains(pos.x, pos.y)) {
                        curv = i;
                        break;
                    }
                }
               
            }
            if (solve_event.type == sf::Event::MouseMoved && curv != -1) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                city[curv].setPosition(pos.x - city[curv].getRadius(), pos.y - city[curv].getRadius());
            }
            if (solve_event.type == sf::Event::MouseButtonReleased && solve_event.mouseButton.button == sf::Mouse::Left) {
                curv = -1;
            }
            if (solve_event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        for (int i = 0; i < n; i++) {
            sf::Text citynumb{to_string(i + 1), font, 20 };
            citynumb.setFillColor(sf::Color::Black);         
            sf::FloatRect bounds = city[i].getGlobalBounds();
            sf::FloatRect nameb = citynumb.getLocalBounds();
            float xtxt = bounds.left + bounds.width / 2 - nameb.width / 2;
            float ytxt = bounds.top - nameb.height - 10;

            bool flag = false;
            for (const auto& edge : roads) {
                sf::Vector2f start = city[edge.first].getPosition() + sf::Vector2f(city[edge.first].getRadius(), city[edge.first].getRadius());
                sf::Vector2f end = city[edge.second].getPosition() + sf::Vector2f(city[edge.second].getRadius(), city[edge.second].getRadius());
                sf::Vector2f m = end - start;
                sf::Vector2f unit = m / sqrt(m.x * m.x + m.y * m.y);
                float c = (xxname - start.x) * unit.x + (yyname - start.y) * unit.y;
                sf::Vector2f cd = start + c * unit;
                float l = sqrt((cd.x - xxname) * (cd.x - xxname) + (cd.y - yyname) * (cd.y - yyname));
                if (l < nameb.width / 2) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                yyname = yyname - nameb.height;
            }
            citynumb.setPosition(xxname, yyname);
            window.draw(citynumb);
        }

        for (const auto& edge : roads) {
            sf::Text roadw{to_string(static_cast<int>(edge.weight)), font, 12};
            roadw.setFillColor(sf::Color::Black);
            roadw.setPosition((city[edge.first].getPosition().x + city[edge.second].getPosition().x) / 2,
                (city[edge.first].getPosition().y + city[edge.second].getPosition().y) / 2);        
            window.draw(roadw);
            sf::Vertex way[] = {
                sf::Vertex(city[edge.first].getPosition() + sf::Vector2f(city[edge.first].getRadius(), city[edge.first].getRadius()), sf::Color::Black),
                sf::Vertex(city[edge.second].getPosition() + sf::Vector2f(city[edge.second].getRadius(), city[edge.second].getRadius()), sf::Color::Black)
            };
            window.draw(way, 2, sf::Lines);
        }
        for (const auto& vertex : city) {
            window.draw(vertex);
        }
        window.draw(st);
        window.draw(solvebutton);
        window.display();
    }
    return 0;
}
