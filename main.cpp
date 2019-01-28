#include<iostream>
#include <queue>
using namespace std;

#define START 'S'
#define END 'E'
#define OBSTRUCTION 'X'
#define PATH '.'

#define ROW 5
#define COL 5

//To store matrix cell cordinates 
struct Point
{
    int x;
    int y;
};

// A Data Structure for queue used in BFS 
struct queueNode
{
    Point pt;  // The cordinates of a cell 
    int dist;  // cell's distance of from the source 
};

// check whether given cell (row, col) is a valid 
// cell or not. 
bool isValid(int row, int col)
{
    // return true if row number and column number 
    // is in range 
    return (row >= 0) && (row < ROW) &&
        (col >= 0) && (col < COL);
}

// These arrays are used to get row and column 
// numbers of 4 neighbours of a given cell 
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

void display(const int r, const int c, char arr[ROW][COL])
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// function to find the shortest path between 
// a given source cell to a destination cell. 
int BFS(char mat[][COL], Point src, Point dest)
{
    // check source and destination cell 
    // of the matrix are on valid path
    if (mat[src.x][src.y] != START)
    {
        cout << "Source is not on path\n";
        return -1;
    }

    if (mat[dest.x][dest.y] != END)
    {
        cout << "Destination is not on path\n";
        return -1;
    }
        

    bool visited[ROW][COL];
    memset(visited, false, sizeof visited);

    // Mark the source cell as visited 
    visited[src.x][src.y] = true;

    // Create a queue for BFS 
    queue<queueNode> q;

    // Distance of source cell is 0 
    queueNode s = { src, 0 };
    q.push(s);  // Enqueue source cell 

    // Do a BFS starting from source cell 
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;
        cout << "Checking (" << pt.x << ", " << pt.y << ")\n";

        // If we have reached the destination cell, 
        // we are done 
        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col) && 
                (mat[row][col] != OBSTRUCTION) &&
                !visited[row][col])
            {
                // mark cell as visited and enqueue it 
                visited[row][col] = true;
                cout << " Alternatives (" << row << ", " << col << ")\n";
                queueNode Adjcell = { { row, col }, curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    // Return -1 if destination cannot be reached 
    cout << "No path found\n";
    return -1;
}

int main()
{
    const int n = 5;
    const int r = n;
    const int c = n;

    char arr[r][c] = {  
                        {'S', '.', '.', '.'},
                        {'.', 'X', 'X', '.' },
                        {'.', 'X', '.', '.' },
                        {'.', '.', '.', '.' },
                        {'.', '.', 'X', 'E' }
                     };


    display(n, n, arr);

    Point source;
    Point dest;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (arr[i][j] == START)
            {
                source = { i, j };
            }
            else if (arr[i][j] == END)
            {
                dest = { i, j };
            }

        }
    }

    cout << "Start: " << source.x << ", "<<source.y<<endl;
    cout << "End  : " << dest.x << ", "<<dest.y<< endl;

    // Path finding
    int dist = BFS(arr, source, dest);

    if (dist != INT_MAX)
        cout << "Shortest Path is " << dist;
    else
        cout << "Shortest Path doesn't exist";

    getchar();
    return 0;
}