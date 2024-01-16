                                     /* NAME: AZMAR KASHIF
                                        SECTION: B
                                        ROLL NO: 22I-2716
                                        Assignment # 2
                                                          */
#include<iostream>
#include<climits>
#include<string>
#include<limits>
#include<iomanip>
#include"header.h"
using namespace std;

int main() {
    Project myProject(1, 0);  // Assuming project starts at time 0

    int choice;
    do {
        cout << "\nProject Scheduling System Menu:" << endl;
        cout << "1. Add Resources" << endl;
        cout << "2. Add Tasks" << endl;
        cout << "3. Set Task Duration for All" << endl;
        cout << "4. Set Task Duration for a Specific Task" << endl;
        cout << "5. Print Task Dependency List" << endl;
        cout << "6. Calculate Basic Schedule" << endl;
        cout << "7. Print Critical Tasks" << endl;
        cout << "8. Completion Time with Resources" << endl;
        cout << "9. Completion Time with Resource Proficiency" << endl;
        cout << "0. Exit" << endl;

        choice = getIntegerInputWithinRange("Enter your choice: ", 0, 9);

        switch (choice) {
            case 1:
                addResources(myProject);
                break;
            case 2:
                addTasks(myProject);
                break;
            case 3:
                int newDuration;
                newDuration = getPositiveIntegerInput("Enter the new duration for all tasks: ");
                setTaskDuration(myProject.tasks, newDuration);
                break;
            case 4:
                int taskId, newTaskDuration;
                taskId = getPositiveIntegerInput("Enter the task ID: ");
                newTaskDuration = getPositiveIntegerInput("Enter the new duration for the task: ");
                setNthTaskDuration(myProject.tasks, taskId, newTaskDuration);
                break;
            case 5:
                printTaskDependencyList(myProject.tasks);
                break;
            case 6:
                calculateBasicSchedule(myProject.tasks);
                calculateLateSchedule(myProject.tasks);
                identifyCriticalPath(myProject.tasks);
                displaySchedule(myProject.tasks);
                break;
            case 7:
                printCriticalTasks(myProject.tasks);
                break;
            case 8:
                completionTimeWithResources(myProject.tasks, myProject.resources);
                displayCompletionTimeWithResources(myProject.tasks, myProject.resources);
                break;
            case 9:
                completionTimeWithResourceProficiency(myProject.tasks, myProject.resources);
                displayCompletionTimeWithResourceProficiency(myProject.tasks, myProject.resources);
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 0);

    // Free allocated memory
    deleteSkills(myProject.resources->skill);
    deleteSkills(myProject.tasks->skill);

    return 0;
}