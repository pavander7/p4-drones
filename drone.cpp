//1761414855B69983BD8035097EFBD312EB0527F0

#include <getopt.h>
#include <iostream>
#include <vector>
#include "MST.h"

using namespace std;

struct Vertex;
class MST;

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
    size_t N = 0;
    cin >> N;
    data.reserve(N);
    for (size_t n = 0; n < N; n++) {
        int x, y;
        cin >> x >> y;
        data.push_back(Vertex{x,y,n});
    }

    switch (mode) {
        case 'A' : {
            MST graph(data);
            cout << graph;
            break;
        } case 'B' : {
            cerr << "unimplemented\n";
            break;
        } case 'C' : {
            cerr << "unimplemented\n";
            break;
        }
    }
    
}