#include <Engine/include/Engine.h>
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

void Engine::Initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<double>(width) / height;

    sf::ContextSettings settings(0, 0, 8, 1, 1, 0, false);
    window.create(sf::VideoMode(width, height), "Achilles", sf::Style::Fullscreen, settings);

    LoadObjTypes("resources/objectTypes.txt");
    LoadObjects("resources/objectMap.txt");
}

void Engine::LoadObjTypes(const std::string& path) {
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        std::cerr << "�� ������� ������� ���� � ���������� �������� �� ���� " +
                         path;  // ����� ��������� ������ ����� ������, ��� ����
        Stop();
    }
    line buf({0, 0}, {0, 0});
    std::string inputbuffer;
    std::string strbuf;
    std::vector<line> vectorbuf;
    double x1, y1, x2, y2;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> strbuf;
        while (input >> x1 >> y1 >> x2 >> y2) {
            buf = line({x1, y1}, {x2, y2});
            vectorbuf.push_back(buf);
        }
        objtypes_.insert({strbuf, vectorbuf});
        vectorbuf.clear();
    }
}

void Engine::LoadObjects(
    const std::string& path) {  // ���� ���, ���������� �����������: ������ � �����
    // ������� � ����������� ���������� ������
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        std::cerr << "�� ������� ������� ���� � ������ �������� �� ���� " +
                         path;  // ����� ��������� ������ ����� ������, ��� ����
        Stop();
    }
    vec buf(0, 0);
    std::string inputbuffer;
    std::string name;
    std::vector<line> vectorcache;
    std::string cachename;
    double x1, y1;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> name >> x1 >> y1;
        buf = vec(x1, y1);
        if (cachename != name) {
            cachename = name;
            vectorcache = objtypes_[name];
        }
        input >> inputbuffer;
        if (inputbuffer == "m") {
            moveableObjects_.push_back(std::make_unique<MoveableObject>(buf, vectorcache));
        }
        if (inputbuffer == "s") {
            objects_.push_back(std::make_unique<Object>(buf, vectorcache));
        }
    }
}

void Engine::Stop() {
    exit(-1);
}

void Engine::RenderFrame() {
    window.clear(sf::Color(0, 0, 0, 0));
    for (const auto& obj : objects_) {
        RenderObject(obj);
    }
    for (const auto& obj : moveableObjects_) {
        RenderObject(obj);
    }
    window.display();
}

void Engine::RenderObject(const std::unique_ptr<Object>& object) {
    for (const auto& line : object->polygons_) {
        sf::Vertex vline[] = {
          sf::Vertex(sf::Vector2f(line.d1.cord(width, height).x, line.d1.cord(width, height).y)),
          sf::Vertex(sf::Vector2f(line.d2.cord(width, height).x, line.d2.cord(width, height).y))};
        window.draw(vline, 2, sf::Lines);
    }
}

void Engine::PhysicPerFrame() {

}