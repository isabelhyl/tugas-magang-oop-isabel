// // Trip Management System
// // features: create v, read v, update v, and delete v
// // additional features: search trip v, display all trips v

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> 
#include <cmath>   
#include <limits>  

using namespace std;

class Trip {
private:
    int tripID;
    string destination;
    string date;
    double price;

public:
    // constructor
    Trip(int id, const string& dest, const string& dt, double pr) 
        : tripID(id), destination(dest), date(dt), price(pr) {}

    // getters
    int getTripID() const { return tripID; }
    string getDestination() const { return destination; }
    string getDate() const { return date; }
    double getPrice() const { return price; }

    void updateTrip(const string& newDestination, const string& newDate, double newPrice) {
        destination = newDestination;
        date = newDate;
        price = newPrice;
    }

    void displayTrip() const {
        cout << "Trip ID: " << tripID << ", Destination: " << destination 
             << ", Date: " << date << ", Price: RP" << fixed << setprecision(2) << price << endl;
    }
};


class TravelManagementSystem {
private:
    vector<Trip> trips;
    int nextTripID = 1;

    // trim whitespace from strings
    string trim(const string& str) const {
        size_t first = str.find_first_not_of(' ');
        if (first == string::npos) return ""; 
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

public:
    void createTrip(const string& destination, const string& date, double price) {
        Trip newTrip(nextTripID++, destination, date, price);
        trips.push_back(newTrip);
        cout << "\nTrip created successfully!\n";
    }

    void displayAllTrips() const {
        if (trips.empty()) {
            cout << "\nNo trips available.\n";
        } else {
            for (const auto& trip : trips) {
                trip.displayTrip();
            }
        }
    }

    void searchTrip() const {
        while (true) {
            cout << "\n--- Search Options ---\n";
            cout << "1. Search by Trip ID\n";
            cout << "2. Search by Destination\n";
            cout << "3. Search by Price\n";
            cout << "4. Search by Date\n";
            cout << "Sample input: 2 3\n";

            cout << "Enter your choice(s): ";
            string input;
            getline(cin, input);
            istringstream ss(input);
            vector<int> choices;
            int choice;

            while (ss >> choice) {
                if (choice >= 1 && choice <= 4) {
                    choices.push_back(choice);
                } else {
                    cout << "\nInvalid choice: " << choice << ". Please choose between 1 and 4.\n";
                    break; 
                }
            }

            if (choices.empty()) continue; 

            // filters
            int id = -1;
            string destination, date;
            double price = -1.0;
            bool priceSet = false;

            for (int c : choices) {
                switch (c) {
                    case 1:
                        cout << "Enter Trip ID: ";
                        cin >> id;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        break;
                    case 2:
                        cout << "Enter Destination: ";
                        getline(cin, destination);
                        break;
                    case 3:
                        cout << "Enter Price: ";
                        cin >> price;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        priceSet = true;
                        break;
                    case 4:
                        cout << "Enter Date (YYYY-MM-DD): ";
                        getline(cin, date);
                        break;
                }
            }

            bool found = false;
            for (const auto& trip : trips) {
                bool match = true;
                if (id != -1 && trip.getTripID() != id) match = false;
                if (!destination.empty() && trim(trip.getDestination()) != trim(destination)) match = false;
                if (priceSet && fabs(trip.getPrice() - price) > 0.01) match = false; 
                if (!date.empty() && trim(trip.getDate()) != trim(date)) match = false;

                if (match) {
                    trip.displayTrip();
                    found = true;
                }
            }
            if (!found) cout << "\nNo matching trips found.\n";
            break; 
        }
    }

    void updateTrip() {
    cout << "\n--- Update Options ---\n";
    cout << "1. Update by Trip ID\n";
    cout << "2. Update by Destination\n";
    cout << "3. Update by Price\n";
    cout << "4. Update by Date\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    int id = -1;
    string destination, date;
    double price = -1.0;


    switch (choice) {
        case 1:
            cout << "Enter Trip ID to update: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 2:
            cout << "Enter Destination to update: ";
            getline(cin, destination);
            break;
        case 3:
            cout << "Enter Price to update: ";
            cin >> price;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 4:
            cout << "Enter Date (YYYY-MM-DD) to update: ";
            getline(cin, date);
            break;
        default:
            cout << "\nInvalid choice. Please choose between 1 and 4.\n";
            return;
    }

    string newDestination, newDate;
    double newPrice;
    cout << "Enter new Destination (leave empty to keep current): ";
    getline(cin, newDestination);
    cout << "Enter new Date (YYYY-MM-DD, leave empty to keep current): ";
    getline(cin, newDate);
    cout << "Enter new Price (-1 to keep current): ";
    cin >> newPrice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (auto& trip : trips) {
        bool match = true;
        if (id != -1 && trip.getTripID() != id) match = false;
        if (!destination.empty() && trim(trip.getDestination()) != trim(destination)) match = false;
        if (price != -1.0 && fabs(trip.getPrice() - price) > 0.01) match = false;
        if (!date.empty() && trim(trip.getDate()) != trim(date)) match = false;

        if (match) {
            found = true;
            trip.updateTrip(
                newDestination.empty() ? trip.getDestination() : newDestination,
                newDate.empty() ? trip.getDate() : newDate,
                newPrice == -1.0 ? trip.getPrice() : newPrice
            );
        }
    }

    if (found) {
        cout << "\nAll matching trips updated successfully!\n";
    } else {
        cout << "\nNo matching trips found for update.\n";
    }
}



    void deleteTrip() {
        cout << "\n--- Delete Options ---\n";
        cout << "1. Delete by Trip ID\n";
        cout << "2. Delete by Destination\n";
        cout << "3. Delete by Price\n";
        cout << "4. Delete by Date\n";

        while (true) {
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int id = -1;
            string destination, date;
            double price = -1.0;
            bool priceSet = false;

            switch (choice) {
                case 1:
                    cout << "Enter Trip ID to delete: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    break;
                case 2:
                    cout << "Enter Destination to delete: ";
                    getline(cin, destination);
                    break;
                case 3:
                    cout << "Enter Price to delete: ";
                    cin >> price;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    priceSet = true;
                    break;
                case 4:
                    cout << "Enter Date (YYYY-MM-DD) to delete: ";
                    getline(cin, date);
                    break;
                default:
                    cout << "\nInvalid choice: " << choice << ". Please choose between 1 and 4.\n";
                    continue; 
            }

            // delete matching trips
            bool deleted = false;
            auto it = trips.begin();
            while (it != trips.end()) {
                bool match = true;
                if (id != -1 && it->getTripID() != id) match = false;
                if (!destination.empty() && trim(it->getDestination()) != trim(destination)) match = false;
                if (priceSet && fabs(it->getPrice() - price) > 0.01) match = false; 
                if (!date.empty() && trim(it->getDate()) != trim(date)) match = false;

                if (match) {
                    it = trips.erase(it); // delete trip and advance the iterator
                    cout << "\nTrip deleted successfully!\n";
                    deleted = true;
                } else {
                    ++it; // move to the next trip
                }
            }
            if (!deleted) cout << "\nNo matching trips found for deletion.\n";
            break; 
        }
    }
};

int main() {
    TravelManagementSystem tms;
    while (true) {
        cout << "\n--- Travel Management System ---\n";
        cout << "1. Create Trip\n";
        cout << "2. Display All Trips\n";
        cout << "3. Search Trip\n";
        cout << "4. Update Trip\n";
        cout << "5. Delete Trip\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1: {
                string destination, date;
                double price;

                cout << "Enter Destination: ";
                getline(cin, destination);
                cout << "Enter Date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter Price: ";
                cin >> price;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                tms.createTrip(destination, date, price);
                break;
            }
            case 2:
                tms.displayAllTrips();
                break;
            case 3:
                tms.searchTrip();
                break;
            case 4:
                tms.updateTrip();
                break;
            case 5:
                tms.deleteTrip();
                break;
            case 6:
                cout << "\nExiting the program. Thanks for visiting us!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please select a valid option.\n";
        }
    }
    return 0;
}


