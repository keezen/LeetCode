/*
207. Course Schedule
Medium


There are a total of numCourses courses you have to take, 
labeled from 0 to numCourses - 1. You are given an array 
prerequisites where prerequisites[i] = [ai, bi] indicates
that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 
you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

 
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course
0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 105
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
*/

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <unordered_set>
using namespace std;


template <typename T> ostream & operator<<(ostream &os, pair<T,T> &x)
{
    os << x.first << ',' << x.second;
}


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    // print out a vector
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i];
        cout << ((i == data.size() - 1) ? eol : sep);
    }
}


bool canFinishTopoSort(int numCourses, vector<vector<int>>& prerequisites)
{
    // whether there is not circle in graph
    // solution: topology sort, delete 0-indegree nodes recursively

    if (numCourses <= 0 || prerequisites.size() <= 0)
        return true;

    // count indegree with edges
    vector<int> indegree(numCourses, 0);
    vector<vector<int>> graph(numCourses, vector<int>());
    int i, p, q;
    for (i = 0; i < prerequisites.size(); i++)
    {
        p = prerequisites[i][0];
        q = prerequisites[i][1];
        graph[q].push_back(p);
        indegree[p]++;
    }

    // 0 indegree nodes
    vector<int> zeroin_nodes;
    for (i = 0; i < numCourses; i++)
        if (indegree[i] == 0)
            zeroin_nodes.push_back(i);

    // topology sort
    while (!zeroin_nodes.empty())
    {
        p = zeroin_nodes.back();
        zeroin_nodes.pop_back();
        for (i = 0; i < graph[p].size(); i++)
            if (--indegree[graph[p][i]] == 0)
                zeroin_nodes.push_back(graph[p][i]);
    }

    // whether there is no circle
    bool res = true;
    for (i = 0; i < numCourses; i++)
        if (indegree[i] > 0)
        {
            res = false;
            break;
        }

    return res; 
}


bool hasCycle(int vertex, vector<vector<int>> &graph, vector<int> &state)
{
    // whether current vertex contains cycle
    if (state[vertex] == -1)
        return true;
    if (state[vertex] == 1)
        return false;

    int i, u;
    state[vertex] = -1;
    for (i = 0; i < graph[vertex].size(); i++)
    {
        u = graph[vertex][i];
        if (hasCycle(u, graph, state))
            return true;
    }
    state[vertex] = 1;
    return false;
}


bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    // whether there is not circle in graph
    // solution: DFS with 3 states, 0 for unvisited, 1 for visited,
    //     -1 for currently visiting

    if (numCourses <= 0 || prerequisites.size() <= 0)
        return true;

    // build graph
    vector<vector<int>> graph(numCourses, vector<int>());
    int i, p, q;
    for (i = 0; i < prerequisites.size(); i++)
    {
        p = prerequisites[i][0];
        q = prerequisites[i][1];
        graph[q].push_back(p);
    }

    // DFS
    vector<int> state(numCourses, 0);
    for (i = 0; i < numCourses; i++)
        if (state[i] == 0 && hasCycle(i, graph, state))
            return false;

    return true; 
}


int main(int argc, char *argv[])
{
    fstream myfile("a.txt");

    bool res;

    string line;
    vector<vector<int>> grid;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        int x;
        vector<int> nums;
        while (ss >> x)
            nums.push_back(x);

        PrintVec(nums);
        grid.push_back(nums);
    }

    res = canFinish(5, grid);
    cout << res << endl;

    myfile.close();
    return 0;
}