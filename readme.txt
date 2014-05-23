// READ ME FILE//
// by: David Pointeau
// March, 5th 2014
// hw3 <-> calendarAssignement


Purpose of Program: This assignement is the part II to hw2. This program can 
		    handle multiple days for calendar, multiple months, 
	            handling calendar conflicts, and finding the next free
	            block of time in the day. It includes features that you can 
		    find in commercial calendars such as Google Calendar.

List of files: 1.event.h : classic implementation needed for handling events.
			   standard getters and setters. As opposed to hw2, this
			   program has two more functions: conflictsWith() and
			   convert24HourTime()
	       2.event.cpp
	       3.dayDynamicArray.h: handles a list of events in the same day.
				      most of the functions are the same as in
				      hw2. Yet, theres an added struct "date"
				      to keep track of the date of a particular 				      day.
	       4.dayDynamicArray.cpp: There are two functions we had to add.
				      scheduleEarliest() and nextFreeBlock().
				      We also had to update print day so it 
				      prints out the date too.
	       5.Calendar.h:The Calendar class is a dynamic arrat of Days.
			    Implmentation of the import functionality that reads
			    data into the CSV format from Google's export format
	       6.Calendar.cpp: Had to write, getDay(), InsertDay(), and 
			       printCalendar().
	       7.Main.cpp: Main is composed of 5 different tests. Handle them
			   with 0 or 1.

Outline of data structures: Basically, Calendar is dynamic array of Days, which
			    is a dynamic array of events. We don't pass the 
		            entire array from one files to another, but keep a
			    pointer pointing to the array and pass that around.

Outline of algorithms: Most of my comments in the files make it clear what my 
		       algorithms are. For insertDay and shcedule earliest, the
		       algorithms are pretty straightforward.
=>for nextFreeBlock(): What I basically do is that I first check if anEvent is smaller than all the other ones. If it is, I insert anEvent at its original time. If its not i move on to the nest test. I then test if anEvent is greater than the last event in the list (while making sure that it doesn't overlap to the enxt day. Then I loop through the list checking for conlifcts. If there is a conflict I break out of the loop. If there isn't than I insert anEvent at its original startTime. If there is a conflict, than I loop through the list lloking for a gap to insert anEvent. If there is a gap, I insert anEvent there, if there isnt
I add anEvent at the end of the list (while still checking it doesn't overlap to the nest day). 

				       
