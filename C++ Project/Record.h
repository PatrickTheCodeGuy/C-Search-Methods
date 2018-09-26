/*
 Record.h
 
 Class for record data that will be inserted into hash table and BSTs
 Each record instancce has 5 variables which hold the record number (primary key), the artist (secondary key),
    the album, the year recorded, and the genre.
 
 Class functions include setters and getters, and an overloaded stream operator which prints the entire object to the screen.
 */

#ifndef Record_h
#define Record_h

using namespace std;
#include <string>
#include <fstream>
class Record
{
private:
    string recNum;
    string album;
    string year;
    string genre;
    string band;
    
public:
    
    //Record();
    
    //setter functions
    void setRecNum(string num) { recNum = num; }
    void setAlbum(string theAlbum) { album = theAlbum; }
    void setYear(string theYear) { year = theYear; }
    void setGenre(string type) { genre = type; }
    void setBand(string people) { band = people; }
    
    //getter functions
    string getRecNum() { return recNum; }
    string getAlbum() { return album; }
    string getYear() { return year; }
    string getGenre() { return genre; }
    string getBand() { return band; }
    
    
    friend ostream &operator << (ostream &output, Record &rec)
    {
        output << "Key: "<< rec.getRecNum() << " Album: " << rec.getAlbum() << " Artist: " << rec.getBand() << " Year: " << rec.getYear() << " Genre: "
            << rec.getGenre() << endl;
        return output;
    }
};
#endif /* Record_h */

