#include "Pathfinder.h"


string Pathfinder :: getMaze()
{
    string current_maze;
    stringstream ss;
    bool no_maze_yet = false;
    
    if (real_array[0][0][0] == "0" && real_array[4][4][4] == "0")
    {
        no_maze_yet = true;
    }
    
    if (no_maze_yet == true)
    {
        for (int k = 0 ; k < 5 ; k++)
        {
            for (int j = 0 ; j < 5 ; j++)
            {
                for (int i = 0 ; i < 5 ; i++)
                {
                    current_maze = current_maze + "1";
                    
                    if (i < 4)
                    {
                        current_maze = current_maze + " ";
                    }
                }
                current_maze = current_maze + "\n";
            }
            current_maze = current_maze + "\n";
        }
    }
    
    if (no_maze_yet == false)
    {
        for (int k = 0 ; k < 5 ; k++)
        {
            for (int j = 0 ; j < 5 ; j++)
            {
                for (int i = 0 ; i < 5 ; i++)
                {
                    current_maze = current_maze + real_array[i][j][k];
                    
                    if (i < 4)
                    {
                        current_maze = current_maze + " ";
                    }
                }
                current_maze = current_maze + "\n";
            }
            current_maze = current_maze + "\n";
        }
    }
    
    return current_maze;
}

void Pathfinder :: createRandomMaze()
{
    for (int i = 0 ; i < 5 ; i++)
    {
        for (int j = 0 ; j < 5 ; j++)
        {
            for (int k = 0 ; k < 5 ; k++)
            {
                int random_number = rand()%2;
                string random_string;
                stringstream ss;
                ss << random_number;
                
                random_string = ss.str();
                real_array[i][j][k] = random_string;
            }
        }
    }
    
    real_array[0][0][0] = "1";
    real_array [4][4][4] = "1";
    
}


bool Pathfinder :: importMaze(string file_name)
{
    string temp_array[5][5][5];
    ifstream in;
    in.open(file_name);
    
    if (in.fail())
    {
        return false;
    }
    
    for (int k = 0 ; k < 5 ; k++)
    {
        for (int j = 0 ; j < 5 ; j++)
        {
            for (int i = 0 ; i < 5 ; i++)
            {
                string temp_string;
                in >> temp_string;
                temp_array[i][j][k] = temp_string;
                
                if (temp_string != "0" && temp_string != "1")
                {
                    return false;
                }
            }
        }
    }
    
    if (temp_array[0][0][0] != "1" || temp_array[4][4][4] != "1")
    {
        return false;
    }
    
    if (!in.eof())
    {
        return false;
    }
    
    
    for (int i = 0 ; i < 5 ; i++)
    {
        for (int j = 0 ; j < 5 ; j++)
        {
            for (int k = 0 ; k < 5 ; k++)
            {
                real_array[i][j][k] = temp_array[i][j][k];
            }
        }
    }
    
    return true;                    // if it gets through all of the above tests... return true;
}



vector<string> Pathfinder :: solveMaze()
{
    cout << "entering solvemaze function.";
    vector<string> maze_solution;
    string temp_array[5][5][5];
    
    
    for (int i = 0 ; i < 5 ; i++)
    {
        for (int j = 0 ; j < 5 ; j++)
        {
            for (int k = 0 ; k < 5 ; k++)
            {
                temp_array[i][j][k] = real_array[i][j][k];
            }
        }
    }
    
    cout << "assigned temp array to real array.";
    int i = 0;
    int j = 0;
    int k = 0;
    
    solve_maze_helper(i, j, k, maze_solution, temp_array);
    
    return maze_solution;
}






bool Pathfinder :: solve_maze_helper(int i , int j , int k, vector<string> &maze_solution, string (&my_array)[5][5][5])
{
    // make the vector of strings in the solve_maze function. and pass it by reference into the solve_maze_helper function;
    
    if (i == 4 && j == 4 && k == 4)
    {
        return true;
    }
    
    if (my_array[i][j][k] == "0")
    {
        return false;
    }
    
    if (my_array[i][j][k] == "2")
    {
        return false;
    }
    
    if (i < 0 || j < 0 || k < 0)
    {
        return false;
    }
    
    if (i > 4 || j > 4 || k > 4)
    {
        return false;
    }
    
    
    /* possible base cases:
     - if == (4,4,4) (reaches the end), return true;
     - if (x,y,z) == 0... return false;
     - if out of bounds. (if you leave the walls...) return false;
     - if it's already been visited: return false;*/
    
    
    if(my_array[i+1][j][k] == "1" && (i+1) <= 4)
    {
        stringstream ss;
        ss << "(" << i+1 << "," << j << "," << k << ")";
        string path = ss.str();
        maze_solution.push_back(path);
        
        my_array[i+1][j][k] = "2";       //update as visited
        
        bool worked = solve_maze_helper(i+1, j , k, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
        
    }
    
    
    // this is where I'm at.... keep doing below what you did right above ^^^
    
    if(my_array[i-1][j][k] == "1" && i-1 >= 0)
    {
        stringstream ss;
        ss << "(" << i-1 << "," << j << "," << k << ")";
        string path = ss.str();
        maze_solution.push_back(path); //insert string into refereneced vector of strings.
        
        my_array[i-1][j][k] = "2";
        
        bool worked = solve_maze_helper(i-1, j , k, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
        
    }
    
    if(my_array[i][j+1][k] == "1" && j+1 <= 4)
    {
        stringstream ss;
        ss << "(" << i << "," << j+1 << "," << k << ")";
        string path = ss.str();
        maze_solution.push_back(path); //insert string into refereneced vector of strings.
        
        my_array[i][j+1][k] = "2";
        
        bool worked = solve_maze_helper(i, j+1 , k, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
    }
    
    if(my_array[i][j-1][k] == "1" && j-1 >= 0)
    {
        stringstream ss;
        ss << "(" << i << "," << j-1 << "," << k << ")";
        string path = ss.str();
        maze_solution.push_back(path); //insert string into refereneced vector of strings.
        
        my_array[i][j-1][k] = "2";
        
        bool worked = solve_maze_helper(i, j-1 , k, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
    }
    
    if(my_array[i][j][k+1] == "1" && k+1 <= 4)
    {
        stringstream ss;
        ss << "(" << i << "," << j << "," << k+1 << ")";
        string path = ss.str();
        maze_solution.push_back(path); //insert string into refereneced vector of strings.
        
        my_array[i][j][k+1] = "2";
        
        bool worked = solve_maze_helper(i, j , k+1, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
    }
    
    if(my_array[i][j][k-1] == "1" && k-1 >= 0)
    {
        stringstream ss;
        ss << "(" << i-1 << "," << j << "," << k << ")";
        string path = ss.str();
        maze_solution.push_back(path); //insert string into refereneced vector of strings.
        
        my_array[i][j][k-1] = "2";
        
        bool worked = solve_maze_helper(i, j , k-1, maze_solution, my_array);
        
        if(worked == true)
        {
            return true;
        }
    }
    
    
    
    return true;
}





/*
 use recursion to solve the maze or to say that there is no solution to the maze.
 
 100     (0,0,0)
 100     (0,1,0)
 100     (0,2,0).... etc
 
 000
 000
 100
 
 000
 000
 111
 
 xyz
 
 (0,0,0) and (4,4,4) must be a 1. otherwise you can never enter or exit the maze.
 
 3D array or 3D vector.
 
 
 creating array or vector:
 triple for-loop (for x, y, and z)
 
 PERHAPS an enum... 0 = wall, 1 = open , 2 = visited
 
 
 pathway... vector of strings? (0,0,0) -> (0,1,0)... store the path as a vector of strings and return it in the "solve maze" function
 
 
 
 
 
 create a random maze...
 
 triple for loop. set each index to either a 1 or a 0. rand() % 2 for generating random maze.
 #include <cstdlib>
 
 (0,0,0) and (4,4,4) have to be 1.
 
 
 
 
 import maze:
 
 open file and read in the string. maybe a counter to be 125... check validity.
 if it's not valid, then the maze that you have shouldn't change.
 or make a temporary array and then store it as the new one. look at the test cases in the maze folder.
 
 - not enough input
 - too much input
 - check if (0,0,0) and (4,4,4) are both 1s.
 - there's an "a" in one of the cells.
 - some random 3s.
 
 how to check if too many lines or too few lines:
 - count the number of lines
 - number of characters per line.
 -
 
 
 
 
 solve the maze: trips up most students (Recursion):
 
 
 call solve_maze_helper_function.
 
 
 solve maze (solve_maze_helper_function (0,0,0);
 once you've visited it, change the coordinate to "visited" or two or whatever you e-num-ed.
 
 
 then call helper function at each of the indexes above, below, left, and right, in and out. (6).
 
 
 
 possible base cases:
 - if == (4,4,4) (reaches the end), return true;
 - if (x,y,z) == 0... return false;
 - if out of bounds. (if you leave the walls...) return false;
 - if it's already been visited: return false;
 
 
 
 
 
 
 
 
 
 */