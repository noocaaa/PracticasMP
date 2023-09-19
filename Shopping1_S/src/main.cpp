/**
 * @file main.cpp
 * @author Manuel Fuentes Plaza && Noelia Carrasco Vilar
 * @date 23/03/2021
 */
#include <iostream>
#include <cstring>
#include <string>
#include <cassert>

#include "Event.h"
#include "MPTests.h"

using namespace std;

/**
 * @brief displays the content of the array by using the method to_string that easy to transfer data to stream.  The content remains constant
 * @param array of the Events
 * @param nEvent number of events in the array
 */
void print(const Event array[], int &nEvent);

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen in the following format
 * ~~~~
 *      SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0)
 *      +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 * @param arrayE an Event input array
 * @param nEvents number of events in arrayE
 * @param arrayA an int output array
 */
void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]);

/**
 * @brief Compute the  max number of activity events, and the day on which is produced
 * @param arrayA the counter of activities, an input array
 * @param ndays number of days
 * @param maxDay
 * @return maxActivity the counter of events of 
 */
int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays=7);


/**
 * @brief The main function of the program carries out the following procedure
 *   - It uses a static array of Events to store a sequence of events read from 
 * keyboard (likely to be redirected from a data file in the ./tests folder) - DONE
 *   - It reads the maximum number of valid records to be stored in the array. - DONE
 *   - If the event read is right (use the method isEmpty() to detect non-valid
 * records), it is stored in the array, otherwise, it is dismissed. Only valid records count. - DONE
 *   - Next, it computes the number of events found at each day of the week (complete the implementation
 * of the local function computeActivity() which also shows the result) -DONE
 *   - Next, it finds which is the day of highest activity recorded and show it on screen
 */
int main(int argc, char** argv) {
    
    const int DIM = 200; //tamanio array
    const int dias_semanas = 7;

    Event events[DIM];
    
    Event temporal;

    int activityWeek[dias_semanas];

    int n2Read = 0, nEvents = 0;
    int maxActivity, maxDay;
    
    string info_introducida;

    cout << "Number of events to read" << endl;
    
    cin >> n2Read;
        
    while (n2Read < 0 || n2Read > DIM) {
        cin >> n2Read;
    }
    
    getline(cin, info_introducida); //para el salto de linea
    
    for (int i=0; i < n2Read; i++) {
        
        getline(cin, info_introducida);
        
        temporal.set(info_introducida);
        
        if (!temporal.isEmpty()) {
            events[nEvents++] = temporal;
        }    
        
    }
    
    print(events, nEvents); 
    computeActivity(events, nEvents, activityWeek);
    maxActivity = computeMaxActivityDay(activityWeek, maxDay);
        
    CVAL << "Records read: " << n2Read << endl;
    CVAL << "Valid records: " << nEvents << endl;
    CVAL << "Max activity: " << maxActivity << endl;
    CVAL << "Day of Max activity: " << DAYNAME[maxDay] << endl;
}

void print(const Event array[], int & nEvent) {

    for (int i=0; i < nEvent; i++) {
        array[i].to_string();
    }
        
}

void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]){

    for (int day=0; day < 7; day++) {
        arrayA[day] = 0;
    }
    
    for (int i=0; i < nEvents; i++) {
        arrayA[arrayE[i].getDateTime().weekDay()] += 1;
    }
        
    CVAL << "Activity found:";
    for (int day2=0; day2<7; day2++) {
        CVAL << " " << DAYNAME[day2]<<"("<<arrayA[day2]<<")";
    }
    CVAL << endl;
}

int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays){
    
    int maxActivity = -1;
    maxDay = -1;
    
    for (int i=0; i < ndays; i++) {
        if (arrayA[i] > maxActivity) {
            maxActivity = arrayA[i];
            maxDay = i;
        }
    }
    
    return maxActivity;
}
