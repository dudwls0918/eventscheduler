#pragma once
#include "Date.h"

class Event {
private:
    static int event_counter;
    int id;
protected:
    string content;
public:
    Event();
    Event(string cont);
    virtual ~Event();
    int get_id();
    bool contains(string keyword);
    virtual bool relevant_to(string& day) = 0;
    virtual void print(ostream& out);
    virtual void savefile(ofstream& outfile) = 0;
    
};

class OneDayEvent : public Event {
private:
    Date date;
public:
    OneDayEvent();
    OneDayEvent(Date d, string str);
    bool relevant_to(string& theDay);
    void print(ostream& out);
    void savefile(ofstream& outfile);
    
};

class PeriodEvent : public Event {
private:
    Date begin, end;
public:
    PeriodEvent();
    PeriodEvent(Date d1, Date d2, string str);
    bool relevant_to(string& theDay);
    void print(ostream& out);
    void savefile(ofstream& outfile);
    
};

class DeadlineEvent : public Event {
private:
    Date deadline;
public:
    DeadlineEvent();
    DeadlineEvent(Date d, string str);
    bool relevant_to(string& theDay);
    void print(ostream& out);
    void savefile(ofstream& outfile);
    
};