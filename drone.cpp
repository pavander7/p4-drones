//1761414855B69983BD8035097EFBD312EB0527F0

#include <getopt.h>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int pow_dist (int a, int b) {return ((a*a) + (b*b));}
double dist (int a, int b) {return sqrt(pow_dist(a,b));}
struct Vertex;
class Graph;

int main (int argc, char* argv[]) {
    // step one: setup
    ios_base::sync_with_stdio(false);
    std::cout.clear();
    cin >> std::boolalpha;
    std::cout << std::boolalpha;
    string modeName;
    bool mode_spec = false;

    //std::cout << "checkpoint 1: beginning \n";

    static struct option long_options[] = {
    {"mode",        required_argument,  0,      'm'},
    {"help",        no_argument,        NULL,   'h'},
    {0,             0,                  NULL,   0, }
    };
    int option_index = 0;

    //variables for input processing

    int c = getopt_long(argc, argv, "mh", long_options, &option_index);
    while (c != -1) {
        switch(c) {
            case 'm' :
                modeName = optarg;
                mode_spec = true;
            case 'h' :
                std::cout << "help message";
                return 0;
                break;
            default :
                cerr << "Error: Invalid command line option\n";
                exit(1);
                break;
        }
        c = getopt_long(argc, argv, "m:h", long_options, &option_index);
    }

    char mode = 0;

    if (!mode_spec) {
        cerr << "Error: No mode specified\n";
        exit(1);
    }

    if (modeName == "MST") mode = 'A';
    else if (modeName == "FASTTSP") mode = 'B';
    else if (modeName == "OPTTSP") mode = 'C';
    else {
        cerr << "Error: Invalid mode\n";
        exit(1);
    }

    std::vector<Vertex> data;
    int N = 0;
    cin >> N;
    data.reserve(N);
    for (int n = 0; n < N; n++) {
        int x, y;
        cin >> x >> y;
        data.push_back(Vertex{x,y});
    }

    
}

struct Vertex {
int x, y;
Vertex(int x_in, int y_in) : x(x_in), y(y_in) {}
int area() {
    if (x < 0 && y < 0) return 2;
    else if ((x == 0 && y < 0)||(y == 0 && x < 0)) return 1;
    else return 0;
}
};

class Graph {
public:
    Graph(vector<Vertex> &data_in) : data(data_in) {}
    void push_back (Vertex datum) {data.push_back(datum);}
    size_t size () {return data.size();}
    Vertex start() {return data[0];}
    Vertex &operator[] (size_t i) {return data[i];}
    size_t area(size_t i) {
        if (areas.count(i) == 0) {
            areas[i] = data[i].area();
        } else return areas[i];
    }
    class Path;
private:
    vector<Vertex> data;
    unordered_map<size_t, size_t> areas;
};

class Graph::Path {
public:
    Path(size_t N) : weight (0) {path.reserve(N);}
    friend class Graph;
    double MST (vector<Vertex> &data);
private:
    double weight;
    vector<size_t> path;
};

