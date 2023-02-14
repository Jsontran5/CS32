#include <iostream>
#include <string>
using namespace std;

//Your declarationsand implementations would go here
//VEHICLE IMPLEMENTATION
class Vehicle
{
public:
    Vehicle(string input) { m_name = input; }
         virtual ~Vehicle() {};

         virtual string id() const;
         virtual string description() const = 0;
         virtual bool canHover() const { return true; }
private:
    string m_name;
       
};

string Vehicle::id() const
{
    return m_name;
}

//DRONE IMPLEMENTATION
class Drone : public Vehicle
{
public:
    Drone(string d) :Vehicle(d) {}

    virtual ~Drone();

    virtual string description() const;
     
};

Drone::~Drone()
{
    cout << "Destroying " << Vehicle::id() << ", a drone" << endl;
}

string Drone::description() const
{
    return "a drone";
}




//BALLOON IMPLMENTATION
class Balloon : public Vehicle
{
public:
    Balloon(string input, double d) :Vehicle(input) { m_d = d; }

    virtual ~Balloon();

    virtual string description() const;
    

private:
    double m_d;
};

Balloon::~Balloon()
{
    cout << "Destroying the balloon " << Vehicle::id() << endl;
}

string Balloon::description() const
{
    if (m_d < 8)
    {
        return "a small balloon";
    }
    else
    {
        return "a large balloon";
    }
}


//Satellite IMPLEMENTATION
class Satellite : public Vehicle
{
public:
    Satellite(string input) :Vehicle(input) {}

    virtual ~Satellite();

    virtual string description() const;
    bool canHover() const { return false; } //wrong due to spec

};

Satellite::~Satellite()
{
    cout << "Destroying the satellite " << Vehicle::id() << endl;
}

string Satellite::description() const
{
    return "a satellite";
}



void display(const Vehicle* v)
{
    cout << v->id() << " is " << v->description();
    if (v->canHover())
        cout << ", so it can hover";
    cout << endl;
}

int main()
{
    Vehicle* fleet[4];
    fleet[0] = new Drone("CB4UP");
    // Balloons have an id and a diameter in meters  Balloons with a
    // diameter under 8 meters are small balloons; those with a diameter
    // 8 meters or more are large balloons
    fleet[1] = new Balloon("99LB", 6.3);
    fleet[2] = new Balloon("CN20230201", 30.2);
    fleet[3] = new Satellite("EB8675309");

    for (int k = 0; k < 4; k++)
        display(fleet[k]);

    // Clean up the vehicles before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete fleet[k];
}