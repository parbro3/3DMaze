#include "Pathfinder.h"
#include <iostream>
using namespace std;
int main()
{
    Pathfinder em;
    
    string temp;
    
    temp = em.getMaze();
    
    cout << temp;
    
    em.createRandomMaze();
    
    bool importmaze = em.importMaze("Solvable1.txt");
    
    if (importmaze == true)
    {
        cout << "true";
    }
    
    if (importmaze == false)
    {
        cout << "false";
    }
    
    em.solveMaze();
    
}

