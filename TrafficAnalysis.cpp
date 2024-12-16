// Traffic analysis
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// Function to generate traffic summary report
void generateTrafficSummaryReport(const vector<string> &vectorTimeStamp, const vector<string> &vectorVehicleType, const vector<int> &vectorSpeed)
{
    // Using map as it uses key to access value this helps to keep track data
    // Create a map to store vehicle counts for each day. key is day of the week
    // and value is the vehicle count
    map<int, int> vehicleCountDay;

    // Create a map to store vehicle types and their counts,
    // key is the type of vehicle(car,truck, bus,...) and value is the vehicle type count
    map<string, int> vehicleType;

    // Display heading for the traffic summary report
    cout << "Traffic Summary Report:\n" << endl;
    cout << "---------------\n" << endl;

    // Get the total number of vehicles from the size of the timeStamp vector
    int totalVehicles = vectorTimeStamp.size();
    // Display the total number of vehicles
    cout << "Total vehicles: " << totalVehicles << endl;
    cout << "\n" << endl;

    // Loop to count vehicles per day based on the timeStamp vector
    for (int i = 0; i < vectorTimeStamp.size(); ++i)
    {
        // Accessing the timeStamp element in a vector and extract the day from the timeStamp
        // as the index start at 0, counting till index 8 then extracting 2 characters
        string timeStampStr = vectorTimeStamp[i].substr(8, 2);
        int day = stoi(timeStampStr);  // Convert timeStamp string to integer

        // Check if the day is within 1-6 days
        if (day > 0 && day <= 6)
        {
            vehicleCountDay[day - 1]++; // Increment the count of the day
        }
    }

    // Output the number of vehicles counted per day
    cout << "Vehicle count per day:\n" << endl;

    // Loop to display day and vehicle count
    for (int i = 0; i < 6; ++i)
    {
        // Display the count of vehicles for each day
        cout << "Day " << (i + 1) << ": " << vehicleCountDay[i] << " vehicles" << endl;
    }

    cout << "\n" << endl;

    // Display heading for vehicle distribution
    cout << "Vehicle distribution:\n" << endl;

    // Loop to count vehicle types based on the vector of vehicle types
   for (int i = 0; i < vectorVehicleType.size(); ++i)
   {
    string type = vectorVehicleType[i]; // Get the vehicle type at index i
    vehicleType[type]++; // Increment the count for the current vehicle type
   }

    double totalTypeVehicles = totalVehicles; // Store total vehicles type

    //Loop to iterate each entry in the vehicleType map
    for (const auto &type : vehicleType)
    {
        // Calculate the percentage of each vehicle type
        double percentage = (static_cast<double>(type.second) / totalTypeVehicles) * 100;
        // Display the count and percentage of each vehicle type
        cout << type.first << ": " << type.second << " vehicles (" << fixed << setprecision(2) << percentage << "%)" << endl;
    }
    cout << "\n" << endl;
}

// Function to generate peak traffic report
void generatePeakTrafficReport(const vector<string> &vectorTimeStamp, const vector<string> &vectorVehicleType, const vector<int> &vectorSpeed)
{
    cout << "Peak Traffic Times Report\n" << endl; // Display heading
    cout << "---------------\n" << endl;

    map<int, int> trafficByHour; // Map to count traffic by hour. Hour is the key and vehicle count is the value

    // Nested map to count traffic by hour and day, the outer map key is the day and the inner map is the value for the outer key,
    // the key is the hour and value is the vehicle count for the inner key
    map<int, map<int, int>> trafficByHourAndDay;

    // Loop through each timeStamp to gather traffic data
    for (int i = 0; i < vectorTimeStamp.size(); ++i)
    {
        // Extract hour and day from the timeStamp
        string hourStr = vectorTimeStamp[i].substr(11, 2); // Get hour at index 11  and extracting 2 characters)
        string dayStr = vectorTimeStamp[i].substr(8, 2); // Get day at index 8  and extracting 2 characters

        int hour = stoi(hourStr); // Convert hour string to integer
        int day = stoi(dayStr); // Convert day string to integer


        trafficByHour[hour]++; // Increment the count for the current hour
        trafficByHourAndDay[day][hour]++; // Increment the count for the current day
    }

    int peakHour = 0; // Variable to store the peak hour
    int maxVehicles = 0; // Variable to store the maximum vehicle count

    // Loop to find the peak hour for overall traffic in 24 hours
    for (int hour = 0; hour <= 24; ++hour)
    {
        // Check if the current hour has more vehicles than the recorded maximum
        if (trafficByHour[hour] > maxVehicles)
        {
            peakHour = hour; // update peak hour
            maxVehicles = trafficByHour[hour]; // Update maximum vehicles for this hour
        }
    }

    // Display the peak traffic time
    cout << "Peak traffic time (overall): " << setw(2) << setfill('0') << peakHour << ":00 - " << setw(2) << setfill('0')
         << peakHour + 1 << ":00" << " with " << maxVehicles << " Vehicles" << endl;
    cout << "\n" << endl;

    // Display heading for peak traffic by day
    cout << "Peak traffic by day:\n" << endl;

    // Loop through each day to find peak traffic times for 1-6 days
    for (int day = 1; day <= 6; ++day)
    {
        int maxVehiclesByDay = 0; // Variable to store the maximum vehicles for the day
        int peakHourByDay = 0; // Variable to store the peak hour for the day

        // Loop through each hour to find the peak hour for the day in 24 hours
        for (int hour = 0; hour <= 24; ++hour)
        {
            int vehicleCount = trafficByHourAndDay[day][hour]; // Get the vehicle count for this hour and day

            // Check if this hour has more vehicles than the recorded maximum for the day
            if (vehicleCount > maxVehiclesByDay)
            {
                peakHourByDay = hour; // Update peak hour for the day
                maxVehiclesByDay = vehicleCount; // Update maximum vehicles
            }
        }

        // Display the peak hour for this day
        cout << "- Day " << day  << ": " << setw(2) << setfill('0') << peakHourByDay << ":00 - "
             << setw(2) << setfill('0') << peakHourByDay + 1 << ":00, " << maxVehiclesByDay << " Vehicles" << endl;
    }
    cout << "\n" << endl;
}

// Function to generate speed analysis report
void generateSpeedReport(const vector<string> &vectorTimeStamp, const vector<string> &vectorVehicleType, const vector<int> &vectorSpeed)
{
    cout << "Speed Analysis Report:\n" << endl; // Display heading
    cout << "---------------\n" << endl;

    int totalSpeed = 0; // Variable to store total speed
    double averageSpeed = 0; // Variable to calculate average speed
    int slow = 0; // variable to count for slow vehicles
    int medium = 0; // variable to count for medium vehicles
    int fast = 0; // variable to count for fast vehicles

    // Loop through each speed in the vector
    for (int i = 0; i < vectorSpeed.size(); ++i)
    {
        int speed = vectorSpeed[i]; // Access each speed using the index
        totalSpeed += speed; // Add total speed


        if (speed <= 30) // Check if speed is between (0-30 km/h)
        {
            slow++; // Increment slow counter
        }
        else if (speed > 30 && speed <= 60) // Check if speed is between (30-60 km/h)
        {
            medium++; // Increment medium counter
        }
        else // Check if speed (60+ km/h)
        {
            fast++; // Increment fast counter
        }
    }

    double speedInDouble = totalSpeed; // variable to store total speed in double

    // Calculate average speed only if vectorSpeed is not empty to avoid zero division
    if (!vectorSpeed.empty())
    {
        averageSpeed = speedInDouble / vectorSpeed.size(); // Calculate average speed
    }

    // Display average speed and counts of slow, medium, and fast vehicles
    cout << "Average speed: " << averageSpeed << " km/h" << endl;
    cout << "- Slow (0-30 km/h): " << slow << " vehicles" << endl;
    cout << "- Medium (30-60 km/h): " << medium << " vehicles" << endl;
    cout << "- Fast (60+ km/h): " << fast << " vehicles" << endl;

    cout << "\n" <<endl;
}


int main()
{
    string fileName; // Declare a string variable for the file name
    ifstream inputFile; // Declare an input file stream
    string line; // Declare a string variable to read each line from the file

    // Vectors to store data from the file
    vector<string> vectorTimeStamp; // Vector to store timeStamps
    vector<string> vectorVehicleType; // Vector to store vehicle types
    vector<int> vectorSpeed; // Vector to store vehicle speeds

    // Loop to ensure the file opens successfully
    do
    {
        cout << "Enter File name (ending with .txt): "; // Ask the user for the file name
        getline(cin, fileName); // Get the file name from user input
        cout << "\n" << endl;

        inputFile.open(fileName); // Open the input file

        // Check if the file opened successfully
        if (!inputFile.is_open())
        {
            cout << "Cannot open file. Please try again\n" << endl; // Display error message
        }

    } while (!inputFile.is_open()); // Loop until the file opens successfully

    getline(inputFile, line); // Skip the first line (heading information)

    // Read data from the input file and store it in vectors
    while (getline(inputFile, line)) // Loop to read each line until the end of the file
    {

        stringstream ss(line); // Create a string stream to extract data from each line

        // Read time stamp from the line
        string timeStamp, vehicleType, speedStr; // Declare variables to hold extracted timeStamp
        getline(ss, timeStamp, ';'); // Extract timeStamp until the delimiter ';'
        vectorTimeStamp.push_back(timeStamp); // Add timeStamp to the vector

        // Read vehicle type from the line
        getline(ss, vehicleType, ';'); // Extract vehicleType until the delimiter ';'
        vectorVehicleType.push_back(vehicleType); // Add vehicleType to the vector

        // Read vehicle speed from the line
        getline(ss, speedStr); // Extract speed as a string
        int speed = stoi(speedStr); // Convert speed string to integer
        vectorSpeed.push_back(speed); // Add speed to the vector
    }

    inputFile.close(); // Close the input file

    // Call functions to generate reports
    generateTrafficSummaryReport(vectorTimeStamp, vectorVehicleType, vectorSpeed); // Call traffic summary report function
    generatePeakTrafficReport(vectorTimeStamp, vectorVehicleType, vectorSpeed); // Call peak traffic report function
    generateSpeedReport(vectorTimeStamp, vectorVehicleType, vectorSpeed); // Call speed report function

    return 0;
}
