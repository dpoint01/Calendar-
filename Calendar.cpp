//
//  Calendar.cpp
//
// by: David Pointeau
// date: Wed, March 5th, 2014
// Implementation of Calendar.h

#include "Calendar.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>

using namespace std;

const int Calendar::INIT_CAPACITY;

Calendar::Calendar(){
        dayList = new Day[INIT_CAPACITY];
        dayCapacity = INIT_CAPACITY;
        dayCount = 0;
}

Calendar::~Calendar(){
        delete [] dayList;
}

// addEvents() takes a CSV of events in the following format, 
// and adds them to a calendar:
// 2/25/2014,2/25/2014,1100,1115,Event A
// 2/25/2014,2/25/2014,1200,1230,Event B

// The addEvents() method needs to create a Day if 
// one does not exist for a particular
// event, and it needs to create events in that Day.
void Calendar::addEvents(string csvEvents) {
        // no student code necessary here
        stringstream eventStream;
        string eventLine;
        eventStream << csvEvents;
        
        date startDate;
        Event evt;
        Day *tempDay;
        
        while (getline(eventStream,eventLine)) {
                //cout << eventLine << endl;
                startDate = csvToStartDate(eventLine);
                evt = csvToEvent(eventLine);
                tempDay = getDay(startDate);
                
                if (tempDay==NULL) { // not found
                        tempDay = insertDay(startDate);
                }
                if (tempDay->scheduleEarliest(evt) == false) { // could not schedule the event!
                        cout << "Could not schedule the event: " 
			     << evt.eventCSV() << endl;
                }
        }
}

// indexOfDay() returns the index in dayList of
// startDate. If the Day does not exist,
// the function returns NULL
Day *Calendar::getDay(date startDate) {
    
    Day *sameDay = NULL; // Intialize to Null
    
    for(int i = 0; i < dayCount; i++){
        if(dayList[i].getDate().day == startDate.day &&
           dayList[i].getDate().month == startDate.month &&
           dayList[i].getDate().year == startDate.year){
            sameDay = &dayList[i];
            return sameDay;
        }
    }
    return NULL;
}

// insertDay() inserts a day into a calendar, keep the list in order by date
// This function returns a pointer to the Day so other functions 
// can insert events
// into that Day.
Day *Calendar::insertDay(date startDate) {

        Day *newDay = new Day(startDate);
    
        if (dayCount == dayCapacity) {
                expandList();
        }
        if(dayCount == 0){        //If list is empty, add at the beginning
            delete newDay;
	    dayList[0] = *newDay;
            dayCount++;
	    return &dayList[0];
        }
        else{
            // find the location where we need to insert the day
            int index;
	    bool added = false;
            for (index = 0;index < dayCount;index++) {
                if (newDay->isBefore(dayList[index])){
	      	    added = true;
		    break;
		}
            }
            // move the second to last item to the end, and then
            // continue down the list
	    for (int moveIndex= dayCount;moveIndex > index; moveIndex--) {
	            dayList[moveIndex] = dayList[moveIndex - 1];
	    } 
	   delete newDay;
	   dayList[index] = *newDay; // ADD
	   dayCount++;
           return &dayList[index];
	   //If it wasn't added, add to end
	   if(added == false){
	       delete newDay;
	       dayList[dayCount] = *newDay;
	       dayCount++;
	       return &dayList[dayCount];
	       }
        }
     return NULL;
}

void Calendar::printCalendar(){
    
    for(int i = 0; i < dayCount; i++){
        dayList[i].printDay();
    }
    cout << endl;
}

//---------------------------------------------------------------------------//




/////// Below this line are helper functions that have been pre-written ///////

// exports a full calendar in a format Google Calendar understands
// The first line needs to literally be the following:
// Start Date,End Date,Start Time,End Time,Subject\n
string Calendar::exportCalendarCSV() {
        stringstream fullCalendar;
        // input header into stringstream, e.g.:
        // fullCalendar << "The header information"
        
        fullCalendar << "Start Date,End Date,Start Time,End Time,Subject\n";
        
        // export each Day in turn
        
        for (int i=0;i<dayCount;i++) {
                fullCalendar << dayList[i].exportDay();
        }
        return fullCalendar.str();
}

void Calendar::expandList(){
        Day *tempList = new Day[dayCapacity * 2];
        for (int i=0;i<dayCapacity;i++) {
                tempList[i] = dayList[i];
        }
        delete [] dayList;
        dayList = tempList;
        dayCapacity = dayCapacity * 2;
}

// importCSV imports data from a Google Calendar export,
// starting at startYear
string Calendar::importCSV(string filename,int startYear) {
        // we will assume our time zone is GMT-5
        // i.e., if a time is 9pm Greenwich Mean Time,
        // we will convert it to 4pm
        //
        // look for DTSTART:, DTEND:, and SUMMARY:
        // ignore all other lines.
        // Example: DTSTART:20140224T143000Z
        //          DTEND:20140224T153000Z
        //          SUMMARY:Event Number One
        
        const string startTimeDelimiter = "DTSTART:";
        const string endTimeDelimiter = "DTEND:";
        const string summaryDelimiter = "SUMMARY:";
        
        string oneLine;
        ostringstream csvStream;
        
        string startDateString,startTimeString,
                endDateString,endTimeString;
        
        ifstream inputFile (filename.c_str());
        assert(inputFile); // must exist, or crash
        
        while(getline(inputFile, oneLine)){
                if (oneLine.find(startTimeDelimiter)==0) {
                        // strip DTSTART:
                        oneLine = oneLine.substr(startTimeDelimiter.length());
                        // the time will be 6-char string (ignore the Z)
                        // the date will be an 8-char string
                        
                        startTimeString = convertTimeSt(oneLine.substr(9,6));
                        
                        startDateString = convertDateSt(oneLine.substr(0,8),startTimeString);
                }
                else if (oneLine.find(endTimeDelimiter)==0) {
                        // strip DTSTART:
                        oneLine = oneLine.substr(endTimeDelimiter.length());
                        // the time will be 6-char string (ignore the Z)
                        // the date will be an 8-char string
                        
                        endTimeString = convertTimeSt(oneLine.substr(9,6));
                        
                        endDateString = convertDateSt(oneLine.substr(0,8),endTimeString);
                }
                else if (oneLine.find(summaryDelimiter)==0) {
                        // strip SUMMARY:
                        oneLine = oneLine.substr(summaryDelimiter.length());
                        
                        // now we can put together the CSV string
                        // first check if the year is >= startYear
                        if (dateStringToStruct(startDateString).year>=startYear) {
                                // it is, so we use this event
                                csvStream << startDateString << "," << endDateString << "," <<
                                             startTimeString << "," << endTimeString << "," <<
                                             oneLine << "\n";
                        }
                }
        }
        if (inputFile.bad()){
                perror("Error reading file!");
                exit(0);
        }
        inputFile.close();
        return csvStream.str();
}

string Calendar::convertDateSt(string dateString, string timeString){
        // the date string needs to be converted from the form:
        // 20140224
        //   to:
        // 02/24/2014
        //
        // We also have to back the date up one if the time is between
        // 1900 and 2359 (because of the GMT conversion), which
        // is why we need the time as well
        ostringstream dateStringStream;
        
        date d;
        int timeNum;
        
        istringstream(timeString) >> timeNum;
        
        istringstream(dateString.substr(4,2)) >> d.month;
        istringstream(dateString.substr(6,2)) >> d.day;
        istringstream(dateString.substr(0,4)) >> d.year;
        
        if (timeNum >= 1900) { // we went back one day, because of the GMT timezone
                d.day--;
                if (d.day==-1) {
                        d.month--;
                        if (d.month == 1  || d.month == 3 || d.month == 5 || d.month == 7 ||
                            d.month == 8 || d.month == 10 || d.month == 0) {
                                // months have 31 days
                                d.day = 31;
                                d.month--;
                        }
                        else if (d.month == 2){ // Feb
                                // leap year...
                                bool isLeapYear;
                                if (d.year % 400 == 0) isLeapYear = true;
                                else if (d.year % 100 == 0) isLeapYear = false;
                                else if (d.year % 4 == 0) isLeapYear = true;
                                else isLeapYear = false;
                                
                                if (isLeapYear) d.day = 29;
                                else d.day = 28;
                        }
                        else {
                                d.day = 30; // all other months
                        }
                        if (d.month == 0) {
                                d.month = 12; // December
                                d.year--;
                        }
                }
        }
        dateStringStream << d.month << "/" << d.day << "/" << d.year;
        return dateStringStream.str();
}

string Calendar::convertTimeSt(string timeSt) {
        // the time needs to be converted from GMT to GMT-5
        // original format is 133000 (1:30PM)
        // We also need to ignore the minutes
        // The result should be in the form HHMM
        int timeNum;
        ostringstream timeStringStream;
        
        // convert from string to num so we can perform arithmetic
        istringstream(timeSt) >> timeNum;
        timeNum = timeNum / 100;
        
        // GMT conversion, subtract five hours
        timeNum = timeNum-500;
        
        // if the time was before 5am, then we need to wrap around midnight
        if (timeNum < 0) timeNum = 2400+timeNum;
        
        // convert back from a num to a string
        timeStringStream << timeNum;
        return timeStringStream.str();
}

date Calendar::dateStringToStruct(string dateString){
        // dateString is in the form 2/22/2014
        // We have to split the string by "/"
        ostringstream stream;
        
        date theDate;
        size_t stringIndex = 0;
        // find month
        while(dateString[stringIndex]!='/'){
                stream << dateString[stringIndex];
                stringIndex++;
        }
        istringstream(stream.str()) >> theDate.month;
        stringIndex++; // skip the slash
        stream.str(std::string()); // clear the string buffer
        
        // find day
        while(dateString[stringIndex]!='/'){
                stream << dateString[stringIndex];
                stringIndex++;
        }
        istringstream(stream.str()) >> theDate.day;
        stringIndex++; // skip the slash
        stream.str(std::string()); // clear the string buffer
        
        // find year
        while(stringIndex!=dateString.length()){
                stream << dateString[stringIndex];
                stringIndex++;
        }
        istringstream(stream.str()) >> theDate.year;
        
        return theDate;
}

// returns the startDate of a CSV eventLine
date Calendar::csvToStartDate(string csvLine){
        return dateStringToStruct(csvLine.substr(0,csvLine.find(",",0)));
}

date Calendar::csvToEndDate(string csvLine){
        size_t index;
        // skip the first comma
        index = csvLine.find(",",0);
        return dateStringToStruct(csvLine.substr(index,csvLine.find(",",index+1)));
}

Event Calendar::csvToEvent(string csvLine){
        Event e;
        size_t index;
        int temp;
        
        // skip the first two commas to get to startTime
        index = csvLine.find(",",0);
        index = csvLine.find(",",index+1);
        istringstream(csvLine.substr(index+1,csvLine.find(",",index+1))) >> temp;
        e.setStartTime(temp);
        
        // get to endTime
        index = csvLine.find(",",index+1);
        istringstream(csvLine.substr(index+1,csvLine.find(",",index+1))) >> temp;
        e.setEndTime(temp);
        
        // get to endTime
        index = csvLine.find(",",index+1);
        e.setDescription(csvLine.substr(index+1));
        
        return e;
}
