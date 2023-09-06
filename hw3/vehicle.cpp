

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
    bool canHover() const { return false; } 

};

Satellite::~Satellite()
{
    cout << "Destroying the satellite " << Vehicle::id() << endl;
}

string Satellite::description() const
{
    return "a satellite";
}




