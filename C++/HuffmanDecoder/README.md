#Huffman Decoder

This program decodes a Huffman compressed message. 

It takes a Binary Tree input and Huffman encoded message and it will output the decoded message.


For this program I have decided to go with a Tree class that is organized by an array. Given that the user doesn't have to input nodes with their children in order, this makes it easier to search for a pre-existing node and to do any traversals. 

I decided to use stack for the pre-order function because that way you don't lose track of any nodes when traversing the tree

I used a stack in the degree function also because I used the pre-order function with a degree count where the cout statement is in the pre-order function. 