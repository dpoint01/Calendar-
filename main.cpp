//
//  main.cpp
//


#define TEST_convert24HourTime 0
#define TEST_printDay 0
#define TEST_nextFreeBlock 0
#define TEST_importA 0
#define TEST_importB 0
#define TEST_importC 1

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "dayDynamicArray.h"
#include "Calendar.h"

void shuffleEvents(Event *events,int eventCount);

int main()
{
        /////////// starting tests
#if TEST_convert24HourTime
        // TEST for properly converting an integer 24-hour time (e.g., 1330)
        //      to a string in the format "1:30 PM"
        //
        // The test will:
        //      attempt to convert four different times
        //
        // What should happen:
        //      The four times should be converted properly
        //
        // Test:  Create the times "1330","0000","930","2359"
        //      Then convert them using Event's convert24HourTime() function
        //
        // Output Expected:
        //      1:30 PM
        //      12:00 AM
        //      9:30 AM
        //      11:59 PM
        //
        // staring test
        cout << "Test: convert24HourTime---------\n";
        cout << "-----Expected output:\n";
        cout << "1:30 PM\n";
        cout << "12:00 AM\n";
        cout << "9:30 AM\n";
        cout << "11:59 PM\n";
        cout << "-----End of expected output\n\n";
        
        cout << "-----Actual output:\n";
        // Create four times
        int timeA = 1330;
        int timeB = 0;
        int timeC = 930;
        int timeD = 2359;
        
        // convert and print out the times
        cout << Event::convert24HourTime(timeA) << endl;
        cout << Event::convert24HourTime(timeB) << endl;
        cout << Event::convert24HourTime(timeC) << endl;
        cout << Event::convert24HourTime(timeD) << endl;
        
        cout << "-----End of Actual output\n\n";
        cout << "Finished testing convert24HourTime\n\n";
        
#elif TEST_printDay
        // TEST for printDay functionality
        //
        // The test will:
        //      add a day and two events, then print the day
        //
        // What should happen:
        //      the day should print with the date as well
        //
        // Test:  Create a Date and a Day, then create two
        //        events, add them to a Day, then print the Day
        //
        cout << "Test: printDay ---------\n";
        cout << "-----Expected output:\n";
        cout << "Date: 2/1/2014\n";
        cout << "Start Time: 10:00 AM\n";
        cout << "End Time: 11:00 AM\n";
        cout << "Description: Event 1\n";
        cout << "\n";
        cout << "Start Time: 11:15 AM\n";
        cout << "End Time: 1:30 PM\n";
        cout << "Description: Event 2\n\n";
        cout << "-----End of expected output\n\n";
        
        cout << "-----Actual output:\n";
        // add a Day
        date theDate;
        theDate.year = 2014;
        theDate.month = 2;
        theDate.day = 1;
        
        Day d(theDate);
        
        // add some events
        Event e1(1000,1100,"Event 1");
        Event e2(1115,1330,"Event 2");
        
        // schedule the events
        d.scheduleEvent(e1);
        d.scheduleEvent(e2);
        
        // print the day
        d.printDay();
        
        cout << "-----End of Actual output\n\n";
        cout << "Finished testing printDay\n\n";
        
#elif TEST_nextFreeBlock
        // TEST for nextFreeBlock function
        //
        // The test will:
        //      create three Events (9am-10am, 11am-12pm, 1pm-2pm)
        //      and schedule them in a Day
        //      then print an exported Day
        //      Then it will call the nextFreeBlock() function
        //      on an event that should end up as the last event of
        //      the day (9:30am-12:30pm). Finally, it will call the nextFreeBlock()
        //      function on an Event for which there is no free block (11am-9pm)
        //
        // What should happen:
        //      The first three events should be scheduled appropriately
        //      The next event should return with the correct time for
        //      the next free block in the Day (1400)
        //      The last event should return -1 because it should not be scheduled
        //
        // Test:  See above
        
        cout << "Test: nextFreeBlock ---------\n";
        cout << "-----Expected output:\n";
        cout << "Date: 2/1/2014\n";
        cout << "Start Time: 9:00 AM\n";
        cout << "End Time: 10:00 AM\n";
        cout << "Description: Event 1\n";
        cout << "\n";
        cout << "Start Time: 11:00 AM\n";
        cout << "End Time: 12:00 PM\n";
        cout << "Description: Event 2\n";
        cout << "\n";
        cout << "Start Time: 1:00 PM\n";
        cout << "End Time: 2:00 PM\n";
        cout << "Description: Event 3\n\n";
        cout << "Next free block, event 4: 1400\n";
        cout << "Next free block, event 5: -1\n";
        cout << "-----End of expected output\n\n";
        
        cout << "-----Actual output:\n";
        // add a Day
        date theDate;
        theDate.year = 2014;
        theDate.month = 2;
        theDate.day = 1;
        
        Day d(theDate);
        
        // add some events
        Event e1(900,1000,"Event 1");
        Event e2(1100,1200,"Event 2");
        Event e3(1300,1400,"Event 3");
        Event e4(900,1000,"Event 4");
        Event e5(1100,2100,"Event 5");
        
        // schedule the first three events
        d.scheduleEvent(e1);
        d.scheduleEvent(e2);
        d.scheduleEvent(e3);
        
        // print the day
        d.printDay();
        
        // call nextFreeBlock() on both events in Day
        cout << "Next free block, event 4: " << d.nextFreeBlock(e4) << endl;
        cout << "Next free block, event 4: " << d.nextFreeBlock(e5) << endl;
        
        cout << "-----End of Actual output\n\n";
        cout << "Finished testing printDay\n\n";
        
#elif TEST_importA
        // imports a number of events from disk and prints
        // See TEST_importA.txt for expected output
        Calendar cal;
        string events = cal.importCSV("randomEvents1Day.txt",2013);
        cal.addEvents(events);
        cal.printCalendar();
        
#elif TEST_importB
        // imports a number of events from disk and prints
        // See TEST_importB.txt for expected output
        Calendar cal;
        string events = cal.importCSV("randomEventsMultipleDays.txt",2013);
        cal.addEvents(events);
        //cal.printCalendar();
        cout << cal.exportCalendarCSV() << endl;
        
#elif TEST_importC
        // imports a number of events from disk and prints
        // See TEST_importC.txt for expected output
        Calendar cal;
        string events = cal.importCSV("randomEventsWithOverlap.txt",2013);
        cal.addEvents(events);
        cal.printCalendar();
#endif
        
}
