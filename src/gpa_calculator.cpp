#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Asks until the user enters a valid positive whole number.
int readPositiveInt(const string &prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value) || value <= 0)
    {
        cout << "Invalid input! Please enter a positive number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n'); // remove the leftover newline
    return value;
}

// Converts a letter ("B+") or a number ("90" or "3.5") into grade points.
// Returns -1.0 if the grade is not valid.
double gradeToPoints(string g)
{
    transform(g.begin(), g.end(), g.begin(),
              [](unsigned char c)
              { return static_cast<char>(toupper(c)); });

    if (g == "A+" || g == "A")
        return 4.0;
    if (g == "A-")
        return 3.7;
    if (g == "B+")
        return 3.3;
    if (g == "B")
        return 3.0;
    if (g == "B-")
        return 2.7;
    if (g == "C+")
        return 2.3;
    if (g == "C")
        return 2.0;
    if (g == "C-")
        return 1.7;
    if (g == "D+")
        return 1.3;
    if (g == "D")
        return 1.0;
    if (g == "D-")
        return 0.7;
    if (g == "F")
        return 0.0;

    // Numeric grade: a percentage (like 90) or points (like 3.5)
    try
    {
        size_t used = 0;
        double score = stod(g, &used);
        if (used != g.size())
            return -1.0; // e.g. "90abc"
        if (score < 0 || score > 100)
            return -1.0;

        if (score > 4.0)
        {
            if (score >= 90)
                return 4.0;
            else if (score >= 85)
                return 3.7;
            else if (score >= 80)
                return 3.3;
            else if (score >= 75)
                return 3.0;
            else if (score >= 70)
                return 2.7;
            else if (score >= 65)
                return 2.3;
            else if (score >= 60)
                return 2.0;
            else if (score >= 50)
                return 1.0;
            else
                return 0.0;
        }
        return score;
    }
    catch (...)
    {
        return -1.0; // not a number at all
    }
}

// Data entry with input validation.
void addCourses(vector<string> &courses, vector<int> &credits, vector<string> &grades)
{
    int courseCount = readPositiveInt("How many courses do you want to add? ");

    for (int i = 0; i < courseCount; i++)
    {
        cout << "\n--- Course " << i + 1 << " of " << courseCount << " ---\n";

        string course;
        do
        {
            cout << "Enter course name: ";
            getline(cin, course); // allows spaces in the name
        } while (course.empty());
        courses.push_back(course);

        credits.push_back(readPositiveInt("Enter credit hours (e.g., 2, 3): "));

        string grade;
        while (true)
        {
            cout << "Enter grade (e.g., A, B+, or 90): ";
            cin >> grade;
            cin.ignore(10000, '\n');
            if (gradeToPoints(grade) >= 0)
                break;
            cout << "Invalid grade! ";
        }
        grades.push_back(grade);
    }
}

// Transcript summary.
void printTranscript(const vector<string> &courses, const vector<int> &credits,
                     const vector<string> &grades)
{
    cout << "\n==============================\n";
    cout << "         COURSE SUMMARY       \n";
    cout << "==============================\n";
    for (size_t i = 0; i < courses.size(); i++)
    {
        cout << "Course: " << courses[i]
             << " | Credits: " << credits[i]
             << " | Grade: " << grades[i]
             << " (Points: " << gradeToPoints(grades[i]) << ")" << endl;
    }
    cout << "------------------------------\n";
}

// GPA calculation: total (points x credits) divided by total credits.
double calculateGPA(const vector<string> &grades, const vector<int> &credits)
{
    double totalPoints = 0;
    int totalCredits = 0;

    for (size_t i = 0; i < grades.size(); i++)
    {
        totalPoints += gradeToPoints(grades[i]) * credits[i];
        totalCredits += credits[i];
    }

    if (totalCredits == 0)
        return 0.0;
    return totalPoints / totalCredits;
}

int main()
{
    vector<string> courses;
    vector<int> credits;
    vector<string> grades;

    cout << fixed << setprecision(2); // show 3.50 instead of 3.5

    addCourses(courses, credits, grades);
    printTranscript(courses, credits, grades);

    cout << "Your Cumulative GPA is: " << calculateGPA(grades, credits) << endl;
    return 0;
}