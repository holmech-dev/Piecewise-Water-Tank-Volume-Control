#include <iostream>
#include <fstream>

/********************
Program - Piecewise Controller
Maintainer - C.Holmes
Version - 0
********************/


// Variable Delarations
int reference;
int actual = 10;
int error = 0;
int K = 1;
int dt = 1; // 1 second time interval
int sim_time = 10;

// Function Declarations

int pieceWise(int ref, int error, int actual, int dt) {
    /*
    Mass Flowrate, m_dot
        if e < 0, -10 kg/s
        if e = 0, 0 kg/s
        if e > 0, 10 kg/s
    */

    // Open and create CSV file and header for plotting
    std::ofstream sim_out_file;
    sim_out_file.open("sim_out.csv");
    sim_out_file << "Index,reference,error,actual,dt\n";

    int q_dot = 0;
    //for loop to interate through the system
    for (int i = 0; i < sim_time; i++){

        int actual_i = q_dot * dt;
        actual = actual + actual_i;
        error = (reference - actual) * K;
        
        if (error <  0)
            q_dot = -10;
        else if (error == 0)
            q_dot = 0;
        else 
            q_dot = 10;

        std::cout << i << ',' << actual << std::endl;
        
        sim_out_file << i << "," << reference << "," << error << "," << actual << "," << dt << "\n";

    }
    return actual;
}


int main () {

    std::cout << "\n\n";
    std::cout << "**********************************************************\n";
    std::cout << "Water Tank Piecewise Controller Program Starting......  🕹️\n";
    std::cout << "**********************************************************\n";
    

    // User intput for Reference/Target water tank level
    std::cout << "\n";
    std::cout << "Please input a reference value: ";
    std::cin >> reference;
    std::cout << "Reference Target Value -> " << reference << std::endl;
    std::cout << "\n";
    std::cout << "Start Actual Value -> " << actual << std::endl;
    std::cout << "\n";

    // Error calculation
    error = reference - actual;
    std::cout << "Start Error Value -> " << error << std::endl;
    std::cout << "\n";

    // Piecewise function to update the flow rate
    pieceWise(reference, error, actual, dt);

}