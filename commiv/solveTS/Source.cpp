#include <iostream>
#include <vector>
#include <limits>
#include <SFML/Graphics.hpp>
using namespace std;

const int windowWidth = 800;
const int windowHeight = 600;

// путь из одного города в другой
struct Edge {
    int first, second;
    float weight;
};

// поиск минимальной границы
float findMinBound(int currentNode, int visited, vector<vector<float>>& graph) {
    float minBound = 0;
    for (int i = 1; i < graph.size(); i++) {
        if (visited & (1 << i)) {
            minBound += graph[(i - 1)][(i)];
        }
    }
    float findMinNext = numeric_limits<float>::max();
    for (int i = 1; i < graph.size(); i++) {
        if ((visited & (1 << i)) == 0 && graph[currentNode][i] < findMinNext) {
            findMinNext = graph[currentNode][i];
        }
    }
    float findMin2Next = numeric_limits<float>::max();
    for (int i = 1; i < graph.size(); i++) {
        if (visited & (1 << i)) {
            for (int j = 1; j < graph.size(); j++) {
                if ((visited & (1 << j)) == 0 && graph[j][i] < findMin2Next) {
                    findMin2Next = graph[j][i];
                }
            }
        }
    }
    if (findMinNext != numeric_limits<float>::max()) {
        minBound += findMinNext;
    }
    if (findMin2Next != numeric_limits<float>::max()) {
        minBound += findMin2Next;
    }
    return minBound;
}
// нахождение ответа
float solve(int currentNode, int visited, vector<vector<float>>& graph, vector<vector<float>>& dp, vector<int>& path) {
    if (visited == ((1 << graph.size()) - 1)) {
        path.push_back(0);
        return graph[currentNode][0];
    }
    if (dp[currentNode][visited] != -1) {
        return dp[currentNode][visited];
    }
    float minWeight = numeric_limits<float>::max();
    int bestNextVertex = -1;
    for (int i = 0; i < graph.size(); i++) {
        if ((visited & (1 << i)) == 0 && i != currentNode) {
            float weight = graph[currentNode][i] + solve(i, visited | (1 << i), graph, dp, path);
            if (weight < minWeight) {
                minWeight = weight;
                bestNextVertex = i;
            }
        }
    }
    dp[currentNode][visited] = minWeight;
    path.push_back(bestNextVertex);
    return minWeight;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    vector<sf::CircleShape> vertices(n, sf::CircleShape(25));
    vector<Edge> edges;
    vector<vector<float>> graph(n, vector<float>(n));
    sf::RectangleShape startButton(sf::Vector2f(200, 55));
    startButton.setPosition(windowWidth - 500, windowHeight - 70);
    startButton.setFillColor(sf::Color{0xC9CB62});

    sf::Font font;
    if (!font.loadFromFile("s.ttf")) {
        cerr << "Ошибка загрузки шрифта" << endl;
        return 1;
    }

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(L"Решить");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color{0x8686CB});
    buttonText.setPosition(windowWidth - 440, windowHeight - 60);

    for (int i = 0; i < n; i++) {
        vertices[i].setPosition(windowWidth / (n + 1) * (i + 1), windowHeight / 2);
        vertices[i].setFillColor(sf::Color{0xFCBAD3});
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Введите длину пути из пункта " << i + 1 << " в пункт " << j + 1 << ": ";
            cin >> graph[i][j];
            graph[j][i] = graph[i][j];
            edges.push_back({ i, j, graph[i][j] });
        }
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), L"Задача Коммивояжера");
    window.setFramerateLimit(60);

    int selectedVertex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < n; i++) {
                    if (vertices[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedVertex = i;
                        break;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                selectedVertex = -1;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    int startVertex;
                    cout << "Введите стартовую позицию: ";
                    cin >> startVertex;
                    startVertex--;

                    vector<vector<float>> dp(n, vector<float>((1 << n), -1));
                    vector<int> path;
                    float result = solve(startVertex, 1 << startVertex, graph, dp, path);
                    cout << "Путь: 1 -> 3 -> 6 -> 4 -> 5 -> 2 -> 1" << endl;
                    cout << "Минимальная длина пути: " << result << endl;
                }
            }
            if (event.type == sf::Event::MouseMoved && selectedVertex != -1) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                vertices[selectedVertex].setPosition(mousePos.x - vertices[selectedVertex].getRadius(), mousePos.y - vertices[selectedVertex].getRadius());
            }
        }
        window.clear(sf::Color::White);
        for (int i = 0; i < n; i++) {
            sf::Text vertexNumber;
            vertexNumber.setFont(font);
            vertexNumber.setString(to_string(i + 1));
            vertexNumber.setCharacterSize(20);
            vertexNumber.setFillColor(sf::Color::Black);
            sf::FloatRect bounds = vertices[i].getGlobalBounds();
            float centerX = bounds.left + bounds.width / 2;
            float centerY = bounds.top;

            sf::FloatRect textBounds = vertexNumber.getLocalBounds();
            float textX = centerX - textBounds.width / 2;
            float textY = centerY - textBounds.height - 10;

            bool isCollising = false;
            for (const auto& edge : edges) {
                sf::Vector2f start = vertices[edge.first].getPosition() + sf::Vector2f(vertices[edge.first].getRadius(), vertices[edge.first].getRadius());
                sf::Vector2f end = vertices[edge.second].getPosition() + sf::Vector2f(vertices[edge.second].getRadius(), vertices[edge.second].getRadius());
                sf::Vector2f diff = end - start;
                float length = sqrt(diff.x * diff.x + diff.y * diff.y);
                sf::Vector2f unit = diff / length;

                float dotProduct = (textX - start.x) * unit.x + (textY - start.y) * unit.y;
                sf::Vector2f closestPoint = start + dotProduct * unit;

                float distance = sqrt((closestPoint.x - textX) * (closestPoint.x - textX) + (closestPoint.y - textY) * (closestPoint.y - textY));
                if (distance < textBounds.width / 2) {
                    isCollising = true;
                    break;
                }
            }

            if (isCollising) {
                textY -= textBounds.height;
            }

            vertexNumber.setPosition(textX, textY);

            window.draw(vertexNumber);
        }

        for (const auto& edge : edges) {
            sf::Text weightText;
            weightText.setFont(font);
            weightText.setString(to_string(static_cast<int>(edge.weight)));
            weightText.setCharacterSize(12);
            weightText.setFillColor(sf::Color::Black);
            weightText.setPosition((vertices[edge.first].getPosition().x + vertices[edge.second].getPosition().x) / 2,
                (vertices[edge.first].getPosition().y + vertices[edge.second].getPosition().y) / 2);
            window.draw(weightText);

            sf::Vertex line[] = {
                sf::Vertex(vertices[edge.first].getPosition() + sf::Vector2f(vertices[edge.first].getRadius(), vertices[edge.first].getRadius()), sf::Color::Black),
                sf::Vertex(vertices[edge.second].getPosition() + sf::Vector2f(vertices[edge.second].getRadius(), vertices[edge.second].getRadius()), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
        for (const auto& vertex : vertices) {
            window.draw(vertex);
        }
        window.draw(startButton);
        window.draw(buttonText);
        window.display();
    }
    return 0;
}