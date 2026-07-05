#define USER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class user {
private:
    string username;
    string password;

public:
    user(string uname, string pass)
        : username(uname), password(pass) {}

    string getusername() const { return username; }

    bool checkpass(const string& pass) const {
        return password == pass;
    }

    void showmenu();
};

class systemManager {
private:
    vector<user> users;

public:
    void loadUsersFromFile() {
        ifstream file("users.txt");
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string uname, pass;
            getline(ss, uname, ',');
            getline(ss, pass, ',');
            users.emplace_back(uname, pass);
        }
    }

    void saveUserToFile(const string& uname, const string& pass) {
        ofstream file("users.txt", ios::app);
        file << uname << "," << pass << "\n";
    }

    void signUp();
    void login();
};

class Movie {
public:
    string title, genre, rating;
    int duration;
    float rent_cost, purchase_cost;

    Movie() {}
    Movie(string t, string g, string r, int d, float rent, float purchase)
        : title(t), genre(g), rating(r), duration(d),
          rent_cost(rent), purchase_cost(purchase) {}

    string serialize() const {
        return "M|" + title + "|" + genre + "|" + rating + "|" + 
               to_string(duration) + "|" + to_string(rent_cost) + "|" + to_string(purchase_cost);
    }

    void show() const {
        cout << "[Movie] " << title << " (" << genre << ", " << rating 
             << "), " << duration << " mins, Rent: " << rent_cost 
             << ", Buy: " << purchase_cost << endl;
    }
};

class TVShow {
public:
    string title, genre, rating;
    int seasons, episodes;
    float rent_cost, purchase_cost;

    TVShow() {}
    TVShow(string t, string g, string r, int s, int eps, float rent, float purchase)
        : title(t), genre(g), rating(r), seasons(s), episodes(eps),
          rent_cost(rent), purchase_cost(purchase) {}

    string serialize() const {
        return "T|" + title + "|" + genre + "|" + rating + "|" + 
               to_string(seasons) + "|" + to_string(episodes) + "|" + 
               to_string(rent_cost) + "|" + to_string(purchase_cost);
    }

    void show() const {
        cout << "[TV Show] " << title << " (" << genre << ", " << rating
             << "), " << seasons << " seasons, " << episodes << " eps/season, "
             << "Rent: " << rent_cost << ", Buy: " << purchase_cost << endl;
    }
};

void addContent() {
    int choice;
    cout << "1. Add Movie\n2. Add TV Show\nChoice: ";
    cin >> choice;

    ofstream out("content.txt", ios::app);

    if (choice == 1) {
        string t, g, r;
        int d;
        float rc, pc;
        cout << "Title Genre Rating Duration RentCost PurchaseCost:\n";
        cin >> t >> g >> r >> d >> rc >> pc;
        Movie m(t, g, r, d, rc, pc);
        out << m.serialize() << endl;
    } else {
        string t, g, r;
        int s, eps;
        float rc, pc;
        cout << "Title Genre Rating Seasons Episodes/Season RentCost PurchaseCost:\n";
        cin >> t >> g >> r >> s >> eps >> rc >> pc;
        TVShow tv(t, g, r, s, eps, rc, pc);
        out << tv.serialize() << endl;
    }

    cout << "Content added.\n";
}

void viewContent() {
    ifstream in("content.txt");
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string type;
        getline(ss, type, '|');

        if (type == "M") {
            string t, g, r;
            int d;
            float rc, pc;
            getline(ss, t, '|'); getline(ss, g, '|'); getline(ss, r, '|');
            ss >> d; ss.ignore();
            ss >> rc; ss.ignore();
            ss >> pc;
            Movie m(t, g, r, d, rc, pc);
            m.show();
        } else if (type == "T") {
            string t, g, r;
            int s, eps;
            float rc, pc;
            getline(ss, t, '|'); getline(ss, g, '|'); getline(ss, r, '|');
            ss >> s; ss.ignore(); ss >> eps; ss.ignore(); ss >> rc; ss.ignore(); ss >> pc;
            TVShow tv(t, g, r, s, eps, rc, pc);
            tv.show();
        }
    }
}

void user::showmenu() {
    int choice;
    do {
        cout << "\n1. Browse Content\n2. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) viewContent();
    } while (choice != 2);
}

void systemManager::signUp() {
    string uname, pass;
    cout << "Enter username: ";
    cin >> uname;
    for (user& u : users) {
        if (u.getusername() == uname) {
            cout << "Username already exists.\n";
            return;
        }
    }
    cout << "Enter password: ";
    cin >> pass;
    users.emplace_back(uname, pass);
    saveUserToFile(uname, pass);
    cout << "Signup successful.\n";
}

void systemManager::login() {
    string uname, pass;
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    if (uname == "admin" && pass == "admin") {
        int choice;
        do {
            cout << "ADMIN PANEL\n1. Add Content\n2. View Content\n3. Logout\nChoice: ";
            cin >> choice;
            if (choice == 1) addContent();
            else if (choice == 2) viewContent();
        } while (choice != 3);
        return;
    }

    for (user& u : users) {
        if (u.getusername() == uname && u.checkpass(pass)) {
            cout << "Login successful.\n";
            u.showmenu();
            return;
        }
    }

    cout << "Invalid credentials.\n";
}

int main() {
    systemManager sys;
    sys.loadUsersFromFile();  // Load users from file

    int choice;
    do {
        cout << "\n===== Welcome to StreamIt =====\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sys.signUp();
                break;
            case 2:
                sys.login();
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
