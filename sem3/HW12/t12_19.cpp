#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

typedef struct Point{
    double x, y, z;
}Point;

typedef struct Interval{
    Point p1, p2;
} Interval;

void append_points(std::ifstream &file, Point **parr, int *size){
    double x, y, z;
    char comma, semicolon;
    int count = 2;
    (*parr) = new Point[count];

    if (file.bad()) {
        std::cout << "File bad";
        return;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream stream(line);

    while (stream >> x >> comma >> y >> comma >> z >> semicolon){


        if  (*size == count){
            count *= 2;
            Point* temp = new Point[count];
            for (int i = 0; i < *size; i++){
                temp[i] = (*parr)[i];
            }
            delete[] *parr;
            *parr = temp;
        }

        (*parr)[*size].x = x;
        (*parr)[*size].y = y;
        (*parr)[*size].z = z;
        (*size)++;


    }
    if (file.eof()) {
        std::cout << "File ended." << std::endl;
    } else if (file.fail()) {
        std::cerr << "Error reading the file." << std::endl;
    }
}

double find_max(double const *arr, int size){
    double max_el = arr[0];
    for (int i = 0; i < size; i++){
        if (max_el < arr[i])
            max_el = arr[i];
    }
    return max_el;
}

double find_length(Interval I){
    double first = pow((I.p1.x-I.p2.x), 2);
    double second = pow((I.p1.y-I.p2.y), 2);
    double third = pow((I.p1.z - I.p2.z), 2);
    return sqrt(first+second+third);
}

void create_intervals(Point* parr, double** lengths, int psize, int* lsize){
    int count_l = 2;
    (*lengths) = new double[count_l];

    if (*lsize == count_l){
        count_l *= 2;
        double *temp = new double[count_l];
        for (int j = 0; j < *lsize; j++){
            temp[j] = (*lengths)[j];
        }
        delete[] *lengths;
        (*lengths) = temp;
    }


    Interval y;
    double max_length = 0;
    Interval largest;
    for (int i = 0; i < psize; i ++){
        for (int k = i; k < psize; k++) {
            y.p1 = parr[i];
            y.p2 = parr[k];
            (*lengths)[*lsize] = find_length(y);
            if (find_length(y) >= max_length){
                largest = y;
                max_length = find_length(y);
            }
            (*lsize)++;
        }
    }
    std::printf("The largest interval is from point %lf %lf %lf to point %lf %lf %lf with length %lf", largest.p1.x, largest.p1.y, largest.p1.z,
                largest.p2.x, largest.p2.y, largest.p2.z, find_length(largest));
}

void free_all(Point *parr, double *larr){
    delete[] parr;
    delete[] larr;
}

void output(Point *arr, int size){
    for (int j = 0; j < size; j++){
//        std::cout << "Point with coordinates" << arr[j].x << arr[j].y << arr[j].z << std::endl;
        std::printf("Point %d with coordinates %lf %lf %lf", j, arr[j].x, arr[j].y, arr[j].z);
    }
}



int main(){
    std::ifstream f_in("input1219.txt");
    Point* points;
    int size_points = 0;
    double *lengths;
    int size_intervals = 0;

    if (!f_in) {
        std::cerr << "Oops, problems with the file" << std::endl;
        return 1;
    }

    append_points(f_in, &points, &size_points);
    create_intervals(points, &lengths, size_points, &size_intervals);
    find_max(lengths, size_intervals);



    free_all(points, lengths);
    f_in.close();
}
