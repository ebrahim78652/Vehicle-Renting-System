/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<iomanip>




//Vehicle

class Vehicle {

private:
    const int no;
    std::string model;
    float price24h;
    static int noOfVehiclesAdded;

    //the below variable being used for setting the ID numbers of the vehicles. above one being used for printing purposes.
    static int noOfVehiclesAdded2;

public:
    Vehicle(const int no, std::string model, float price24h); //change this line


    virtual ~Vehicle();

    const int getNo() const;

    const std::string &getModel() const;

    const double get_price(int numberOfRentalDays);

    virtual void print()=0;

    static int get_noOfVehiclesAdded();

    static void set_noOfVehiclesAdded(int);

    static int get_noOfVehiclesAdded2();

    static void set_noOfVehiclesAdded2(int);





};
//implementation for vehicle


Vehicle::Vehicle(int no, std::string model, float price24h):
        no(no),
        model(model),
        price24h(price24h)
{
}

Vehicle::~Vehicle(){
    std::cout<<"Destructor called";
}

const int Vehicle::getNo() const {
    return no;
}

const std::string& Vehicle::getModel() const {
    return model;
}

const double Vehicle::get_price(int numberOfRentalDays){
    return price24h*numberOfRentalDays;
}

int Vehicle::get_noOfVehiclesAdded() {
    return noOfVehiclesAdded;
}

void Vehicle::set_noOfVehiclesAdded(int noOfVehicles ){
    noOfVehiclesAdded=noOfVehicles;
}


int Vehicle::get_noOfVehiclesAdded2() {
    return noOfVehiclesAdded2;
}

void Vehicle::set_noOfVehiclesAdded2(int noOfVehicles ){
    noOfVehiclesAdded2=noOfVehicles;
};

//bike
class Bike :public Vehicle {
public:

    Bike(int no ,std::string model);
    virtual void print();
};

//implementing bike
Bike::Bike(int no ,std::string model):Vehicle(no, model, 9.99)
{}


void Bike::print(){
    set_noOfVehiclesAdded(get_noOfVehiclesAdded()+1);
    std::cout<<get_noOfVehiclesAdded()<<": "<<getModel()<<getNo()<<" "<<"(Bike)\n";
}

//EmotorVehicle

class EMotorVehicle:public Vehicle{
public:
    EMotorVehicle(int no, std::string, float price24h);
    virtual bool is_streetLegal()=0;
    virtual void print();

};

//EmotorVehicle implementation

EMotorVehicle::EMotorVehicle(int no, std::string model, float price24h):Vehicle(no, model, price24h){}

//the print method.
void EMotorVehicle::print(){
    set_noOfVehiclesAdded(get_noOfVehiclesAdded()+1);
    std::cout<<get_noOfVehiclesAdded()<<": "<<getModel()<<getNo(); //instead of getNo() it should be 'noEBikesAdded
    if(!is_streetLegal()){
        std::cout<<" (not street legal) ";
    }
    else{
        std::cout<<" ";
    }
}

//Ebike
class EBike:public EMotorVehicle {
public:
    EBike(int no, std::string model);
    virtual bool is_streetLegal();
    virtual void print();
};

//Ebike implementation

EBike::EBike(int no, std::string model):EMotorVehicle(no, model, 29.99){};
bool EBike::is_streetLegal(){
    return true;
}
void EBike::print(){
    EMotorVehicle::print();
    std::cout<<" (EBike)\n";
}


//Escooter

class EScooter: public EMotorVehicle {

private:
    bool streetLegal;
public:
    EScooter(int no, std::string model, float price24h=19.99,  bool streetLegal= false);
    virtual bool is_streetLegal();
    virtual void print();
};

//Escooter implementation
EScooter::EScooter(int no, std::string model,float price24h,  bool streetLegal):
        EMotorVehicle(no, model, price24h)
{}


bool EScooter::is_streetLegal(){
    return streetLegal;
}

void EScooter::print(){
    EMotorVehicle::print();
    std::cout<<" (EScooter)\n";
}

//Dayofyear
class DayOfYear {


private:
    short int dayOfYear;
    short int year;
    //initialise and define the  below array outside the class.
    static const int days[13];

public:
    DayOfYear(short int dayOfYear=1 , short int year=365);

    DayOfYear(short int day, short int month, short int year);

    short int get_DayOfYear() const;

    friend DayOfYear operator++(DayOfYear day);

    friend std::istream& operator>>(std::istream& in, DayOfYear& dayOfYear);

    friend std::ostream& operator<<(std::ostream& out, DayOfYear &dayOfyear);
};

//DayOfyear implementation
DayOfYear::DayOfYear( short int dayOfYear, short int year):

        dayOfYear(dayOfYear),
        year(year)
{}

DayOfYear::DayOfYear(short int day, short int month, short int year):
        DayOfYear( days[month-1]+day, year)
{}

short int DayOfYear::get_DayOfYear() const {
    return dayOfYear;
}


DayOfYear operator++(DayOfYear day){
    if(day.dayOfYear<365) {
        day.dayOfYear++;
        return day;
    }//above code accounts for : all days except the last day of the year;
    else{
        day.dayOfYear=1;
        day.year++;
        return day;
    } //here it accounts for the last day of the year
}


std::istream& operator>>(std::istream& in, DayOfYear& dayOfYear){
    std::string date;
    std::cin>>date;
    std::string year, month, day;
    year= date.substr(0,4);
    month= date.substr(5,2);
    day= date.substr(8, 2);
    int intYear= std::stoi(year);
    int intMonth= std::stoi(month);
    int intDay= std::stoi(day);
    dayOfYear.year=intYear;
    dayOfYear.dayOfYear= DayOfYear::days[intMonth-1]+ intDay;
    return in;
}

std::ostream& operator<<(std::ostream& out, DayOfYear& dayOfyear){
    out<<dayOfyear.year<<"-";
    int i=0;
    int count=0;
    while(DayOfYear::days[i]<dayOfyear.dayOfYear){
        count =count+1;
        i=i+1;
    };

    int IntMonth= count;
    int IntDay= dayOfyear.dayOfYear- DayOfYear::days[IntMonth-1];

    out<<std::setw(2)<<std::setfill('0')<<IntMonth<<"-";
    out<<std::setw(2)<<std::setfill('0')<<IntDay;
    return out;
}

//rental
class Rental {
private:
    const int no;
    DayOfYear from;
    int days;
    std::string customer;
    static int last_no;

public:
    Rental(std::string customer, DayOfYear from , int days =1);

    int getDays() ;

    DayOfYear &getFrom() ;

    DayOfYear getUntil() ;

    void print();
};


//rental implementation
Rental::Rental(std::string customer, DayOfYear from , int days):
        customer(customer),
        from(from),
        days(days),
//cant be lower than 1.
        no(last_no+1)
{
    last_no=last_no+1;
}

int Rental::getDays()  {
    return days;
}

DayOfYear &Rental::getFrom()  {
    return from;
}

DayOfYear Rental::getUntil() {
    DayOfYear temp= from;
    for(int i=0; i<days-1; i++){
        temp=++temp;
    }
    return temp;
}

void Rental::print() {
    DayOfYear temp=getUntil();
    std::cout << from << " to "<< temp <<", rental no."<<no<<", for: "<<customer;
}

//schedule

class Schedule {
private:
    Vehicle* vehicle;
    Rental* year[365];
    //somehow include the condition of a rental being maximum 28 days.
    Schedule* next;

public:
    Schedule(Vehicle* vehicle);

    Vehicle* getVehicle() const;

    Schedule* getNext() const;

    void setNext(Schedule *next);

    bool isFree(DayOfYear firstdate, int noDaysToRent);

    float book(std::string customer, DayOfYear firstday, int noDaysToRent);


    void print(DayOfYear dayOfYear);

    void print();
};

//schedule implementation

Schedule::Schedule(Vehicle *vehicle) : vehicle(vehicle), next(nullptr) {
    for (int i = 0; i < 365; i++) {
        year[i] = nullptr;
    };
}

Vehicle* Schedule::getVehicle() const {
    return vehicle;
}

Schedule *Schedule::getNext() const {
    return next;
}

void Schedule::setNext(Schedule *next) {
    Schedule::next = next;
}

bool Schedule::isFree(DayOfYear firstDay, int noOfDaysToRent){
    bool flag = true;
    for(int i=0 ; i<noOfDaysToRent ; i++) //
    {
        if(year[i + firstDay.get_DayOfYear() -1 ] != nullptr){
            flag = false;
            std::cout<<flag<<'\n';
            return flag;
        }
    }

    return true;
}


float Schedule::book(std::string customer, DayOfYear firstday, int noDaysToRent) {
    int noOfMaxDaysYouCanRent;
    if(noDaysToRent>28){
        std::cout<<"Cannot book more than 28 days\n";
        noOfMaxDaysYouCanRent=28;
    }
    else{
        noOfMaxDaysYouCanRent= noDaysToRent;
    }


    if(isFree(firstday, noOfMaxDaysYouCanRent)){
        Rental* rental= new Rental(customer, firstday, noDaysToRent);
        for (int i=0; i<noDaysToRent; i++){
            year[firstday.get_DayOfYear() -1 + i]= rental;
        }
        return vehicle->get_price(noDaysToRent);
    }
    else{
        return 0.00;
    }
}



void Schedule::print(DayOfYear dayOfYear){
    vehicle->print();
    if(year[dayOfYear.get_DayOfYear()-1]!=nullptr){
        year[dayOfYear.get_DayOfYear()-1]->print();
    }
}

void Schedule::print(){
    std::cout<<"\nSCHEDULE FOR: ";
    vehicle->print();
    for(int i=0; i<365; i++){
        if(year[i]!=nullptr) {
            year[i]->print();
            std::cout<<'\n';
            i = i + (year[i]->getDays()) -1;
        }
    }
}


//Agency
class Agency {

private:
    float profitPercentage;
    float profit;
    Schedule* head;
    Schedule* last;
public:
    Agency();

    float getProfit() const;

    void setProfitPercentage(float profitPercentage);

    void add(Vehicle* vehicle);

    bool isFree(int VehicleNo, DayOfYear startDay, int noOfDaysToRent);

    float book(int VehicleNo, std::string customer, DayOfYear startday, int noOfDaysToRent);

    int chooseVehicle();

    void print(DayOfYear dayOfYear);

    void print();



protected:
    Schedule*  searchFor(int no);

};

//agency  implementation

Agency::Agency():
        profitPercentage(20),
        profit(0),
        head(nullptr),
        last(nullptr)
{}

float Agency::getProfit() const {
    return profit;
}

void Agency::setProfitPercentage(float profitPercentage) {
    Agency::profitPercentage = profitPercentage;
}

void Agency::add(Vehicle* vehicle){
    Schedule* temp=head;
    if(head == nullptr){
        head= new Schedule(vehicle);
    }

    else{
        while(temp->getNext()!=nullptr){
            temp=temp->getNext();
        }
        temp->setNext(new Schedule(vehicle));
    }

}

Schedule*  Agency::searchFor(int no){
    Schedule* temp= head;
    while(temp!=nullptr){
        if(temp->getVehicle()->getNo()==no){
            return temp;
        }
        else{
            temp=temp->getNext();
        }
    }
    std::cout<<"NO VEHICLE FOUND\n";
    return nullptr;
}

bool Agency::isFree(int VehicleNo, DayOfYear startDay, int noOfDaysToRent){
    Schedule* TheScheduleWeNeed= searchFor(VehicleNo);
    return  (TheScheduleWeNeed->isFree(startDay, noOfDaysToRent));
}



float Agency::book(int VehicleNo, std::string customer, DayOfYear startday, int noOfDaysToRent){
    if(isFree(VehicleNo, startday, noOfDaysToRent)){
        Schedule* theScheduleWeNeed= searchFor(VehicleNo);
        float priceOfBooking= theScheduleWeNeed->book(customer, startday, noOfDaysToRent);
        profit=(priceOfBooking*(profitPercentage/100))+profit;
        std::cout<<"booked, price for this rental: "<<priceOfBooking;
        return priceOfBooking;
    }
    else{
        std::cout<<"Sorry booking not done\n";
        return 0.00;
    }

}


//implement this later
int Agency::chooseVehicle(){
    Schedule* temp= head;
    while(temp!=nullptr){
        temp->getVehicle()->print();
        temp=temp->getNext();
    }

    std::cout<<"\nChoose vehicle no: \n";
    int vehicleChoice;
    std::cin>>vehicleChoice;

    return vehicleChoice;
}

//print all the bookings on a particular day;
void Agency::print(DayOfYear dayOfYear){
    Schedule* temp= head;
    while(temp!=nullptr){
        if(!(temp->isFree(dayOfYear, 1))){
            temp->print(dayOfYear);
            temp= temp->getNext();
        }
        else{
            temp=temp->getNext();
        }
    }
}

//prints all the schedules
void Agency::print(){
    Schedule* temp=head;
    while(temp!=nullptr){
        temp->print();
        temp=temp->getNext();
    }

    std::cout<<"\nProfit: "<<std::fixed<<std::setprecision(2)<< profit <<" EUR"<<'\n';
}
































const int DayOfYear::days[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int Rental::last_no = 0;
int Vehicle::noOfVehiclesAdded=0;
int Vehicle::noOfVehiclesAdded2=0;
std::string bikeModel="City";
std::string EbikeModel = "Trekky";
std::string EScooterModel= "Scooty";
int noBikesAdded=0;
int noEbikesAdded=0;
int noEScootersAdded=0;



int main() {



    bool quit = false;
    Agency DeutschLandRentACar;
    //update this variable to the current day when showing to the tutor,
    DayOfYear todaysDate;
    while (!quit) {
        std::cout << "\n\nSIMPLIFIED SIMULATION OF A RENTAL AGENCY\n"
                  << "========================================\n"
                  << "________________________________________\n"
                  << " MENUE\n"
                  << "A end of simulation\n"
                     "B set new simulation date\n"
                     "C new rental manually\n"
                     "D print rental of today "<<todaysDate;
        DayOfYear tomorrowsDate= ++todaysDate;
        std::cout<<
                     "\nE print rental of tomorrow "<< tomorrowsDate<<
                     "\nF print all rentals\n"
                     "G print agency profit\n"
                     "H set agency profit percent\n"
                     "I add bikes\n"
                     "J add E-bikes\n"
                     "K add E-scooters\n"
                     "L new rental simulation\n"
                     "your choice: \n";
        char choice;
        std::cin >> choice;
        switch (choice) {
            case ('A'): case'a':
                std::cout << "THANK YOU FOR USING THE SIMULATION\n";
                quit = true;
                break;
                case 'B': case 'b':
                std::cout<<"Enter today's date: ";
                std::cin>>todaysDate;
                break;

            case 'C': case'c' : {
                int VehicleNum = DeutschLandRentACar.chooseVehicle();
                DayOfYear dayOfRent; int numberOfDays; std::string name;
                std::cout<<"day of rental:";
                std::cin>>dayOfRent;
                std::cout<< "number of days:";
                std::cin>>numberOfDays;
                std::cout<<"input data vehicle renter name:";
                std::cin>>name;
                DeutschLandRentACar.book(VehicleNum,name, dayOfRent, numberOfDays);
                Vehicle::set_noOfVehiclesAdded(0);
                break;
            }

            case 'D': case'd':
                //method not complete
                std::cout<<"SCHEDULE FOR: "<<todaysDate<<'\n';
                DeutschLandRentACar.print(todaysDate);
                std::cout<<"\n________________________________________\n";

                break;
            case 'E': case'e':
                //method not complete
                std::cout<<"SCHEDULE FOR: "<<tomorrowsDate<<'\n';
                DeutschLandRentACar.print(++todaysDate);
                break;
            case 'F':case 'f':
                DeutschLandRentACar.print();
                Vehicle::set_noOfVehiclesAdded(0);

                break;
            case 'G': case 'g':
                std::cout<<"\nagency profit: "<<DeutschLandRentACar.getProfit()<<" EUR";
                break;
            case 'H':case'h':
                std::cout<<"\nAgency profit percent: ";
                float profitPercentage;
                std::cin>>profitPercentage;
                DeutschLandRentACar.setProfitPercentage(profitPercentage);
                break;
            case 'I': case'i':
                std::cout<<"\nHow many Bikes in this simulation? \n";
                int noOfBikes;
                std::cin>>noOfBikes;
                for(int i=0; i<noOfBikes; i++){
                    noBikesAdded++;
                    Vehicle::set_noOfVehiclesAdded2(Vehicle::get_noOfVehiclesAdded2()+1);
                    DeutschLandRentACar.add(new Bike(Vehicle::get_noOfVehiclesAdded2(), bikeModel));
                }
                break;

            case 'J':case 'j':
                std::cout<<"\nHow many E-Bikes in the simulation? \n";
                int noOfEbikes;
                std::cin>>noOfEbikes;
                for(int i=0; i<noOfEbikes; i++){
                    noEbikesAdded++;
                    Vehicle::set_noOfVehiclesAdded2(Vehicle::get_noOfVehiclesAdded2()+1);
                    DeutschLandRentACar.add(new EBike(Vehicle::get_noOfVehiclesAdded2(), EbikeModel));
                }
                break;

                case 'K': case'k':
                std::cout<<"\nHow many E-Scooters in the simulation? \n";
                int noOfEscooters;
                std::cin>>noOfEbikes;
                for(int i=0; i<noOfEbikes; i++){
                    noEScootersAdded++;
                    Vehicle::set_noOfVehiclesAdded2(Vehicle::get_noOfVehiclesAdded2()+1);
                    DeutschLandRentACar.add(new EScooter(Vehicle::get_noOfVehiclesAdded2(), EScooterModel));
                }
                break;

            default:
                std::cout<<"\nplease enter a valid letter\n";
                break;
        }

    }
}