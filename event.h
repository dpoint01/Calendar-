//
//  event.h
//
// Enter overview information here.


#ifndef __CalendarOrderedLists__event__
#define __CalendarOrderedLists__event__

#include <iostream>
using namespace std;

class Event{
public:
	Event(); // constructor
	Event(int startT, int endT, string desc);
	int getStartTime();
	int getEndTime();
	std::string getDescription();
	
	void setStartTime(int startT);
	void setEndTime(int endT);
	void setDescription(string str);
        
	bool amIBefore(Event otherEvent); // returns true if the event is before another event
        bool isSameEventAs(Event otherEvent); // returns true if the event is the same event as another event
        
        bool conflictsWith(Event anEvent); // returns true if the event conflicts with the other event
        
        void printEvent(); // prints the event as follows:
                           // Start Time: 1200
                           // End Time: 1300
                           // Description: Lunch (with two newlines)
                           //
	string eventCSV(); // returns a comma-separated-value string in the form:
                           //     startTime,endTime,description
        
        // converts an integer in 24-hour time (e.g., 1330) to
        // a string that is in 12-hour time with AM or PM, as follows:
        // The int 1330 becomes
        // the string "1:30 PM"
        static string convert24HourTime(int time24);
        
private:
	int startTime;
        int endTime;
        string description;
};

#endif /* defined(__CalendarOrderedLists__event__) */
