#Breadth First Spanning Tree
This program reads in a graph and then calculates and outputs the breadth first spanning tree.

I decided to set this graph up as a dynamic array of a struct called Vertex. 
This struct contained its own dynamic arrays of both the names of the vertices it is connected to and the edge lengths between them, with corresponding indexes. 
I decided to do this because we had to represent it as an adjacency list and it therefore made sense to do it as a list. 
So as to not get lost in an array full of vertices that had arrays full of vertices themselves. 
Since it only stores a string, I had to search for it, but it made referencing a lot easier. 

I also decided that as I'm reading in the graph if there is more than one edge between vertices, 
it only keeps the smaller one. For the purpose of this assignment, we only want the smaller one. 
For a basic graph-reading-in function, this feature should be taken out though. 
