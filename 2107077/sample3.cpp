#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define cls system("cls");
#define pause system("pause");

class security
{
  string username, pass;

  bool securitysign()
  {
    cout << "set username and password" << endl;
    int n;
    cout << "Enter your user name: ";
    cin >> username;

    cout << "enter the password :";
    cin >> pass;
    ofstream secure("security.txt");
    secure << 1 << endl
           << username << endl
           << pass;
    cout << "password set\n";
    secure.close();
    return 1;
  }
  bool signin()
  {
    ifstream secure("security.txt");
    int s;
    string name, password;
    secure >> s >> name >> password;
    secure.close();
    if (s != 1)
    {

      return securitysign();
    }

    cout << "User Name: " << endl;
    cin >> username;
    cout << "password: " << endl;
    cin >> pass;
    if (username == name && pass == pass)
    {
      cout << "logged in" << endl;
      return 1;
    }
  }
  friend bool SignIn(security sss);

public:
  security()
  {
    username = pass = "";
  }
};
bool SignIn(security sss)

{
  return sss.signin();
}

class customer
{
private:
  string name, address, mobile;
  int iday, imon, iyer, oday, omon, oyer, room_no;

public:
  customer() {}
  customer(string nam, string ad, string mo, int ida, int imo, int iye, int oda, int omo, int oye)
  {
    name = nam, address = ad, mobile = mo, iday = ida, imon = imo, iyer = iye, oday = oda, omon = omo, oyer = oye;
  }
  void getdata()
  {
    ofstream custom;
    custom.open("customers.txt", ios::app);
    cout << "give name" << endl;
    cin >> name;
    cout << "address :" << endl;
    cin >> address;
    cout << "give mobile number:" << endl;
    cin >> mobile;
    cout << "check in day :" << endl;
    cin >> iday;
    cout << "check in month(1-12):" << endl;
    cin >> imon;
    cout << "check in year:" << endl;
    cin >> iyer;
    cout << "check out day :" << endl;
    cin >> oday;
    cout << "check out month(1-12):" << endl;
    cin >> omon;
    cout << "check out year:" << endl;
    cin >> oyer;
    // cout << "room no:" << endl;
    // cin >> room_no;
    // custom << room_no << endl;
    custom << name << endl;
    custom << address << endl;
    custom << mobile << endl;
    custom << iday << " " << imon << " " << iyer << endl;
    custom << oday << " " << omon << " " << oyer << endl;
    custom.close();
  }
  friend class manage;
  void showcustomer()
  {
    cout << "customer name: " << name << endl;
    cout << "customer address:" << address << endl;
    cout << "customer number:" << mobile << endl;
    cout << "check in day: " << iday << "/" << imon << "/" << iyer << endl;
    cout << "check out day: " << oday << "/" << omon << "/" << oyer << endl;
  }
};

class room
{
  int number;
  int roomdetails;
  int room_stat;
  int rent;

public:
  room() {}
  room(int a, int b, int c, int d)
  {
    int number = a;
    int roomdetails = b;
    int room_status = c;
    int rent = d;
  }
  friend class manager;
  ~room()
  {
    // cout<<"yobo";
  }

  int getNumber() { return number; }
  int getRoomDetails() { return roomdetails; }
  int getRoomStat() { return room_stat; }
  int getRent() { return rent; }
};

class manage
{
  vector<room> hotelroom;

public:
  void showroom()
  {
    ifstream allroom;
    allroom.open("roomdetails.txt");
    int num, det, stat, rent;
    while (allroom >> num >> det >> stat >> rent)
    {
      cout << "Room no:" << num << endl;
      if (det == 0)
        cout << "Room Type:"
             << "single" << endl;
      else if (det == 1)
        cout << "Room Type:"
             << "double" << endl;
      else if (det == 2)
        cout << "Room Type:"
             << "family" << endl;
      else
        cout << "room doesnt exit" << endl;
      if (stat == 0)
        cout << "Status: "
             << "available" << endl;
      else if (stat == 1)
        cout << "Status: "
             << "occupied" << endl;
      cout << "rent per day:" << rent << endl;
    }
    allroom.close();
  };

  void addroom()
  {
    ofstream newroom;
    newroom.open("roomdetails.txt", ios::app);
    int num, det, stat, rent;
    cout << "Enter room number: ";
    cin >> num;
    cout << "Enter room type (0 for single, 1 for double, 2 for family): ";
    cin >> det;
    cout << "Enter room status (0 for available, 1 for occupied): ";
    cin >> stat;
    cout << "Enter rent per day: ";
    cin >> rent;

    // Check if the room number already exists
    for (auto &r : hotelroom)
    {
      if (r.getNumber() == num)
      {
        cout << "Room number already exists. Please choose a different number." << endl;
        return;
      }
    }

    newroom << num << "\n"
            << det << "\n"
            << stat << "\n"
            << rent << endl;
    newroom.close();

    // 1
    //  room* r_old =new room(num, det, stat, rent);
    //  room & r = *r_old;
    room r(num, det, stat, rent);
    hotelroom.push_back(r);
    // hotelroom.erase(hotelroom.begin());
    cout << "Room added successfully!" << endl;
  };

  void removeroom()
  {
    int num;
    cout << "Enter the room number to remove: ";
    cin >> num;

    for (auto it = hotelroom.begin(); it != hotelroom.end(); ++it)
    {
      if (it->getNumber() == num)
      {
        hotelroom.erase(it);
        cout << "Room number " << num << " removed successfully!" << endl;
        break;
      }
    }

    ofstream newroom("roomdetails.txt", ios::trunc);
    for (auto &r : hotelroom)
    {
      newroom << r.getNumber() << " " << r.getRoomDetails() << " " << r.getRoomStat() << " " << r.getRent() << endl;
    }
    newroom.close();
  }
  void AvailableRoom()
  {
    ifstream room;
    room.open("rooms.txt");
    string name, address, mob;
    int iday, imn, iyr, oday, omn, oyr, advance, id;
    int rnt, no, t, st;
    while (room >> no >> t >> st >> rnt)
    {
      if (st)
        continue;
      cout << "\nRoom No: " << no << endl;
      cout << "Type: " << (t == 1 ? "Single" : (t == 2 ? "Double" : "Family")) << " room" << endl;
      cout << "Status: " << (st == 0 ? "Available" : "Occupied") << endl;
      cout << "Rent: " << rnt << endl;
    }
    room.close();
  }
  void checkin()
  {

    ifstream room;
    room.open("roomdetails.txt");
    int rnt, no, t, st, rm_no;
    while (room >> no >> t >> st >> rnt)
      if (!st)
        cout << "\nRoom No: " << no << endl;
    room.close();
    vector<int> info;
    int c;
  again:
    cout << "\n\n(1) Show Details\n(..) Continue....\nChoice: ";
    cin >> c;
    if (c == 1)
      AvailableRoom();
    room.open("roomdetails.txt");
    info.clear();
    cout << "Enter the Room No: ";
    cin >> rm_no;

    bool flag = true;
    while (room >> no >> t >> st >> rnt)
    {
      if (no == rm_no)
      {
        flag = false;
        if (st)
        {
          cout << "The room does not found or the room is already occupied.\nTry again........\n";
          room.close();
          goto again;
        }
        else
          st = 1;
      }
      info.push_back(no);
      info.push_back(t);
      info.push_back(st);
      info.push_back(rnt);
    }
    room.close();
    if (flag)
    {
      cout << "The room does not found or the room is already occupied.\nTry again........\n";
      goto again;
    }
    ofstream rm;
    rm.open("roomdetails.txt");
    for (int i = 0; i < info.size(); i++)
      rm << info[i] << endl;
    rm.close();
    ofstream cm;
    cm.open("customers.txt", ios::app);
    cm << rm_no << endl;
    cm.close();
    customer cmm;
    cmm.getdata();
  }

  void checkout()
  {
    vector<int> info;
    ifstream room;
    room.open("roomdetails.txt");
    int roomno;
    cout << "Enter the Room No: ";
    cin >> roomno;
    string name, add, phone, iday, imon, iyear, oday, omon, oyear;
    // vector<int>rminfo;
    vector<string> cminfo;
    int rnt, no, t, st;
    while (room >> no >> t >> st >> rnt)
    {
      if (roomno == no)
      {
        st = 0;
        cout << "room checked out" << endl;
        cout << "customer info" << endl;
        ifstream cm(" customer.txt");
        int rm_no;
        while (cm >> rm_no >> name >> add >> phone >> iday >> imon >> iyear >> oday >> omon >> oyear)
        {
          if (roomno == rm_no)
          {
            customer cc(name, add, phone, stoi(iday), stoi(imon), stoi(iyear), stoi(oday), stoi(omon), stoi(oyear));
            cc.showcustomer();
          }
          else
            cminfo.insert(cminfo.end(), {to_string(rm_no), name, add, phone, iday, imon, iyear, oday, omon, oyear});
        }
        cm.close();
      }
      info.push_back(no);
      info.push_back(t);
      info.push_back(st);
      info.push_back(rnt);
    }
    room.close();
    // ofstream cm
    ofstream rm;
    rm.open("roomdetails.txt");
    for (int i = 0; i < info.size(); i++)
      rm << info[i] << endl;
    ofstream cm;
    cm.open("customers.txt");
    for (int i = 0; i < cminfo.size(); i++)
    {
      cm << cminfo[i] << endl;
    }
    // cm << rm_no << endl;
    cm.close();
  }
  void updateroom()
  {
  }
  void showCustomerDetails()
  {
    ifstream customer;
    string name, address, mob;
    int iday, imn, iyr, oday, omn, oyr, rm_no, rnt, no, t, st;
    cout << "\nCustomer Info: " << endl;
    customer.open("customers.txt");
    while (customer >> rm_no >> name >> address >> mob >> iday >> imn >> iyr >> oday >> omn >> oyr)
    {

      cout << "Name: " << name << endl;
      cout << "Address: " << address << endl;
      cout << "Mobile No: " << mob << endl;
      cout << "Check-In Date: " << iday << '/' << imn << '/' << iyr << endl;
      cout << "Check-Out Date: " << oday << '/' << omn << '/' << oyr << endl;
      // cout << "Advance Payement: " << advance << endl;
      // cout << "Booking ID: " << id << endl;
    }
    customer.close();
  }
};

int main()
{
  cout << "\033[43m";
  system("cls");
  security ss;

  if (!SignIn(ss))
  {
    return 0;
  }
  system("cls");
  manage mg;
  int choice;

  while (true)
  {
    cls
            cout
        << "\nMenu:\n";
    cout << "1. Show Room Details\n";
    cout << "2. Add Room\n";
    cout << "3. Check-In\n";
    cout << "4. Check-Out\n";
    cout << "5. Show Customer Details\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cls switch (choice)
    {
    case 1:
      mg.showroom();
      pause break;
    case 2:
      mg.addroom();
      pause break;
    case 3:
      mg.checkin();
      pause break;
    case 4:
      mg.checkout();
      pause break;
    case 5:
      mg.showCustomerDetails();
      pause break;
    case 6:
      cout << "Exiting the program.\n";
      pause return 0;
    default:

      cout << "Invalid choice. Please try again.\n";
      pause
    }
  }

  return 0;
}
