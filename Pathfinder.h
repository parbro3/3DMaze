#pragma once
#include "PathfinderInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;


class Pathfinder : public PathfinderInterface
{
protected:
    string real_array[5][5][5];
    
public:
    Pathfinder()
    {
        for (int i = 0 ; i < 5 ; i++)
        {
            for (int j = 0 ; j < 5 ; j++)
            {
                for (int k = 0 ; k < 5 ; k++)
                {
                    real_array[i][j][k] = "0";
                }
            }
        }
    }
    
    ~Pathfinder(){}

    string getMaze();

    void createRandomMaze();

    bool importMaze(string file_name);

    vector<string> solveMaze();
    
    bool solve_maze_helper(int i , int j , int k, vector <string> &maze_solution, string (&my_array)[5][5][5]);
};
