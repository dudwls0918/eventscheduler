#include "Event.h"
#include<fstream>

int Event::event_counter = 0;

Event::Event() {
    id = event_counter++;
}

Event::Event(string cont) : content(cont) {
    id = event_counter++;
}

Event::~Event() {};

int Event::get_id() {
    return id;
}

bool Event::contains(string keyword) {
    if (content.find(keyword) != string::npos)
        return true;
    return false;
}

void Event::print(ostream& out) {
    out << id << ". ";
}

OneDayEvent::OneDayEvent() = default;
OneDayEvent::OneDayEvent(Date d, string str) : Event(str), date(d) {}

bool OneDayEvent::relevant_to(string& theDay) {
    Date begin, end;
    int start = 0, last = 0;
    while (last < theDay.length() && theDay.at(last) != '-') last++;
    begin = (theDay.substr(start, last));
    start = last + 1;
    end = (theDay.substr(start));
    
    return begin <= date and end >= date;
}

void OneDayEvent::print(ostream& out) {
    Event::print(out);
    date.print(out);
    out << ":" << content;
}
void OneDayEvent::savefile(ofstream& outfile) {
    date.savefile(outfile);
    outfile << " " << content;
}


PeriodEvent::PeriodEvent() = default;
PeriodEvent::PeriodEvent(Date d1, Date d2, string str) : Event(str), begin(d1), end(d2) {}

bool PeriodEvent::relevant_to(string& theDay) {
    Date one, two;
    int start = 0, last = 0;
    while (last < theDay.length() && theDay.at(last) != '-') last++;
    one = (theDay.substr(start, last));
    start = last + 1;
    two = (theDay.substr(start));
    

    return (begin <= two && end >= one);
}

void PeriodEvent::print(ostream& out) {
    Event::print(out);
    begin.print(out);
    out << "-";
    end.print(out);
    out << ":" << content;
}
void PeriodEvent::savefile(ofstream& outfile) {
    begin.savefile(outfile);
    outfile << "-";
    end.savefile(outfile);
    outfile << " " << content;
}

DeadlineEvent::DeadlineEvent() = default;
DeadlineEvent::DeadlineEvent(Date d, string str) : Event(str), deadline(d) {}

bool DeadlineEvent::relevant_to(string& theDay) {
    Date begin, end;
    int start = 0, last = 0;
    while (last < theDay.length() && theDay.at(last) != '-') last++;
    begin = (theDay.substr(start, last));
    start = last + 1;
    end = (theDay.substr(start));
    return end <= deadline;
}

void DeadlineEvent::print(ostream& out) {
    Event::print(out);
    out << "~";
    deadline.print(out);
    out << ":" << content;
}
void DeadlineEvent::savefile(ofstream& outfile) {
    outfile << "~";
    deadline.savefile(outfile);
    outfile << " " << content;
}