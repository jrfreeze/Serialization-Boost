/* This program uses Boost serialization to write to and read from
   an archive. It counts the number of elements in a vector to
   make sure the same number come out that went in. */

//
//  main.cpp
//  SerializationProg
//
//  Created by Joshua on 4/16/18.
//  Copyright © 2018 Joshua Freeze. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost\serialization\vector.hpp>
#include <boost\serialization\nvp.hpp>
#include <boost\archive\binary_iarchive.hpp>
#include <boost\archive\binary_oarchive.hpp>


using namespace std;

// Class to use in the vector
class our_dogs
{
public:
    string Name;
    string Breed;
    our_dogs(string name, string breed) { this->Name = name;  this->Breed = breed; }
    our_dogs(){}
    // Temlpate to make the archive work on the vector of the class
    template<typename Archive>
    void serialize(Archive &ar, const unsigned version) {ar & Name & Breed;}
};

int main() {
    
    // Create in and out vectors to hold information
    vector<our_dogs> vecout;
    vector<our_dogs> vecin;
    // Initialize the out vector
    vecout.push_back(our_dogs("Buddy", "Boston Terrier"));
    vecout.push_back(our_dogs("Frederick", "Dachshund"));
    vecout.push_back(our_dogs("Beauregard", "Basset Hound"));
    vecout.push_back(our_dogs("Devo", "Chiwhippet"));
    vecout.push_back(our_dogs("Rosa", "Puggle"));
    
    // How many before serialization
    cout << "Before serialization we have had " << vecout.size() << " dogs." << endl;
    
    // Open the stream and archive to write the vector
    ofstream output("dogs.txt");
    boost::archive::binary_oarchive binoarch(output);
    
    // Write the vector
    binoarch << vecout;
    output.close();  // Close the output stream
    
    // Open the stream and archive to read the vector
    ifstream input("dogs.txt");
    boost::archive::binary_iarchive biniarch(input);
    
    // Read the vector
    biniarch >> vecin;
    input.close(); // CLose the input stream
    
    cout
    // How many after serialization
    << "After serialization we have had " << vecin.size() << " dogs." << endl;
    
    cin.get();
    
    return 0;
}
