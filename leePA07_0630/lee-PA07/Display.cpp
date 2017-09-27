#include "Display.h"

Display::Display()
{

}

//void function displaying the start screen. The starter for other functions
// display initial screen and call chooseShipment.
void Display:: startScreen()
{
    cout<<"***********************************************"<<endl;
    cout<<" L E E ' S    S H I P M E N T    M A N A G E R"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"Thanks for using Lee's Shipment Manager."<<endl;
    cout<<"This program will help you enter and manage information"<<endl;
    cout<<"and revenue on your daily shipments"<<endl;
    cout<<endl;
    cout<<"Please choose from the list of possible functions."<<endl;
    cout<<endl;
    chooseShipment();
}

//void function asking for shipment Type, and call different calculation functions according to the user's choice//
// In the end, call repeat function to ask user for more input //
void Display:: chooseShipment()
{
    //ask for shipment type
    char shipmentChoice = '\0';
    cout<<"What is the shipment type?"<<endl;
    cout<<endl;
    cout<<"1. Ground Shipment"<<endl;
    cout<<"2. Two Day Shipment"<<endl;
    cout<<"3. Overnight Shipment"<<endl;
    cin>>shipmentChoice;

    //input error check//
    while (shipmentChoice != '1' && shipmentChoice != '2' && shipmentChoice != '3')
    {
        cout<<"The input is invalid. Please choose again."<<endl;
        cin.clear();
        cin>>shipmentChoice;
    }

    if(shipmentChoice == '1')
    {
        Ground dispGnd;
        dispGnd.calcWeightFee(); // asks for user input on weight and calculate weight fee
    }
    else if(shipmentChoice == '2')
    {
        Twoday dispTdy;
        dispTdy.checkTrackService(); // asks for user input on trackingNumber and weight. Calculate service and weight fee.
    }
    else
    {
        Overnight dispOvn;
        dispOvn.checkConfirm(); // asks for user input on confirmation and weight. Calculate service and weight fee.
    }
    repeat(); // calls repeat function for further input.

}

//void function used for loop.
//asks user whether the user wants to input more data and if yes, call chooseShipment function.
void Display:: repeat()
{
    string repeat;
    cout<<"The information was saved successfully. Would you like to add more information?"<<endl;
    cout<<"[y/n]"<<endl;
    cin>>repeat;

    while (repeat != "y" && repeat != "n") // input error check.
    {
        cout<<"The input is invalid. Please choose again."<<endl;
        cin.clear();
        cin>>repeat;
    }

    if(repeat == "y") // if user chooses yes, restart chooseShipment function
    {
        chooseShipment();
    }
    else // if user chooses no, call finalScreen.
    {
        cout<<"The Program will now print the information of shipments."<<endl;
        cout<<endl;
        finalScreen();
    }
}

//void function. Calls all the display functions at the end of the program.
void Display:: finalScreen()
{
    printOvnList(); // print organized Overnight List
    printTdyList(); // print organized Twoday List
    printGndList(); // print organized Ground List
    subtotalConfirm(); // print the subtotal for Overnight Confirmation fee
    subtotalTrackNum(); // print the subtotal for Twoday Track Number fee
    subtotalWeightFee(); // print the subtotal for each and net weight charge
    subtotalFlatFee(); // print subtotal for each and net flat fee
    countOfPackage(); // print the count of each kinds of shipments and net shipment.
    totalRevenue(); // print the Total Revenue for the day.
}

// void function calls function from Ground Class which sorts and prints the array.
void Display:: printGndList()
{
    cout<<"3. A list of ground packages ordered by weight"<<endl;
    cout<<"**************************************"<<endl;
    Ground printGnd;
    printGnd.sortGround();
}

// void function calls function from Twoday Class which sorts and prints the array
void Display:: printTdyList()
{
    cout<<"2. A list of two-day packages ordered by weight in ascending order"<<endl;
    cout<<"**************************************"<<endl;
    Twoday printTdy;
    printTdy.sortTwoday();
}

//void function calls function from Overnight class which sorts and prints array.
void Display:: printOvnList()
{
    cout<<"1. A list of the overnight packages ordered by their tracking number"<<endl;
    cout<<"**************************************"<<endl;
    Overnight printOvn;
    printOvn.sortOvernight();
}

// double function returning the net service fee on Overnight shipment
// calls function from Overnight class that will calcuate the sum of confirmation fee
double Display:: subtotalConfirm() //Displays Overnight Subtotal of Confirm Fee
{
    cout<<"4. Amount of revenue generated by delivery confirmation"<<endl;
    cout<<"**************************************"<<endl;
    Overnight ovnSubConfirm;
    ovnSubConfirm.overnightSubTotConfirm(); // sums the service fee for all overnight shipments
    serviceFeeOvn = ovnSubConfirm.getOvernightSubTotConfirm(); // assign the sum to variable for later use
    return serviceFeeOvn;// return the value for total Revenue.
}

//double function returning the net service fee on Twoday Shipment
// calls function from Twoday class that will calculate the sum of tracking number fee
double Display:: subtotalTrackNum() // Displays Twoday Subtotal of Track Number Fee
{
    cout<<"5. Amount of revenue generated by tracking numbers for two-day packages"<<endl;
    cout<<"**************************************"<<endl;
    Twoday tdySubTrackNum;
    tdySubTrackNum.twodaySubtotTrack(); // sums the tracking number fee for all twoday Shipments
    serviceFeeTwo = tdySubTrackNum.getTwodaySubtotTrack(); // assign te sum to variable for later use
    return serviceFeeTwo;// return value for total Revenue.
}
//double function returning net weight charge
// calls function from all 3 package child classes to calculate individual weight charges and net charge
double Display:: subtotalWeightFee() //Displays Subtotal of Per Ounce Fee, for each kind of shipments and net.
{
    cout<<"6. Amount of revenue generated by per-ounce fees"<<endl;
    cout<<"**************************************"<<endl;
    Ground groundSubWeight;
    groundSubWeight.groundSubTotWeight(); // calcuate the value of weight charge for ground
    groundSubWeight.getGndSubTotWeight(); // get the value of weight charge for ground

    Twoday twodaySubWeight;
    twodaySubWeight.twodaySubTotWeight(); // calculate the value of weight charge for twoday
    twodaySubWeight.getTdySubTotWeight(); // get the value of weight charge for twoday

    Overnight overnightSubWeight;
    overnightSubWeight.overnightSubTotWeight(); // calculate the value of weight charge for overnight
    overnightSubWeight.getOvnSubTotWeight(); // get the value of weight charge for overnight
    netWeightFee = groundSubWeight.getGndSubTotWeight() + twodaySubWeight.getTdySubTotWeight() + overnightSubWeight.getOvnSubTotWeight();
    cout<<"The Net Subtotal for per-ounce fee is $ "<<netWeightFee<<endl; //assigned the sum to a variable for later use.
    cout<<endl; //extra blank space for readability
    return netWeightFee;// return value for totalRevenue
}
//double function returning net flat charge
// calls function from all 3 package child classes to calculate individual flat charges and net charge
double Display:: subtotalFlatFee() // Prints Subtotal for Flat Fee for each kind of shipment and net.
{
    cout<<"7. Amount of revenue generated by flat fees"<<endl;
    cout<<"**************************************"<<endl;
    Ground groundSubFlat;
    groundSubFlat.setGndFlat();//calculate flat fee for ground shipment
    cout<<"The Subtotal for Flat Fee of Ground Shipments is $ "<<groundSubFlat.getGndFlat()<<endl; //print charge

    Twoday twodaySubFlat;
    twodaySubFlat.setTdyFlat();//calculate flat fee for twoday shipment
    cout<<"The Subtotal for Flat Fee of Twoday Shipments is $ "<<twodaySubFlat.getTdyFlat()<<endl; //print charge

    Overnight overnightSubFlat;
    overnightSubFlat.setOvnFlat();//calculate flat fee for overnight shipment
    cout<<"The Subtotal for Flat Fee of Overnight Shipments is $ "<<overnightSubFlat.getOvnFlat()<<endl; //print charge
    cout<<endl;// extra blank space for readability.
    netFlatFee = groundSubFlat.getGndFlat() + twodaySubFlat.getTdyFlat() + overnightSubFlat.getOvnFlat();
    cout<<"The Net Subtotal for Flat Fee is $ "<<netFlatFee<<endl; // assign the sum to a variable for later use
    cout<<endl; //extra blank space for readability
    return netFlatFee;// return value for totalRevenue
}

//void function printing the count of each kind of shipment
//calls function from all 3 package child classes to print individual and total count of shipment
void Display:: countOfPackage() // Displays number of each kind of package and net.
{
    cout<<"8. Counts of the three types of packages and total number of packages"<<endl;
    cout<<"**************************************"<<endl;
    Ground gndCountPackage;
    Twoday tdyCountPackage;
    Overnight ovnCountPackage;

    cout<<"The Total number of shipments today are: ";
    //add up all the counters of each kind of shipments.
    cout<<gndCountPackage.updateGndCount()+tdyCountPackage.updateTdyCount()+ovnCountPackage.updateOvnCount()<<endl;
    cout<<endl;//blank for readability.
    cout<<"Shipment Type"<<endl;
    cout<<endl;//blank for readability.
    cout<<"Ground: "<<gndCountPackage.updateGndCount()<<endl; //count for ground shipment
    cout<<"Twoday: "<<tdyCountPackage.updateTdyCount()<<endl; // count for twoday shipment
    cout<<"Overnight: "<<ovnCountPackage.updateOvnCount()<<endl; //count for overnight shipment
    cout<<"**************************************"<<endl;
    cout<<endl; //blank for readability
}

//void function printing the total Revenue for the day
//sums up the values returned from the prior functions and print the result
void Display:: totalRevenue() // Will calculate and display the Total Revenue for the day.
{
    cout<<"9. Total amount of revenue generated today"<<endl;
    cout<<"**************************************"<<endl;
    //add up the values returned from confirmation fee, tracking number fee, flat fee and weight fee for total.
    cout<<"The Total Revenue for today is $ "<<serviceFeeOvn+serviceFeeTwo+netFlatFee+netWeightFee<<endl;
    cout<<"Thank you for choosing Lee's Shipment Manager. The Program will now Terminate."<<endl;
    cout<<"**************************************"<<endl;
}