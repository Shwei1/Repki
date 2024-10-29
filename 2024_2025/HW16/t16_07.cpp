#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <random>

class Point{
public:
    double x, y;

    Point(double x, double y): x(x), y(y){}

    static double distance(const Point& a, const Point& b){
        return sqrt((a.x - b.x)*(a.x - b.x) + (a.y-b.y)*(a.y-b.y));
    }

};


class Figure{
public:
    virtual ~Figure() = default;

    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double perimeter() const = 0;
    virtual void output() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle, const Point& pivot) = 0;
};

class Trapezium : public Figure {
private:
    Point a, b, c, d;

    [[nodiscard]] static bool areParallel(const Point& p1, const Point& p2, const Point& p3, const Point& p4){
        return (p2.y - p1.y) * (p4.x - p3.x) == (p4.y - p3.y) * (p2.x - p1.x);
    }

public:
    Trapezium(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {
        if (!(areParallel(a, b, c, d) || areParallel(b, c, d, a))) {
            throw std::invalid_argument("Input points do not resemble a trapezium");
        }
    }

    [[nodiscard]] double area() const override {
        return 0.5 * std::abs(a.x * b.y + b.x * c.y + c.x * d.y + d.x * a.y - (b.x * a.y + c.x * b.y + d.x * c.y + a.x * d.y));
    }

    [[nodiscard]] double perimeter() const override {
        return Point::distance(a, b) + Point::distance(b, c) + Point::distance(c, d) + Point::distance(d, a);
    }

    void output() const override {
        std::cout << "Trapezium with vertices:\n";
        std::cout << "A(" << a.x << ", " << a.y << ")\n";
        std::cout << "B(" << b.x << ", " << b.y << ")\n";
        std::cout << "C(" << c.x << ", " << c.y << ")\n";
        std::cout << "D(" << d.x << ", " << d.y << ")\n";
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }

    void move(double dx, double dy) override{
        a.x += dx;
        a.y += dy;
        b.x += dx;
        b.y += dy;
        c.x += dx;
        c.y += dy;
        d.x += dx;
        d.y += dy;
    }

    void rotate(double angle, const Point& pivot) override {
        double rad = angle * M_PI / 180.0;
        double cosine = cos(rad);
        double sine = sin(rad);

        Point newa = Point(cosine * (a.x - pivot.x) - sine * (a.y - pivot.y) + pivot.x,
                           sine * (a.x - pivot.x) + cosine * (a.y - pivot.y) + pivot.y);

        Point newb = Point(cosine * (b.x - pivot.x) - sine * (b.y - pivot.y) + pivot.x,
                           sine * (b.x - pivot.x) + cosine * (b.y - pivot.y) + pivot.y);

        Point newc = Point(cosine * (c.x - pivot.x) - sine * (c.y - pivot.y) + pivot.x,
                           sine * (c.x - pivot.x) + cosine * (c.y - pivot.y) + pivot.y);

        Point newd = Point(cosine * (d.x - pivot.x) - sine * (d.y - pivot.y) + pivot.x,
                           sine * (d.x - pivot.x) + cosine * (d.y - pivot.y) + pivot.y);

        a = newa;
        b = newb;
        c = newc;
        d = newd;
    }
};

class Parallelogram: public Figure {
private:
    Point a, b, c, d;

    [[nodiscard]] static bool areParallel(const Point& p1, const Point& p2, const Point& p3, const Point& p4){
        return (p2.y - p1.y) * (p4.x - p3.x) == (p4.y - p3.y) * (p2.x - p1.x);
    }
public:

    Parallelogram(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {
        if (!(areParallel(a, b, c, d) && areParallel(b, c, d, a))) {
            throw std::invalid_argument("Input points do not resemble a parallelogram");
        }
    }

    [[nodiscard]] double area() const override {
        return 0.5 * std::abs(a.x * b.y + b.x * c.y + c.x * d.y + d.x * a.y - (b.x * a.y + c.x * b.y + d.x * c.y + a.x * d.y));
    }

    [[nodiscard]] double perimeter() const override {
        return Point::distance(a, b) + Point::distance(b, c) + Point::distance(c, d) + Point::distance(d, a);
    }

    void output() const override {
        std::cout << "Parallelogram with vertices:\n";
        std::cout << "A(" << a.x << ", " << a.y << ")\n";
        std::cout << "B(" << b.x << ", " << b.y << ")\n";
        std::cout << "C(" << c.x << ", " << c.y << ")\n";
        std::cout << "D(" << d.x << ", " << d.y << ")\n";
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }

    void move(double dx, double dy) override{
        a.x += dx;
        a.y += dy;
        b.x += dx;
        b.y += dy;
        c.x += dx;
        c.y += dy;
        d.x += dx;
        d.y += dy;
    }

    void rotate(double angle, const Point& pivot) override {
        double rad = angle * M_PI / 180.0;
        double cosine = cos(rad);
        double sine = sin(rad);

        Point newa = Point(cosine * (a.x - pivot.x) - sine * (a.y - pivot.y) + pivot.x,
                           sine * (a.x - pivot.x) + cosine * (a.y - pivot.y) + pivot.y);

        Point newb = Point(cosine * (b.x - pivot.x) - sine * (b.y - pivot.y) + pivot.x,
                           sine * (b.x - pivot.x) + cosine * (b.y - pivot.y) + pivot.y);

        Point newc = Point(cosine * (c.x - pivot.x) - sine * (c.y - pivot.y) + pivot.x,
                           sine * (c.x - pivot.x) + cosine * (c.y - pivot.y) + pivot.y);

        Point newd = Point(cosine * (d.x - pivot.x) - sine * (d.y - pivot.y) + pivot.x,
                           sine * (d.x - pivot.x) + cosine * (d.y - pivot.y) + pivot.y);

        a = newa;
        b = newb;
        c = newc;
        d = newd;
    }
};

class Circle: public Figure {
private:
    Point o;
    double r;
public:
    Circle(const Point& center, double radius) : o(center), r(radius) {}

    [[nodiscard]] double perimeter() const override {
        return 2 * M_PI * r;
    }

    [[nodiscard]] double area() const override{
        return M_PI * r * r;
    }

    void output() const override {
        std::cout << "Circle with origin and radius:\n";
        std::cout << "O(" << o.x << ',' << o.y << ")\n";
        std::cout << "r = " << r << '\n';
    }

    void move(double dx, double dy) override{
        o.x += dx;
        o.y += dy;
    }

    void rotate(double angle, const Point& pivot) override {
        double rad = angle * M_PI / 180.0;
        double cosine = cos(rad);
        double sine = sin(rad);
        Point newo = Point(cosine * (o.x - pivot.x) - sine * (o.y - pivot.y) + pivot.x,
                           sine * (o.x - pivot.x) + cosine * (o.y - pivot.y) + pivot.y);

        o = newo;
    }
};

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<> dis(-100, 100);
std::uniform_int_distribution<> distype(-100, 100);


std::unique_ptr<Figure> createRandomFigure() {
    int figureType = distype(gen);
    double x1 = dis(gen), y1 = dis(gen);
    double x2 = dis(gen), y2 = dis(gen);
    double x3 = dis(gen), y3 = dis(gen);
    double x4 = dis(gen), y4 = dis(gen);

    switch (figureType) {
        case 0: // Circle
            return std::make_unique<Circle>(Point(x1, y1), std::abs(x2)); // Radius should be positive
        case 1: // Trapezium
            // Ensuring at least one pair of sides is parallel might require more controlled logic
            return std::make_unique<Trapezium>(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4));
        case 2: // Parallelogram
            return std::make_unique<Parallelogram>(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4));
        default:
            throw std::runtime_error("Unsupported figure type");
    }
}

std::unique_ptr<Figure>* generateRandomFigures(int count) {
    std::unique_ptr<Figure> *figures = new std::unique_ptr<Figure>[count];
    for (int i = 0; i < count; ++i) {
        figures[i] = createRandomFigure();
    }
    return figures;
}

int main(int argc, char* argv[]){
    Parallelogram p({0, 1}, {1, 0}, {0, -1}, {-1, 0});
    p.output();

}

