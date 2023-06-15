#include <iostream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;

const int windowWidth = 800;
const int windowHeight = 600;

struct Edge {
    int first;
    int second;
    int weight;
};
int m = 1000;
int n = 6;
vector<vector<int>> matr(n, vector<int>(n));
vector<vector<int>> matr2;
vector<vector<int>> matr3;
vector<pair<int, int>> way;
vector<sf::CircleShape> city(n, sf::CircleShape(35));
vector<Edge> roads;


void create() {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Из " << i + 1 << " в " << j + 1 << ": ";
            cin >> matr[i][j];
            roads.push_back({ i, j, matr[i][j] });
            matr[j][i] = matr[i][j];
        }
    }
}

int rMin(int h, int g)
{
    int min = m;
    for (int i = 0; i < n; i++)
    {
        if (matr2[h][i] < min && i != g && matr2[h][i] != -1)
            min = matr2[h][i];
    }
    return min;
}
int cMin(int h, int g)
{
    int min = m;
    for (int i = 0; i < n; i++)
    {
        if (matr2[i][g] < min && i != h && matr2[i][g] != -1)
            min = matr2[i][g];
    }
    return min;
}
void fillingmatr() {
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i == j)
                tmp.push_back(-1);
            else
                tmp.push_back(matr[i][j]);
        matr2.push_back(tmp);
        tmp.clear();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            tmp.push_back(matr[i][j]);
        matr3.push_back(tmp);
        tmp.clear();
    }
}
pair<int, int> bestways()
{
    int max = -m;
    vector<vector < int>> copy = matr2;
    std::pair<int, int> way;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matr2[i][j] == 0)
            {
                int mark = 0;
                mark += rMin(i, j);
                mark += cMin(i, j);
                if (max < mark)
                {
                    max = mark;
                    way.first = i;
                    way.second = j;
                }
            }
        }
    }
    if (matr2[way.second][way.first] == 0)
        matr2[way.second][way.first] = -1;
    for (int i = 0; i < n; i++)
    {
        matr2[way.first][i] = -1;
        matr2[i][way.second] = -1;
    }
    return way;
}
void Solve()
{
    matr2 = matr3;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                matr2[i][j] = -1;
            if (matr2[i][j] <= 0)
                matr2[i][j] = -1;
        }

    int i = 0;
    while (i != n) {  
        std::pair<int, int> tmp;
        for (int i = 0; i < n; i++)
        {
            int min = m;
            for (int j = 0; j < n; j++)
            {
                if (matr2[j][i] < min && matr2[j][i] != -1)
                    min = matr2[j][i];
            }
            if (min != m && min != 0)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matr2[j][i] > 0 && matr2[j][i] != m)
                        matr2[j][i] -= min;
                }
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            int min = m;
            for (int j = 0; j < n; j++)
            {
                if (matr2[i][j] < min && matr2[i][j] != -1)
                    min = matr2[i][j];
            }
            if (min != m && min != 0)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matr2[i][j] > 0 && matr2[i][j] != m)
                        matr2[i][j] -= min;
                }
            }
        }      
        tmp = bestways();
        if (tmp != std::pair<int, int>(0, 0))
            way.push_back(tmp);
        i++;
    }
}

void bestwayprint() {
    cout << "Путь: ";
    int startpos = 0;
    int sum = 0;
    for (int i = 0; i < way.size(); i++) {
        for (int j = 0; j < way.size(); j++) {
            if (way[j].first == startpos) {
                cout << way[j].first + 1 << " -> ";
                startpos = way[j].second;
                break;
            }
        }
    }
    bool f = false;
    for (int j = 0; j < way.size(); j++)
        if (way[j].first == startpos) {
            cout << way[j].first + 1;
            f = true;
            break;
        }
    if (!f) {
        for (int j = 0; j < way.size(); j++)
            if (way[j].second == startpos)
                cout << way[j].second + 1;
    }
    cout << endl;
    for (int i = 0; i < way.size(); i++)
        sum += matr[way[i].first][way[i].second];
    cout << "Ответ: " << sum << endl;
}

int main() {
    setlocale(LC_ALL, "RUS"); 
    
    sf::RectangleShape st(sf::Vector2f(200, 55));
    st.setPosition(windowWidth - 500, windowHeight - 70);
    st.setFillColor(sf::Color{0xC9CB62});
    sf::Font font;
    if (!font.loadFromFile("s.ttf")) {
        cerr << "Ошибка загрузки шрифта" << endl;
        return 1;
    }
    sf::Image icon;
    icon.loadFromFile("icon.png");
    
    sf::Image table;
    table.loadFromFile("t2.png");
    sf::Texture texture_table;
    texture_table.loadFromImage(table);
    sf::Sprite table_sprite(texture_table, sf::IntRect(0, 0, 800, 600));

    sf::Image donut;
    donut.loadFromFile("donut.png");
    sf::Texture texture_donut;
    texture_donut.loadFromImage(donut);
    texture_donut.setRepeated(true);

    sf::Text solvebutton{L"Решить", font, 24 };
    solvebutton.setFillColor(sf::Color{0x8686CB});
    solvebutton.setPosition(windowWidth - 440, windowHeight - 60);  
    //БОЛЬШИЕ ГОРОДАААААА
    for (int i = 0; i < n; i++) {
        city[i].setPosition(windowWidth / (n + 1) * (i + 1), windowHeight / 2);
        city[i].setTexture(&texture_donut);
        city[i].setTextureRect(sf::IntRect(0, 0, 722, 722));
        city[i].setFillColor(sf::Color(252, 186-i*5, 211));
        
    }

    sf::RenderWindow window{ {800, 600}, L"Задача Коммивояжера" };
    window.setFramerateLimit(0);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Vector2u sizewin = window.getSize();
    unsigned int w = sizewin.x;
    unsigned int h = sizewin.y;   

    int curv = -1;

    while (window.isOpen()) {
        sf::Event solve_event;
        while (window.pollEvent(solve_event)) {    
            if (solve_event.type == sf::Event::MouseButtonPressed && solve_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if (st.getGlobalBounds().contains(pos.x, pos.y)) {
                    create();
                    fillingmatr();
                    Solve();
                    bestwayprint();
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
                int citySize = 35;
                ;
                if (city[curv].getPosition().x < 0)
                    city[curv].setPosition(0, (city[curv].getPosition().y));
                else if (city[curv].getPosition().x > 730)
                    city[curv].setPosition(730, (city[curv].getPosition().y));

                if (city[curv].getPosition().y < 20)
                    city[curv].setPosition((city[curv].getPosition().x), 20);
                else if (city[curv].getPosition().y > 530)
                    city[curv].setPosition((city[curv].getPosition().x), 530);
            }
            if (solve_event.type == sf::Event::MouseButtonReleased && solve_event.mouseButton.button == sf::Mouse::Left) {
                curv = -1;
            }
            if (solve_event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        window.draw(table_sprite);
        for (int i = 0; i < n; i++) {
            sf::Text citynumb{to_string(i + 1), font, 20 };
            citynumb.setFillColor(sf::Color::Black);         
            sf::FloatRect bounds = city[i].getGlobalBounds();
            float xx = bounds.left + bounds.width / 2;
            float yy = bounds.top;
            sf::FloatRect nameb = citynumb.getLocalBounds();
            float xxname = xx - nameb.width / 2;
            float yyname = yy - nameb.height - 10;

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
