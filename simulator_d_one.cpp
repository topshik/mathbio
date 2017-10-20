#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

const double birth_rate = 0.4;
const double death_rate = 0.2;
int wall;

class Cell {
private:
    unsigned long long  population, column;
    double x;
public:
    Cell() {};

    Cell(int Population, double X)
    : population(Population), x(X) {};

    double get_coordinates() const {
        return x;
    }

    unsigned long long get_population() const {
        return population;
    }

    unsigned long long get_indices() const {
        return column;
    }

    void set_coordinates(double X) {
        x = X;
    }

    void set_population(unsigned long long Population) {
        population = Population;
    }

    void set_indices(unsigned long long Column) {
        column = Column;
    }

    void print(std::ostream &out) const {
        out << std::setw(3) << population << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const Cell &cell) {
        cell.print(out);
        return out;
    }
};

class Grid {
private:
    unsigned long long total_population, discretizatiion;
    double width;
    std::vector<Cell> cells;
public:
    Grid() {};

    Grid(unsigned long long Init_population, unsigned long long Discretizatiion, double Width)
    :total_population(Init_population), discretizatiion(Discretizatiion), width(Width) {
        cells = std::vector<Cell>(discretizatiion);
        Cell init_cell;
        for (unsigned long long i = 0; i != total_population; ++i) {
            init_cell.set_population(1);
            init_cell.set_indices(rand() % discretizatiion);             // FIXME: indices, columns, rows??
            init_cell.set_coordinates((width / discretizatiion) * ((double)init_cell.get_indices() + 0.5));
            cells[init_cell.get_indices()] = init_cell;
        }
    }

    std::vector<Cell> get_cells() const {
        return cells;
    }

    Cell & operator[] (int x) {  // setter
        return cells[x];
    }

    Cell operator[] (int x) const {  // getter
        return cells[x];
    }
};

int main(int argc, char ** argv) {
    srand(time(NULL));
    Grid grid(10, 10, 1);
    for (auto cell : grid.get_cells())
        std::cout << cell;
}
