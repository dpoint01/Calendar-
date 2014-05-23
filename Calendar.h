//
//  Calendar.h
//
// Enter overview information here.

#ifndef __BetterCalendarOrderedLists__Calendar__
#define __BetterCalendarOrderedLists__Calendar__

#include <iostream>
#import "dayDynamicArray.h"

using namespace std;

class Calendar {
public:
        static const int INIT_CAPACITY = 5;

        Calendar(); // constructor
        ~Calendar(); // destructor
        
        // importCSV() reads from a file and makes a string that holds CSV
        // events in the form:
        // Start Date,End Date,Start Time,End Time,Subject
        // 2/24/2014,2/24/2014,9:30 AM,10:30 AM,Event Number One
        // 2/25/2014,2/25/2014,2:30 PM,3:40 PM,Event Number Two
        string importCSV(string filename,int startYear);
        
        // addEvents reads a string of events in CSV format and puts them into a calendar
        void addEvents(string csvEvents);
        
        // exportCalendarCSV exports a calendar to CSV values, with a header that Google
        // Calendar recognizes
        string exportCalendarCSV();
        
        // printCalendar prints an entire calendar
        void printCalendar();
        
private:
        Day *dayList;
        int dayCapacity;
        int dayCount;
        
        // private methods
        Day *getDay(date startDate);
        Day *insertDay(date startDate);
        
        
        // helper functions pre-written
        void expandList();
        
        // converts date strings from GMT time in the format 20140224
        // to 2/24/2014 format in the GMT-5 timezone
        string convertDateSt(string dateString, string timeString);
        
        // converts a time from 
        string convertTimeSt(string timeString);
        static date dateStringToStruct(string dateString);
        date csvToStartDate(string csvLine);
        date csvToEndDate(string csvLine);
        Event csvToEvent(string csvLine);
        
};

#endif /* defined(__BetterCalendarOrderedLists__Calendar__) */
