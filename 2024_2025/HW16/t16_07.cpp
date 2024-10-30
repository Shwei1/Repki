#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>

class Point{
public:
    double x, y;

    Point(double x, double y): x(x), y(y){}

    static double distance(const Point& a, const Point& b){
        return sqrt((a.x - b.x)*(a.x - b.x) + (a.y-b.y)*(a.y-b.y));
    }

};

struct BoundingBox {
    double left, top, right, bottom;

    BoundingBox(double left, double top, double right, double bottom)
            : left(left), top(top), right(right), bottom(bottom) {}
};

class Figure{
public:
    virtual ~Figure() = default;

    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double perimeter() const = 0;
    virtual void output() const = 0;
    [[nodiscard]] virtual std::string get_type() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle, const Point& pivot) = 0;
    [[nodiscard]] virtual BoundingBox get_bounding_box() const = 0;
};

class Trapezium : public Figure {
private:
    Point a, b, c, d;

    [[nodiscard]] static bool are_parallel(const Point& p1, const Point& p2, const Point& p3, const Point& p4){
        return (p2.y - p1.y) * (p4.x - p3.x) == (p4.y - p3.y) * (p2.x - p1.x);
    }

public:
    Trapezium(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {
        if (!(are_parallel(a, b, c, d) || are_parallel(b, c, d, a))) {
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
    }

    [[nodiscard]] std::string get_type() const override{
        return "Trapezium";
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

    [[nodiscard]] BoundingBox get_bounding_box() const override{
        double minX = std::min({a.x, b.x, c.x, d.x});
        double maxX = std::max({a.x, b.x, c.x, d.x});
        double minY = std::min({a.y, b.y, c.y, d.y});
        double maxY = std::max({a.y, b.y, c.y, d.y});

        return BoundingBox(minX, minY, maxX, maxY);
    }
};

class Parallelogram: public Figure {
private:
    Point a, b, c, d;

    [[nodiscard]] static bool are_parallel(const Point& p1, const Point& p2, const Point& p3, const Point& p4){
        return (p2.y - p1.y) * (p4.x - p3.x) == (p4.y - p3.y) * (p2.x - p1.x);
    }
public:

    Parallelogram(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {
        if (!(are_parallel(a, b, c, d) && are_parallel(b, c, d, a))) {
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
    }

    [[nodiscard]] std::string get_type() const override{
        return "Parallelogram";
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

    [[nodiscard]] BoundingBox get_bounding_box() const override{
        double minX = std::min({a.x, b.x, c.x, d.x});
        double maxX = std::max({a.x, b.x, c.x, d.x});
        double minY = std::min({a.y, b.y, c.y, d.y});
        double maxY = std::max({a.y, b.y, c.y, d.y});

        return BoundingBox(minX, minY, maxX, maxY);
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

    [[nodiscard]] std::string get_type() const override{
        return "Circle";
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

    [[nodiscard]] BoundingBox get_bounding_box() const override{
        double minX = o.x - r;
        double minY = o.y - r;
        double maxX = o.x + r;
        double maxY = o.y + r;
        return BoundingBox(minX, minY, maxX, maxY);
    }
};


std::unique_ptr<Figure> create_random_figure() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(-100, 100);
    static std::uniform_int_distribution<> type_dis(0, 2);

    int figureType = type_dis(gen);
    double x1 = dis(gen), y1 = dis(gen);
    double x2 = dis(gen), y2 = dis(gen);
    double x3 = dis(gen), y3 = dis(gen);
    double x4, y4;

    switch (figureType) {
        case 0:
            return std::make_unique<Circle>(Point(x1, y1), std::abs(x2)); // Ensure radius is positive
        case 1:
            if (std::uniform_int_distribution<>(0, 1)(gen) == 0) {
                x4 = x1 + (x3 - x2);
                y4 = y1 + (y3 - y2);
            } else {
                x4 = x2 + (x3 - x1);
                y4 = y2 + (y3 - y1);
            }
            return std::make_unique<Trapezium>(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4));
        case 2:
            x4 = x1 + (x3 - x2);
            y4 = y1 + (y3 - y2);
            return std::make_unique<Parallelogram>(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4));
        default:
            throw std::runtime_error("Unsupported figure");
    }
}

bool intersects(const BoundingBox& a, const BoundingBox& b) {
    return (a.left < b.right && a.right > b.left &&
            a.top < b.bottom && a.bottom > b.top);
}


void clear_intersections(std::unique_ptr<Figure>* figures, int num_figures) {
    bool any_intersect;
    do {
        any_intersect = false;
        for (int i = 0; i < num_figures; ++i) {
            for (int j = i + 1; j < num_figures; ++j) {
                if (intersects(figures[i]->get_bounding_box(), figures[j]->get_bounding_box())) {
                    std::cout << "Found an intersection between " << figures[i]->get_type() << " and " << figures[j]->get_type() << "!\n";
                    figures[i]->move(5, 5);
                    figures[j]->move(-5, -5);
                    any_intersect = true;
                }
            }
        }
    } while (any_intersect);
    std::cout << "All intersections cleared. Now they are all on their own." << std::endl;
}

void find_total_measures(std::unique_ptr<Figure>* figures, int num_figures){
    double general_area = 0;
    double general_perimeter = 0;

    for (int i = 0; i < num_figures; ++i){
        general_area += figures[i]->area();
        general_perimeter += figures[i]->perimeter();
    }
    std::cout << "The total area of figures is: " << general_area << '\n';
    std::cout << "The total perimeter of figures is: " << general_perimeter << '\n';
}

void largest_area_figure(std::unique_ptr<Figure>* figures, int num_figures){
    int largest_area_figure = 0;
    for (int i = 0; i < num_figures; ++i){
        if (figures[i]->area() > figures[largest_area_figure]->area())
            largest_area_figure = i;
    }
    std::cout << "The fattest figure is " << figures[largest_area_figure]->get_type() <<
    " with area of " << figures[largest_area_figure]->area() << '\n';
}

int main() {
    int num_figures;

    std::cout << "Enter the amount of figures you want to create: ";
    std:: cin >> num_figures;

    std::unique_ptr<Figure>* figures = new std::unique_ptr<Figure>[num_figures];

    try {
        for (int i = 0; i < num_figures; ++i) {
            figures[i] = create_random_figure();
        }

        for (int i = 0; i < num_figures; ++i) {
            figures[i]->output();
            std::cout << "Area: " << figures[i]->area() << "\n";
            std::cout << "Perimeter: " << figures[i]->perimeter() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        delete[] figures;
        return 1;
    }

    clear_intersections(figures, num_figures);

    find_total_measures(figures, num_figures);

    largest_area_figure(figures, num_figures);

    delete[] figures;

    return 0;
}

