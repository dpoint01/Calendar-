//
//  event.cpp
//
// By David Pointeau
// Date: Wed, March 4th 2014
// Implementation of event.h


#include "event.h"
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

Event::Event() { // constructor
        startTime = 0;
        endTime = 2359;
        description = "";       
}

Event::Event(int startT, int endT, string desc) {
        startTime = startT;
        endTime = endT;
        description = desc;
}

int Event::getStartTime() {
        return startTime;
}

int Event::getEndTime() {
        return endTime;
}

std::string Event::getDescription() {
        return description;
}

void Event::setStartTime(int startT) {
        startTime = startT;
}

void Event::setEndTime(int endT) {
        endTime = endT;
}

void Event::setDescription(string str) {
        description = str;
}

bool Event::amIBefore(Event otherEvent) {
        if (startTime < otherEvent.getStartTime()) {
                return true;
        }
        return false;
}

bool Event::isSameEventAs(Event otherEvent) {
        if (startTime == otherEvent.getStartTime() &&
         endTime == otherEvent.getEndTime() &&
         description == otherEvent.getDescription())
                return true;
        return false;
}

// conflictsWith returns true if this event overlaps with another event
// during the day
// events can "touch" but not overlap. I.e., one event can end
// at the same time the next event begins and this is not an overlap

//NOTE: I check if they don't conflict instead of checking if they do
bool Event::conflictsWith(Event anEvent) {
    
    if(endTime <= anEvent.getStartTime() && startTime < anEvent.getStartTime()){
	return false;
    }
    else if(startTime >= anEvent.getEndTime() && endTime>anEvent.getEndTime()){
	    return false;
    }

    return true;

}


void Event::printEvent(){
        cout << "Start Time: " << convert24HourTime(startTime) << "\n";
        cout << "End Time: " << convert24HourTime(endTime) << "\n";
        cout << "Description: " << description << "\n\n";
}

string Event::eventCSV() {
        string EventString = convert24HourTime(startTime) + "," +
                                convert24HourTime(endTime) + "," +
                                description;
        return EventString;
        
}

// converts an integer in 24-hour time (e.g., 1330) to
// a string that is in 12-hour time with AM or PM, as follows:
// The int 1330 becomes
// the string "1:30 PM"
string Event::convert24HourTime(int time24){
    
    	string fullTime;
        ostringstream hour_oss,minute_oss;
	
	//Initalize meridiem to AM
	string meridiem = "AM";
        
        int hourNum, minuteNum;
        int newHourNum;

     	hourNum = time24 / 100;
	minuteNum = time24 % 100;

	if (hourNum > 11 && hourNum < 24){
	    meridiem = "PM";
	}
	if(hourNum >= 13){
	    newHourNum = hourNum - 12;
	}
	else if (hourNum == 0){
	    newHourNum = 12;
	}
        else {
       	    newHourNum = hourNum;
        }    
    //corner case where we have to add a 0 after the minute
    if(minuteNum == 0){
        hour_oss << newHourNum;
        minute_oss << minuteNum;

        fullTime = hour_oss.str() + ":" + minute_oss.str() + "0" + " " + 
		   meridiem;
        return fullTime;
    }
    //corner case where we have to add a 0 before the minute
    else if(minuteNum > 0 && minuteNum <= 9){
        hour_oss << newHourNum;
        minute_oss << minuteNum;
        
        fullTime = hour_oss.str() + ":" + "0" + minute_oss.str() + " " + 
		   meridiem;
        return fullTime;
    }
    else{
        hour_oss << newHourNum;
        minute_oss << minuteNum;
        
        fullTime = hour_oss.str() + ":" + minute_oss.str() + " " + 
		   meridiem;
        return fullTime;
    }
}
