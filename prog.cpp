#include <iostream>
using namespace std;

class BaseVehicle
{
protected:
    int id;
    string brand;
    string vehicleName;
    int manufactureYear;

public:
    static int vehicleCount;

    BaseVehicle()
    {
        id = 0;
        brand = "";
        vehicleName = "";
        manufactureYear = 0;
        vehicleCount++;
    }

    BaseVehicle(int v_id, string v_brand, string v_name, int v_year)
    {
        id = v_id;
        brand = v_brand;
        vehicleName = v_name;
        manufactureYear = v_year;
        vehicleCount++;
    }

    virtual ~BaseVehicle()
    {
        vehicleCount--;
    }

    void setID(int v)
    {
        id = v;
    }

    int getID()
    {
        return id;
    }

    virtual void showInfo()
    {
        cout << "ID: " << id << endl;
        cout << "Brand: " << brand << endl;
        cout << "Name: " << vehicleName << endl;
        cout << "Year: " << manufactureYear << endl;
    }
};

int BaseVehicle::vehicleCount = 0;

class NormalCar : public BaseVehicle
{
protected:
    string fuel;

public:
    NormalCar()
    {
        fuel = "";
    }

    NormalCar(int id, string brand, string name, int year, string f)
        : BaseVehicle(id, brand, name, year)
    {
        fuel = f;
    }

    void showInfo()
    {
        BaseVehicle::showInfo();
        cout << "Fuel Type: " << fuel << endl;
    }
};

class BatteryCar : public NormalCar
{
protected:
    int batterySize;

public:
    BatteryCar() : NormalCar()
    {
        batterySize = 0;
    }

    BatteryCar(int id, string brand, string name, int year, string fuel, int battery)
        : NormalCar(id, brand, name, year, fuel)
    {
        batterySize = battery;
    }

    void showInfo()
    {
        NormalCar::showInfo();
        cout << "Battery Size: " << batterySize << " kWh" << endl;
    }
};

class AirVehicle
{
protected:
    int airRange;

public:
    AirVehicle()
    {
        airRange = 0;
    }
    AirVehicle(int r)
    {
        airRange = r;
    }
};

class AirCar : public NormalCar, public AirVehicle
{
public:
    AirCar() : NormalCar(), AirVehicle() {}

    AirCar(int id, string brand, string name, int year, string fuel, int range)
        : NormalCar(id, brand, name, year, fuel), AirVehicle(range) {}

    void showInfo()
    {
        NormalCar::showInfo();
        cout << "Air Range: " << airRange << endl;
    }
};

class RaceCar : public BatteryCar
{
    int maxSpeed;

public:
    RaceCar() : BatteryCar()
    {
        maxSpeed = 0;
    }

    RaceCar(int id, string brand, string name, int year, string fuel, int battery, int speed)
        : BatteryCar(id, brand, name, year, fuel, battery)
    {
        maxSpeed = speed;
    }

    void showInfo()
    {
        BatteryCar::showInfo();
        cout << "Max Speed: " << maxSpeed << endl;
    }
};

class FamilySedan : public NormalCar
{
public:
    FamilySedan() {}
    FamilySedan(int id, string brand, string name, int year, string fuel)
        : NormalCar(id, brand, name, year, fuel) {}
};

class BigSUV : public NormalCar
{
public:
    BigSUV() {}
    BigSUV(int id, string brand, string name, int year, string fuel)
        : NormalCar(id, brand, name, year, fuel) {}
};

class VehicleStore
{
private:
    BaseVehicle list[100];
    int total;

public:
    VehicleStore()
    {
        total = 0;
    }

    void add(BaseVehicle v)
    {
        if (total < 100)
        {
            list[total] = v;
            total++;
            cout << "\nVehicle Added Successfully!\n";
        }
    }

    void showAll()
    {
        if (total == 0)
        {
            cout << "\nNo vehicles available.\n";
            return;
        }

        for (int i = 0; i < total; i++)
        {
            list[i].showInfo();
            cout << endl;
        }
    }

    void findByID(int id)
    {
        for (int i = 0; i < total; i++)
        {
            if (list[i].getID() == id)
            {
                list[i].showInfo();
                return;
            }
        }
        cout << "\nVehicle Not Found!\n";
    }
};

int main()
{
    VehicleStore store;
    int choice;

    do
    {
        cout << "\n----------- VEHICLE STORE MENU -----------\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int type;
            cout << "Select Type:\n"
                 << "1. Car\n2. Electric Car\n3. Flying Car\n4. Sports Car\n5. Sedan\n6. SUV\n";
            cin >> type;

            int id, year, battery, range, speed;
            string brand, name, fuel;

            cout << "Enter ID: ";
            cin >> id;
            cout << "Brand: ";
            cin >> brand;
            cout << "Name: ";
            cin >> name;
            cout << "Year: ";
            cin >> year;

            switch (type)
            {
            case 1:
                cout << "Fuel: ";
                cin >> fuel;
                store.add(NormalCar(id, brand, name, year, fuel));
                break;

            case 2:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> battery;
                store.add(BatteryCar(id, brand, name, year, fuel, battery));
                break;

            case 3:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Range: ";
                cin >> range;
                store.add(AirCar(id, brand, name, year, fuel, range));
                break;

            case 4:
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> battery;
                cout << "Max Speed: ";
                cin >> speed;
                store.add(RaceCar(id, brand, name, year, fuel, battery, speed));
                break;

            case 5:
                cout << "Fuel: ";
                cin >> fuel;
                store.add(FamilySedan(id, brand, name, year, fuel));
                break;

            case 6:
                cout << "Fuel: ";
                cin >> fuel;
                store.add(BigSUV(id, brand, name, year, fuel));
                break;

            default:
                cout << "Invalid Type!\n";
            }
            break;
        }

        case 2:
            store.showAll();
            break;

        case 3:
        {
            int id;
            cout << "\nEnter ID: ";
            cin >> id;
            store.findByID(id);
            break;
        }

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}
