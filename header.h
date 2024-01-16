                                     /* NAME: AZMAR KASHIF
                                        SECTION: B
                                        ROLL NO: 22I-2716
                                                          */
#include<iostream>
#include<climits>
#include<string>
#include<limits>
#include<iomanip>
using namespace std;

// Define structures
struct Skill {
    string skillName;
    int proficiency_level;
    Skill* next;

    Skill(string  skillRequired, int _proficiency_level)
        : skillName(skillRequired), proficiency_level(_proficiency_level), next(nullptr) {}
};

struct Resource {
    int id;
    int availability;
    Skill* skill;
    Resource* next;
    Resource(int _id, int _availability, Skill* _skill)
        : id(_id), availability(_availability), skill(_skill), next(nullptr) {}
};

struct Task {
    int id;
    string name; // Task name as string
    int duration;
    int start_time;
    int* dependencies;
    int num_Dependencies;
    int early_start;
    int early_finish;
    int late_start;
    int late_finish;
    Skill* skill;
    bool isCritical; // Added member to identify critical tasks
    Task* next;

    Task(const string& _name, int _duration, Skill* _skill, int _num_Dependencies)
        : id(0), name(_name), duration(_duration), start_time(0),
          skill(_skill), next(nullptr), num_Dependencies(_num_Dependencies),
          early_start(-1), early_finish(-1), late_start(-1), late_finish(-1), isCritical(false) {
        dependencies = new int[num_Dependencies]();
    }

    ~Task() {
        delete[] dependencies;
    }
};

struct Project {
    int id;
    int duration;
    Task* tasks;
    Resource* resources;

    Project(int _id, int _duration)
        : id(_id), duration(_duration), tasks(nullptr), resources(nullptr) {}
};

// Function to validate and get a positive integer input
int getPositiveIntegerInput(const string& prompt) {
    int value;
    do {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    return value;
}

// Function to validate and get an integer input within a range
int getIntegerInputWithinRange(const string& prompt, int minValue, int maxValue) {
    int value;
    do {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < minValue || value > maxValue) {
            cout << "Invalid input. Please enter an integer within the range [" << minValue << ", " << maxValue << "]." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    return value;
}

// Function to validate and get a string input
string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin >> input;
    return input;
}

int resID() {
    static int resIDCounter = 1;
    return resIDCounter++;
}
// Function definitions
void addResources(Project& myProject) { // Function to add resources to the project
    int num_Resources;
    cout << "Enter the number of resources: ";
    cin >> num_Resources;

    for (int i = 0; i < num_Resources; i++) {
        string skillName;
        int availability;
        int profLvl;
        cout << "Enter details for resource " << i + 1 << ":" << endl;
        cout << "Skill Name: ";
        cin >> skillName;
        cout << "Skill Proficiency Level: ";
        cin >> profLvl;
        cout << "Availability [0/1]: ";
        cin >> availability;
        Skill* skill = new Skill(skillName, profLvl); // Create a new skill
        Resource* newResource = new Resource(resID(), availability, skill); // Create a new resource

        if (myProject.resources == nullptr) { // If the resource list is empty
            myProject.resources = newResource; // Add the resource to the list
        } else {    
            Resource* temp = myProject.resources;
            while (temp->next != nullptr) { // Traverse to the end of the list
                temp = temp->next; // Add the resource to the end of the list
            }
            temp->next = newResource; // Add the resource to the end of the list
        }
    }
}

void addTasks(Project& myProject) {
    int num_Tasks;
    cout << "Enter the number of tasks: ";
    cin >> num_Tasks;

    for (int i = 0; i < num_Tasks; i++) {
        string skillReq;
        int profLvl, num_Dependencies;

        cout << "Enter details for task " << i + 1 << ":" << endl;
        string taskName;
        cout << "Name: ";
        cin >> taskName;

        int taskId = i + 1; // Task ID is assigned sequentially
        cout << "Duration: ";
        int duration;
        cin >> duration;

        cout << "Skill Required: ";
        cin >> skillReq;

        cout << "Number of Dependencies: ";
        cin >> num_Dependencies;

        Skill* skill = new Skill(skillReq, profLvl); 
        Task* newTask = new Task(taskName, duration, skill, num_Dependencies);
        newTask->id = taskId; // Assigning task ID

        if (myProject.tasks == nullptr) { // If the task list is empty
            myProject.tasks = newTask; // Add the task to the list
        } else {
            Task* temp = myProject.tasks; // Traverse to the end of the list
            while (temp->next != nullptr) { // Add the task to the end of the list
                temp = temp->next;    // Add the task to the end of the list
            }
            temp->next = newTask;
        }

        // If dependencies exist, let the user specify them later
        if (num_Dependencies > 0) {
            cout << "Specify dependencies for Task " << taskId << ": ";
            for (int j = 0; j < num_Dependencies; j++) { 
                cin >> newTask->dependencies[j];
            }
        }
    }
}

void setTaskDuration(Task* head, int newDuration) { // Function to set the duration of all tasks
    Task* temp = head;
    while (temp != nullptr) { // Traverse the list and set the duration of each task
        temp->duration = newDuration; // to the new duration
        temp = temp->next; // Traverse to the next task
    }
}

void setNthTaskDuration(Task* head, int taskId, int newDuration) { // Function to set the duration of a specific task
    Task* temp = head;
    while (temp != nullptr && temp->id != taskId) { // Traverse the list and find the task with the given ID
        temp = temp->next; // Traverse to the next task 
    }

    if (temp != nullptr) { // If the task is found, set the duration to the new duration
        temp->duration = newDuration; // Otherwise, do nothing
    }
}

void printTaskDependencyList(Task* head) {
    Task* temp = head;
    while (temp != nullptr) {
        cout << "Task " << temp->id << ": ";
        if(temp->num_Dependencies == 0){ // If the task has no dependencies
            cout << "None";
        }
        for (int i = 0; i < temp->num_Dependencies; i++) { // Print the dependencies of the task
            cout << temp->dependencies[i] << " ";
        }
        cout << endl;
        temp = temp->next;
    }
}


void calculateBasicSchedule(Task* head) { // Function to calculate the basic schedule
    Task* temp = head;
    int currTime = 0; // Initialize current time to 0 for the first task

    while (temp != nullptr) {
        int max_startTime = currTime; // Initialize max start time to current time

        // Update early start and early finish
        temp->early_start = max_startTime; // Early start time is the max of current time and max start time
        temp->early_finish = max_startTime + temp->duration; // Early finish time is the early start time + duration

        // Update start time for the next task
        currTime = temp->early_finish; // Current time is the early finish time of the current task

        temp = temp->next;
    }
}

void calculateLateSchedule(Task* head) {
    Task* temp = head;
    int projDur = 0; // Initialize project duration to 0

    // Find the project completion time
    while (temp != nullptr) {
        int taskEndTime = temp->start_time + temp->duration; // Calculate the end time of the task
        projDur = max(projDur, taskEndTime); // Project duration is the max of project duration and task end time
        temp = temp->next;
    }

    // Initialize late start and late finish for each task
    temp = head;
    while (temp != nullptr) {
        temp->late_finish = projDur; // Late finish time is the project duration
        temp->late_start = temp->late_finish - temp->duration; // Late start time is the late finish time - duration
        temp = temp->next;
    }

    // Propagate late finish times backward
    bool flag;
    do {
        flag = false;
        temp = head;
        while (temp != nullptr) {
            int ls = temp->late_finish - temp->duration;  // Late start time is the late finish time - duration
            for (int i = 0; i < temp->num_Dependencies; i++) { // Check dependencies
                Task* dependency = head; // Find the dependency
                while (dependency != nullptr && dependency->id != temp->dependencies[i]) { // Find the dependency
                    dependency = dependency->next; // Find the dependency
                }

                if (dependency != nullptr) { // If the dependency is found
                    ls = min(ls, dependency->late_start); // Late start time is the min of late start time and dependency late start time
                }
            }

            if (ls < temp->late_start) { // If late start time is less than the current late start time
                temp->late_start = ls; // Update late start time
                temp->late_finish = temp->late_start + temp->duration; // Update late finish time
                flag = true; // Set flag to true to indicate that late finish times need to be propagated backward again
            }

            temp = temp->next;
        }
    } while (flag); // Repeat until late finish times are not updated anymore
}

void identifyCriticalPath(Task* head) { // Function to identify the critical path
    Task* temp = head;
    while (temp != nullptr) {
        if (temp->early_start == temp->late_start && temp->early_finish == temp->late_finish) { // If early start time and late start time are equal
            temp->isCritical = true; // and early finish time and late finish time are equal, the task is critical
        } else {
            temp->isCritical = false; // Otherwise, the task is not critical
        }
        temp = temp->next; // Traverse to the next task
    }
}

void printCriticalTasks(Task* head) {
    cout << "Critical Tasks:" << endl;

    Task* temp = head;
    while (temp != nullptr) {
        int slack = temp->late_start - temp->early_start;
        slack = (slack < 0) ? -slack : slack; // Ensure non-negative slack

        if (temp->isCritical || slack == 0) {
            cout << "Task " << temp->id << " - Duration: " << temp->duration << endl;
        }

        temp = temp->next;
    }
}


void completionTimeWithResources(Task* head, Resource* resources) {

    Task* temp = head;
    while (temp != nullptr) {
        int earliestStartTime = INT_MAX; // Initialize earliest start time to infinity
        Resource* availableResource = nullptr; // Initialize available resource to null

        // Find the earliest available resource for the task
        Resource* resourceTemp = resources; // Traverse the resource list
        while (resourceTemp != nullptr) { // Find the resource with the earliest availability
            int res_EndTime = resourceTemp->availability; // Resource end time is the resource availability

            // Check dependencies
            for (int i = 0; i < temp->num_Dependencies; i++) { // Check dependencies
                Task* dependency = head; // Find the dependency
                while (dependency != nullptr && dependency->id != temp->dependencies[i]) { // Find the dependency
                    dependency = dependency->next; // Find the dependency
                }

                if (dependency != nullptr) {
                    int dep_EndTime = dependency->start_time + dependency->duration; // Dependency end time is the dependency start time + duration
                    res_EndTime = max(res_EndTime, dep_EndTime);    // Resource end time is the max of resource end time and dependency end time
                }
            }

            if (res_EndTime < earliestStartTime) { // If resource end time is less than earliest start time
                earliestStartTime = res_EndTime; // Update earliest start time
                availableResource = resourceTemp; // Update available resource
            }

            resourceTemp = resourceTemp->next; // Traverse to the next resource
        }

        // Assign the resource and update start time
        if (availableResource != nullptr) { // If an available resource is found
            temp->start_time = earliestStartTime; // Update start time
            availableResource->availability = earliestStartTime + temp->duration; // Update resource availability
        }

        temp = temp->next;
    }
}

void completionTimeWithResourceProficiency(Task* head, Resource* resources) { 
    // Assuming resource availability and proficiency level are considered

    Task* temp = head; // Traverse the task list
    while (temp != nullptr) {
        int earliestStartTime = INT_MAX; // Initialize earliest start time to infinity
        Resource* availableResource = nullptr; // Initialize available resource to null

        // Find the earliest available resource for the task based on proficiency level
        Resource* resourceTemp = resources; // Traverse the resource list
        while (resourceTemp != nullptr) {
            if (resourceTemp->skill->skillName == temp->skill->skillName && 
                resourceTemp->skill->proficiency_level >= temp->skill->proficiency_level) { // Check if the resource has the required skill and proficiency level
                int res_EndTime = resourceTemp->availability; // Resource end time is the resource availability

                // Check dependencies
                for (int i = 0; i < temp->num_Dependencies; i++) { // Check dependencies
                    Task* dependency = head; 
                    while (dependency != nullptr && dependency->id != temp->dependencies[i]) {  // Find the dependency
                        dependency = dependency->next; // Find the dependency
                    }

                    if (dependency != nullptr) { // If the dependency is found
                        int dep_EndTime = dependency->start_time + dependency->duration; // Dependency end time is the dependency start time + duration
                        res_EndTime = max(res_EndTime, dep_EndTime); // Resource end time is the max of resource end time and dependency end time
                    } 
                }

                if (res_EndTime < earliestStartTime) { // If resource end time is less than earliest start time
                    earliestStartTime = res_EndTime; // Update earliest start time
                    availableResource = resourceTemp;  // Update available resource
                }
            }

            resourceTemp = resourceTemp->next;
        }

        // Assign the resource and update start time
        if (availableResource != nullptr) { // If an available resource is found
            temp->start_time = earliestStartTime; // Update start time
            availableResource->availability = earliestStartTime + temp->duration; // Update resource availability
        }

        temp = temp->next;
    }
}

void deleteSkills(Skill* head) {
    while (head != nullptr) {
        Skill* temp = head;
        head = head->next;
        delete temp;
    }
}

// Function to display the schedule
void displaySchedule(Task* head) {
    Task* temp = head;

    cout << "=========================================================================================================\n";
    cout << "| Task ID | Task Name      | Duration | Early Start | Early Finish | Late Start | Late Finish | Slack | Critical |\n";
    cout << "=========================================================================================================\n";
    
    while (temp != nullptr) {
        int slack = temp->late_start - temp->early_start;
        slack = (slack < 0) ? -slack : slack;  // Ensure non-negative slack

        cout << "|    " << temp->id << "    | " << setw(14) << temp->name << " |    " << temp->duration << "    |      " 
            << temp->early_start << "      |      " << temp->early_finish << "       |      " << temp->late_start 
            << "     |      " << temp->late_finish << "      |   " << slack << "   |    " << (temp->isCritical ? "Yes" : "No") << "    |\n";

        temp = temp->next;
    }

    cout << "=========================================================================================================\n";
}

// Function to display the schedule with resource availability
void displayCompletionTimeWithResources(Task* head, Resource* resources) {
    Task* temp = head;
    cout << "============================================================\n";
    cout << "| ID | ES | EF | Slack | Resource Availability |\n";
    cout << "============================================================\n";
    
    while (temp != nullptr) {
        int slack = temp->late_start - temp->early_start;
        slack = (slack < 0) ? -slack : slack;  // Ensure non-negative slack

        cout << "|  " << temp->id << " | " << setw(2) << temp->early_start << " | " << setw(2) << temp->early_finish << " | " << setw(3) << slack << " |           " << resources->availability << "           |\n";

        temp = temp->next;
    }

    cout << "============================================================\n";
}

// Function to display the schedule with resource proficiency
void displayCompletionTimeWithResourceProficiency(Task* head, Resource* resources) {
    Task* temp = head;

    cout << "==============================================================\n";
    cout << "| ID | ES | EF | Slack | Res Proficiency |\n";
    cout << "==============================================================\n";
    
    while (temp != nullptr) {
        int slack = temp->late_start - temp->early_start; // Ensure non-negative slack
        slack = (slack < 0) ? -slack : slack;  // Ensure non-negative slack

        cout << "|  " << temp->id << " | " << setw(2) << temp->early_start << " | " << setw(2) << temp->early_finish << " | " << setw(3) << slack << " |        " << resources->skill->proficiency_level << "         |\n";

        temp = temp->next;
        resources = resources->next;
    }

    cout << "==============================================================\n";
}

