
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct report {
    string report;
    string name;
    int cnic;
};

struct info {
    string name;
    int ticketid;
    int trainid;
    int age;
    char gender;
    int phnum;
};
struct train {
    int trainID;
    string name;
    string route_name;
    int capacity;
    string dep_time;
    string arrival_time;
};
struct passenger {
    string passname;
    int age;
    char gender;
    int id;
    int phnum;
};
struct tickets {
    int bookid;
    int seat_num;
    passenger p;

};

int Trainmenu();
int admin_menu();
int passenger_menu();
void managetrain();
bool trainidcheck(int id);
void addtrain();
void passengermanagment();
void removetrain();
void edittrain();
void bookticket();
void reports();
void viewtrainshedule();
void viewtrainshedule2();
void cancelTicket();
void vreport();



int Trainmenu()
{

    string occ = "";

    while (true) {
        cout << "-----Are you a passenger or admin:-----" << endl;
        cin >> occ;
        cin.ignore();


        if (occ == "admin" || occ == "Admin" || occ == "ADMIN") {
            int attempts = 0;
            int max_try = 3;
            int pass;
            while (attempts < max_try) {
                cout << "Enter password: ";
                cin >> pass;
                cin.ignore();

                if (pass == 12345) {
                    cout << "-----WElcome to train Management System-----" << endl;
                    admin_menu();
                    return 0;
                }
                else {
                    attempts++;
                    if (attempts < max_try) {
                        cout << "YOu have entered wrong password || " << (max_try - attempts)
                            << "  atteampts remaining ||" << endl;
                    }
                }
            }

            cout << "You have entered wrong password for three times." << endl;
            return 0;

        }
        else if (occ == "passenger") {
            cout << "-----Welcome to passenger menu----" << endl;
            passenger_menu();
            return 0;
        }
        else {
            cout << "Invalid input.exiting" << endl;
        }
        return 0;
    }


}
int admin_menu() {
    cout << "ADMIN MENU:" << endl;
    cout << "1.MANAGE TRAIN:" << endl;
    cout << "2.BOOK TICKETS:" << endl;
    cout << "3.CANCEL TICKET:" << endl;
    cout << "4.PASSENGER MANAGEMENT:" << endl;
    cout << "5.VIEW TRAIN SHEDULE:" << endl;
    cout << "6.vIEW REPORTS:" << endl;
    cout << "7.EXIT:" << endl;
    cout << "8.MAIN MENU:" << endl;
    int choose;
    cin >> choose;
    switch (choose) {
    case 1:
        managetrain();
        break;
    case 2:
        bookticket();
        break;
    case 3:
        cancelTicket();
        break;
    case 4:
        passengermanagment();
        break;
    case 5:
        viewtrainshedule();
        break;
    case 6:
        vreport();
        break;
    case 8:
        Trainmenu();
        break;

    default:
        cout << "Thank You for using!";
        return 0;
    }
    return 0;
}
int passenger_menu() {
    cout << "MENU:" << endl;
    cout << "2.BOOK TICKETS:" << endl;
    cout << "3.CANCEL TICKET:" << endl;
    cout << "5.VIEW TRAIN SHEDULE:" << endl;
    cout << "6.REPORTS:" << endl;
    cout << "7.EXIT:" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 2:
        bookticket();
        break;
    case 3:
        cancelTicket();
        break;
    case 5:
        viewtrainshedule2();
        break;
    case 6:
        vreport();
        break;
    default:
        cout << "Exiting the system." << endl;
        return 0;
    }
    return 0;
}
void managetrain() {
    int choice;
    cout << "Manage Train Menu" << endl;
    cout << "1.Add trains" << endl;
    cout << "2.Remove trains" << endl;
    cout << "3.Edit trains" << endl;
    cout << "4.Admin menu" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        addtrain();
        break;
    case 2:
        removetrain();
        break;
    case 3:
        edittrain();
        break;
    default:
        admin_menu();
    }
}

bool trainidcheck(int id) {
    int fileid;
    ifstream inputfile;
    inputfile.open("trains.txt");
    if (!inputfile) {
        cout << "Error opening the file.";
        return true;
    }
    string eachline;
    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        stream >> fileid;
        if (fileid == id) {
            return false;
        }
    }
    inputfile.close();
}

void addtrain() {
    ofstream inputfile;
    inputfile.open("trains.txt", ios::app);
    if (!inputfile) {
        cout << "Error opening the file.";
    }
    else {
        train new_train;
        cout << "Enter the train ID:";
        while (true) {
            cin >> new_train.trainID;
            if (trainidcheck(new_train.trainID)) {
                break;
            }
            else {
                cout << "The train id already exist plz enter a unique id.";
            }

        }
        cout << "Enter the train Name:";
        cin.ignore();
        getline(cin, new_train.name);
        cout << "Enter the route for the train:";
        getline(cin, new_train.route_name);
        cout << "Enter the capacity of the train:";
        cin >> new_train.capacity;
        cout << "Enter the the departure time for the train:";
        cin.ignore();
        getline(cin, new_train.dep_time);
        cout << "Enter the arrival time of the train:";
        getline(cin, new_train.arrival_time);

        inputfile << new_train.trainID << ","
            << new_train.name << ","
            << new_train.route_name << ","
            << new_train.capacity << ","
            << new_train.dep_time << ","
            << new_train.arrival_time << endl;


        inputfile.close();
        cout << "Train added successfully." << endl;

        managetrain();
    }

}
void removetrain() {

    int remove_id;
    cout << "Enter the train id to remove the train:";
    cin >> remove_id;
    ifstream  inputfile;
    ofstream tempfile;
    inputfile.open("trains.txt");
    tempfile.open("temp.txt");
    if (!inputfile || !tempfile) {
        cout << "Error opening the files.";
        return;
    }
    string eachline;
    bool found = false;
    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        int train_id;
        stream >> train_id;
        if (train_id == remove_id) {
            found = true;
            cout << "Train with id " << remove_id << " remove successfully." << endl;
            continue;
        }
        tempfile << eachline << endl;
    }
    inputfile.close();
    tempfile.close();

    if (found) {
        remove("trains.txt");
        rename("temp.txt", "trains.txt");
    }
    else {
        cout << "Train id not found." << endl;
        remove("temp.txt");
    }
    managetrain();

}
void edittrain() {
    int trainID;
    string name = "";
    string route_name = "";
    int capacity = 0;
    string dep_time = "";
    string arrival_time = "";
    int edit_id;
    cout << "Enter the train Id to Edit:";
    cin >> edit_id;
    ifstream  inputfile;
    ofstream tempfile;
    inputfile.open("trains.txt");
    tempfile.open("temp.txt");
    if (!inputfile || !tempfile) {
        cout << "Error opening the files.";
        return;
    }
    string eachline;
    bool found = false;
    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        string temp;
        getline(stream, temp, ',');
        trainID = stoi(temp);
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');

        if (trainID == edit_id) {
            found = true;
            cout << "Train found. current details:" << endl;
            cout << "Train ID: " << trainID << "\nTrain Name: " << name << "\nroute:" << route_name << "\ncapacity: " << capacity
                << "\nDeparture time: " << dep_time << "\narrival time:" << arrival_time;

            cout << "\nEnter the new details:";
            cout << "Name:";
            cin.ignore();
            getline(cin, name);
            cout << "Route:";
            getline(cin, route_name);
            cout << "capacity:";
            cin >> capacity;
            cout << "Departure Time:";
            cin >> dep_time;
            cout << "Arrival time:";
            cin >> arrival_time;

            tempfile << trainID << "," << name << "," << route_name << ","
                << capacity << "," << dep_time << "," << arrival_time << endl;
            cout << "Train with ID: " << trainID << " Updated successfully.";
            continue;

        }
        tempfile << eachline;
    }
    inputfile.close();
    tempfile.close();
    if (found) {
        remove("trains.txt");
        rename("temp.txt", "trains.txt");
    }
    else {
        cout << "Train ID not found.";
        remove("temp.txt");
    }
    cout << "\n";
    managetrain();


}
void bookticket() {
    string trainname;
    cout << "Enter the train name you want to travel: ";
    cin.ignore();
    getline(cin, trainname);

    ifstream inputfile;
    inputfile.open("trains.txt");
    if (!inputfile) {
        cout << "Error opening the file." << endl;
        return;
    }

    int id;
    string name;
    string route_name;
    int capacity;
    string dep_time;
    string arrival_time;
    string eachline;
    bool trainfound = false;
    vector<int> matchingtrainids;

    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        string temp;

        getline(stream, temp, ',');
        id = stoi(temp);
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');

        if (trainname == name) {
            matchingtrainids.push_back(id);
            cout << "Train ID: " << id << " Route: " << route_name << "capacity " << capacity
                << " Departure time: " << dep_time << " Arrival time: " << arrival_time << endl;
            trainfound = true;
        }
    }

    inputfile.close();
    if (!trainfound) {
        cout << "No train found with this name: " << trainname << endl;
        return;
    }
    int selecttrainId;
    cout << "Enter the train Id to proceed with the booking: ";
    cin >> selecttrainId;

    ifstream ticketfile;
    ticketfile.open("tickets.txt");
    if (!ticketfile) {
        cout << "Error opening the file." << endl;
        return;
    }

    int Tid, trainid;

    string Name;
    int ticketsold = 0;
    while (getline(ticketfile, eachline)) {
        stringstream stream(eachline);
        stream >> Tid;
        stream.ignore();
        stream >> trainid;
        if (selecttrainId == trainid) {
            ticketsold++;
        }
    }
    ticketfile.close();

    string temp;
    int Id;
    int train_capacity;
    string Route;
    ifstream checkfile;
    checkfile.open("trains.txt");
    if (!checkfile) {
        cout << "Error opening the file." << endl;
        return;
    }

    while (getline(checkfile, eachline)) {
        stringstream stream(eachline);
        getline(stream, temp, ',');
        Id = stoi(temp);
        getline(stream, Name, ',');
        getline(stream, Route, ',');
        getline(stream, temp, ',');
        train_capacity = stoi(temp);

        if (Id == selecttrainId) {
            break;
        }
    }
    if (ticketsold >= train_capacity) {
        cout << "Sorry, the train is fully booked!" << endl;
        return;
    }
    checkfile.close();


    passenger newpassenger;
    cout << "Enter the Passenger Name: ";
    cin.ignore();
    getline(cin, newpassenger.passname);
    cout << "Enter the age: ";
    cin >> newpassenger.age;
    cin.ignore();
    cout << "Enter the Gender (M/F): ";
    cin >> newpassenger.gender;
    cin.ignore();
    cout << "Enter the ID: ";
    cin >> newpassenger.id;
    cin.ignore();
    cout << "Enter the phone number: ";
    cin >> newpassenger.phnum;
    cin.ignore();

    // Add passenger to the "passenger.txt" file
    ofstream passengerfile;
    passengerfile.open("passenger.txt", ios::app);
    passengerfile << newpassenger.id << "," << newpassenger.passname << ","
        << newpassenger.age << "," << newpassenger.gender << ","
        << newpassenger.phnum << endl;
    passengerfile.close();

    // Generate a random ticket ID
    int ticketID = rand();
    tickets Newticket;
    Newticket.bookid = ticketID;
    Newticket.p = newpassenger;

    // Add ticket to the "tickets.txt" file
    ofstream ticketsfile;
    ticketsfile.open("tickets.txt", ios::app);
    ticketsfile << Newticket.bookid << "," << selecttrainId << "," << Newticket.p.passname << ","
        << Newticket.p.age << "," << Newticket.p.gender << "," << Newticket.p.phnum << endl;
    ticketsfile.close();

    //minusing the capacity
    bool found = false;
    int train_id;
    ofstream tempfile;
    tempfile.open("temp.txt");
    ifstream trainfile;
    trainfile.open("trains.txt");

    while (getline(trainfile, eachline)) {
        stringstream stream(eachline);
        getline(stream, temp, ',');
        train_id = stoi(temp);
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        train_capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');
        if (train_id == selecttrainId) {
            cout << "Train ID: " << train_id << " Route: " << route_name
                << " Departure time: " << dep_time << " Arrival time: " << arrival_time << endl;
            found = true;
            train_capacity--;

            tempfile << train_id << "," << name << "," << route_name << ","
                << train_capacity << "," << dep_time << "," << arrival_time << endl;
            continue;

        }
        tempfile << eachline << endl;
    }
    trainfile.close();
    tempfile.close();

    if (found) {
        remove("trains.txt");
        rename("temp.txt", "trains.txt");
    }

    cout << "Ticket successfully booked!" << "Your Ticket Number is: " << ticketID << endl;
    admin_menu();
}
void passengermanagment() {

    int ticketid, id;
    string eachline;
    info detail;
    ifstream show;
    show.open("tickets.txt");

    if (!show) {
        cout << "Error opening the file." << endl;
        return;
    }

    cout << "Enter the ticket id of passenger: " << endl;
    cin >> ticketid;
    cin.ignore();

    bool found = false;
    while (getline(show, eachline)) {
        stringstream stream(eachline);
        stream >> detail.ticketid;
        stream.ignore();
        stream >> detail.trainid;
        stream.ignore();
        getline(stream, detail.name, ',');
        stream >> detail.age;
        stream.ignore();
        stream >> detail.gender;
        stream.ignore();
        stream >> detail.phnum;


        if (ticketid == detail.ticketid) {
            cout << "Ticket ID: " << detail.ticketid << endl;
            cout << "Train ID: " << detail.trainid << endl;
            cout << "Name: " << detail.name << endl;
            cout << "Age: " << detail.age << endl;
            cout << "Gender: " << detail.gender << endl;
            cout << "Phone Number: " << detail.phnum << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Ticket ID not found." << endl;
    }

    show.close();
    admin_menu();
}

void reports() {
    report data;

    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, data.name);
    cout << "Enter your CNIC: ";
    cin >> data.cnic;
    cin.ignore();
    cout << "Enter your report below: " << endl;
    getline(cin, data.report);
    ofstream outfile;
    outfile.open("report.txt", ios::app);
    if (outfile.is_open()) {
        outfile << data.name << "," << data.cnic << " " << data.report << endl;
        cout << "Report saved successfully!" << endl;
    }
    else {
        cout << "Error opening the file." << endl;
    }
}
void vreport() {
    report data;
    string eachline;
    ifstream infile;
    infile.open("report.txt");
    while (getline(infile, eachline)) {
        stringstream stream(eachline);
        stream >> data.name;
        stream >> data.cnic;
        stream.ignore();
        getline(stream, data.report);
        cout << data.name << "," << data.cnic << ": " << data.report << endl;
    }
    admin_menu();
}

void viewtrainshedule() {
    ifstream inputfile;
    inputfile.open("trains.txt");
    if (!inputfile) {
        cout << "Error opening the file." << endl;
        return;
    }

    string eachline;
    bool found = false;
    cout << "Train Schedule: " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Train ID | Train Name | Route | Departure Time | Arrival Time" << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        int trainID, capacity;
        string name, route_name, dep_time, arrival_time;

        string temp;
        getline(stream, temp, ',');
        trainID = stoi(temp);
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');

        // Display the train details
        cout << trainID << " | " << name << " | " << route_name << " | " << dep_time << " | " << arrival_time << endl;
        found = true;
    }

    inputfile.close();

    if (!found) {
        cout << "No trains found in the schedule." << endl;
    }

    admin_menu();
}
void viewtrainshedule2() {
    ifstream inputfile;
    inputfile.open("trains.txt");
    if (!inputfile) {
        cout << "Error opening the file." << endl;
        return;
    }
    string eachline;
    bool found = false;
    cout << "Train Schedule: " << endl;
    cout << "-----------------------------------" << endl;
    cout << "Train ID | Train Name | Route | Departure Time | Arrival Time" << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (getline(inputfile, eachline)) {
        stringstream stream(eachline);
        int trainID, capacity;
        string name, route_name, dep_time, arrival_time;

        string temp;
        getline(stream, temp, ',');
        trainID = stoi(temp);
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');

        // Display the train details
        cout << trainID << " | " << name << " | " << route_name << " | " << dep_time << " | " << arrival_time << endl;
        found = true;
    }

    inputfile.close();

    if (!found) {
        cout << "No trains found in the schedule." << endl;
    }

    passenger_menu();
}

void cancelTicket() {
    int ticketId;
    cout << "Enter the ticket ID you want to cancel: ";
    cin >> ticketId;
    ifstream ticketFile("tickets.txt");
    if (!ticketFile) {
        cout << "Error opening tickets file." << endl;
        return;
    }

    string eachLine;
    bool ticketFound = false;
    vector<string> ticketLines;
    int trainid;
    int ticketID;
    string temp;

    while (getline(ticketFile, eachLine)) {
        stringstream stream(eachLine);
        stream >> ticketID;

        if (ticketID == ticketId) {
            getline(stream, temp, ',');
            trainid = stoi(temp); // Get the train ID from the ticket
            ticketFound = true;
            break;
        }
        else {
            ticketLines.push_back(eachLine);
        }
    }
    ticketFile.close();

    if (!ticketFound) {
        cout << "Ticket ID not found!" << endl;
        return;
    }

    ofstream newTicketFile("tickets.txt");
    if (!newTicketFile) {
        cout << "Error opening tickets file for writing." << endl;
        return;
    }

    // Write all remaining tickets to the file
    for (const string& line : ticketLines) {
        newTicketFile << line << endl;
    }
    newTicketFile.close();

    cout << "Ticket successfully canceled!" << endl;

    // Now update the train capacity
    int train_id;
    string name;
    int train_capacity;
    string eachline;
    string route_name;
    string dep_time, arrival_time;
    bool found = false;
    ofstream tempfile("temp.txt");
    ifstream trainfile("trains.txt");

    while (getline(trainfile, eachline)) {
        stringstream stream(eachline);
        getline(stream, temp, ',');
        train_id = stoi(temp); //
        getline(stream, name, ',');
        getline(stream, route_name, ',');
        getline(stream, temp, ',');
        train_capacity = stoi(temp);
        getline(stream, dep_time, ',');
        getline(stream, arrival_time, ',');

        if (train_id == trainid) {
            cout << "Train ID: " << train_id << " Route: " << route_name
                << " Capacity: " << train_capacity
                << " Departure time: " << dep_time
                << " Arrival time: " << arrival_time << endl;
            found = true;
            train_capacity++;

            tempfile << train_id << "," << name << "," << route_name << ","
                << train_capacity << "," << dep_time << "," << arrival_time << endl;
            continue;
        }
        tempfile << eachline << endl;
    }
    trainfile.close();
    tempfile.close();

    if (found) {
        remove("trains.txt");
        rename("temp.txt", "trains.txt");
    }
    Trainmenu();
}

int main()
{
    srand(time(0));
    Trainmenu();
}