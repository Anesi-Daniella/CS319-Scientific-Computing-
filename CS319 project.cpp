//
//  CS319 project.hpp
//  CS319 Project.cpp
//
//  Created by Anesi Daniella Igunma on 24/03/2019.
//  Copyright © 2019 Anesi Daniella Igunma. All rights reserved.

#include <iostream>
#include <random>

using namespace std;

// Declaring StarGraph method
// pointer to a pointer of a 2D array
int** StarGraph(int n, int k);

//main method
int main()
{
    //k randomly generated between 1 and 10
    //This is the ammount of spokes
    int k = (rand() % 10) + 1;
    
    //N is inputted by user
    //this is number of points
    //This must be >= 3 as you cant have a cycle grap with just 2 or less vertices
    int n = 0;
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    if (n < 3){
        cerr << "Number of nodes must be >= 3\n";
    }else{
        
        //define variable graph
        int** graph = StarGraph(n,k);
        //N is dimensions of array
        int N = n + (n*k);
        
        //Print Graph
        for (int i=0;i<N;i++){
            cout << "\n";
            for (int j=0;j<N;j++){
                cout << "[" << graph[i][j] << "]";
            }
        }
        
        //Algorithm
        //Demonstrate Friendship Paradox
        //Show that average number of friends is lower than average number of friends of friends.
        
        //First calculate average number of friends of each node of the graph.
        int m1 =0;
        for(int i=0;i<N;i++){
            int count = 0;
            for(int j=0;j<N;j++){
                count += graph[i][j];
            }
            m1 += count;
        }
        
        //Divide total by number of points for the average.
        m1 = pow(m1,2)/N;
        
        int m2 = 0;
        for(int i=0;i<N;i++){
            int count = 0;
            for(int j=0;j<N;j++){
                // if the
                if(graph[i][j]==1){
                    for(int k=0;k<N;k++){
                        count += graph[j][k];
                    }
                }
            }
            m2 += count;
        }
        
        if(m1<=m2){
            cout << "\nm1 <= m2. The Friendship Paradox holds.\n";
        }else{
            cout << "\nFriendship paradox proven false somehow.";
        }
    }
    return 0;
}
//Method 1: StarGraph creates and returns a 2d array representing paths of a star graph.
int** StarGraph(int n, int k){
    //Create graph of size n.
    //Set values to 0
    int** Graph = 0;
    Graph = new int*[n];
    for(int i=0;i<n;i++){
        Graph[i] = new int[n];
        //Set values to 0
        for(int j=0;j<n;j++){
            Graph[i][j] = 0;
        }
    }
    
    // Make it a cycle graph of size n.
    for (int i=0;i<n;i++){
        if(i!=n-1){
            Graph[i][(i+1)%n] = 1;
            Graph[(i+1)%n][i] = 1;
        }
    }
    
    //Get Dimensions of big matrix
    int N = n+(n*k);
    
    //Create big matrix
    int** g = 0;
    g = new int*[N];
    for(int i=0;i<N;i++){
        g[i] = new int[N];
        //Set values to 0
        for(int j=0;j<N;j++){
            g[i][j] = 0;
        }
    }
    
    //Puts small graph into top left corner of big graph
    cout << "Merging graphs!\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g[i][j] = Graph[i][j];
        }
    }
    
    //Sets edges connected points to spokes
    cout << "Reached spoke loop!\n";
    for (int i=0;i<n;i++){
        for (int j=0;j<k;j++){
            g[i][n+(i*k)+j] = 1;
            g[n+(i*k)+j][i] = 1;
        }
    }
    //cout << "Printing!";
    //for (int i=0;i<N;i++){
    //    cout << "\n";
    //    for (int j=0;j<N;j++){
    //        cout << "[" << g[i][j] << "]";
    //    }
    //}
    return g;
}

