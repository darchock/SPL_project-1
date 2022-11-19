#include <iostream>
#include <iomanip>
#include "../include/Parser.h"

using std::cout;
using std::endl;

// visulization:
// python3 visualization.py ./tests/02_sol.out

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <config_path>" << endl;
        return -1;
    }

    // read simulation from config file
    const string config_path = argv[1];
    Simulation simulation = Parser::readSimulation(argv[1]);

    // run simulation and store json state after each iteration
    // vector<json> outPerIter = {Parser::makeJson(simulation)};
    // while (!simulation.shouldTerminate())
    // {
    //     simulation.step();
    //     outPerIter.push_back(Parser::makeJson(simulation));
    // }

    // // writing the outputs list to a file
    // const string output_path = config_path.substr(0, config_path.find_last_of('.')) + ".out";
    // std::ofstream outputFile(output_path);
    // outputFile << std::setw(4) << json(outPerIter) << endl;

    cout << simulation.getParty(0).getName() << " - The Lannisters" << endl;
    cout << simulation.getParty(0).getCoalitionId() <<  " - 0" << endl;
    for (vector<int> vec : simulation.getPartiesByCoalitions()) {
        for (int i : vec)
            cout << i << endl;
    }

    cout << "This run has successfully have been built & launch" << endl;

    return 0;
}