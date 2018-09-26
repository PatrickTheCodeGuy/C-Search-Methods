//
//  main.cpp
//  22C_GroupProject
//
//  Created by Tiffany Verner, James Martin, Patrick Thompson on 11/30/17.
//  
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HashTable.h"
#include "BinarySearchTree.h"

using namespace std;

// shows menu for switch statement 
void displayMenu()
{
	cout << "A - Add new record" << endl;
	cout << "D - Delete record" << endl;
	cout << "S - Search for record" << endl;
	cout << "L - List records" << endl;
	cout << "W - Write all data to file" << endl;
	cout << "T - Display statistics" << endl;
	cout << "Q - Quit" << endl;

}

//function to pass to BST traversal to print 
void display(Record* & aRecord)
{
	cout << *aRecord;
}

// create a new record from user input 
Record  *createRecord()
{
	Record *tempRec = new Record();
	string line;

	string tempKey;
	string tempAlbum;
	string tempArtist;
	string tempYear;
	string tempGenre;
	cin.clear();
	cin.ignore();
	cout << "Enter record number: ";
	getline(cin,tempKey);
	cout << "Enter album name: ";
	getline(cin, tempAlbum);
	cout << "Enter artist name: ";
	getline(cin,tempArtist);
	cout << "Enter release year: ";
	getline(cin,tempYear);
	cout << "Enter genre: ";
	getline(cin,tempGenre);

	tempRec->setAlbum(tempAlbum);
	tempRec->setRecNum(tempKey);
	tempRec->setBand(tempArtist);
	tempRec->setYear(tempYear);
	tempRec->setGenre(tempGenre);
	return tempRec;
}

int main()
{
	cout << "Music Store Database" << endl;
	cout << endl << "This program manages a database of music albums" << endl;
	cout << endl << "Developers: James Martin, Tiffany Verner, Patrick Thompson" << endl << endl;
    //counters for staistics function
    int totalCollisions = 0; 
	int count = 0;

    ifstream inFile;
    inFile.open("records.txt");

    HashTable *table = new HashTable(53);
	BinarySearchTree<Record*> *searchTree = new BinarySearchTree<Record*>;
	BinarySearchTree<Record*> *primarySearchTree = new BinarySearchTree<Record*>;
    while (!inFile.eof())
    {
        Record *tempRec = new Record();
        string line;
        
        string temp;
        string tempKey;
        string tempAlbum;
        string tempArtist;
        string tempYear;
        string tempGenre;
        
        getline(inFile, line);
        stringstream str(line);

        getline(str, tempKey, ',');
        getline(str, tempAlbum, ',');
        getline(str, tempArtist, ',');
        getline(str, tempYear, ',');
        getline(str, tempGenre, ',');

        tempRec->setAlbum(tempAlbum);
        tempRec->setRecNum(tempKey);
        tempRec->setBand(tempArtist);
        tempRec->setYear(tempYear);
        tempRec->setGenre(tempGenre);
		searchTree->insert(tempRec);
		primarySearchTree->insertByNumber(tempRec);
        table->insert(tempRec,totalCollisions);
		count++;
    }

    inFile.close();

	displayMenu();
	char choice = ' ';
	string num;
	while (choice != 'Q')
	{
		cout << "Enter your selection(M to show menu): ";
		cin >> choice;
		switch (choice)
		{
		case 'A':
			Record *newRec;
			newRec = createRecord();
			searchTree->insert(newRec);
			table->insert(newRec, count);
			primarySearchTree->insertByNumber(newRec);
			break;
		case 'D':
			cout << "Enter a record number to delete: ";//hash search
			cin.clear();
			cin.ignore();
			cin >> num;
			Record * foundRecord;
			if (table->search(num, foundRecord))
			{
				primarySearchTree->remove(foundRecord);
				searchTree->remove(foundRecord);
				//table->deleteHash(num);
				//delete foundRecord;
			}
			else
				cout << "Not found" << endl;
			break;
		case 'S':
			int searchType;
			cout << "How do you want to search?\n 1 - by record number\n 2 - by artist (all albums)\n";
			//cin >> searchType;
			while (!(cin >> searchType))//as long as the number entered is not an int or negative, keep checking
			{
				cout << "Invalid input. Please, try again: ";
				cin.clear();//clear input buffer
				cin.ignore(INT_MAX, '\n');
			}
			if (searchType == 1)
			{
				cout << "Enter a record number to search for: ";//hash search
				string num;
				cin >> num;
				Record * foundRecord;
				if (table->search(num, foundRecord))
					cout << *foundRecord << endl;
				else
					cout << "Not found" << endl;
			}
			else if (searchType == 2)
			{
				string artist;
				cout << "Enter artist to search: ";
				cin.clear();
				cin.ignore();
				getline(cin,artist);
				searchTree->printNodes(artist);//BST search, display all results
			}
			else
				cout << "Invalid selection.\n";
			break;
		case 'L':
			char choice;
			choice = ' ';
			cout << "How do you want the data listed?\n U - unsorted\n N - Sorted by record number\n B - Sorted by band\n ";
			cin >> choice;
			switch (choice)
			{
			case 'U':
				table->printTable();
				break;
			case 'N':
				primarySearchTree->inOrder(display);
				break;
			case 'B':
				searchTree->inOrder(display);
				break;
			}
			break;
		case 'W':
			cout << "written to file"<< endl;
			break;

		case 'M':
			displayMenu();
			break;
		case 'T':
			table->statistics(totalCollisions, count);
		case 'Q':
			//
			break;

		}
	}
    
    return 0;
}

