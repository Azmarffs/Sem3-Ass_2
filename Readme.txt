
PROJECT  SCHEDULING SYSTEM:
OVERVIEW:
This C++ program serves as a comprehensive tool for managing project schedules and resource allocations. 
Leveraging linked data structures, it allows users to define and manipulate tasks, resources, and skills within a project context.
The program covers crucial aspects of project management, including task dependencies, scheduling, critical path identification, 
and considerations for both resource availability and proficiency levels.

KEY COMPONENTS:
1. Structures
Skill
The Skill structure encapsulates a skill required for a task. It includes the skill's name and the proficiency level needed.

->Resource
          Resource represents an entity within the project that contributes to task completion. Each resource has an identifier (id),   availability 
          status, and a set of skills.

->Task
    A Task represents a specific unit of work within the project. It incorporates details such as task name, duration, dependencies on other
    tasks, and scheduling information. Tasks can be linked to specific skills required for their completion.

->Project
       The overarching Project structure brings together tasks and resources, providing a cohesive representation of the entire project.

2. Functions
->Adding Resources and Tasks
                            Functions like addResources and addTasks guide users through the process of introducing resources and tasks into the project. 
                            These functions prompt users to input relevant details such as resource availability, skill proficiency, task duration, and dependencies.

->Setting Task Durations
                        The program provides flexibility in managing task durations. The functions setTaskDuration and setNthTaskDuration allow users to 
                        set durations for tasks collectively or individually.

->Calculating Schedules
                        Two key functions, calculateBasicSchedule and calculateLateSchedule, are responsible for computing task schedules. The basic schedule r
                        epresents the earliest start and finish times for tasks, while the late schedule considers dependencies and calculates the latest start
                        and finish times.

->Identifying Critical Path
                            The identifyCriticalPath function determines the critical path within the project. Tasks on the critical path are those that, if delayed,
                            would directly impact the project's overall completion time.

->Completion Time with Resources
                                The function completionTimeWithResources calculates project completion time, taking into account the availability of resources. 
                                It considers the earliest available resource for each task, factoring in dependencies.

->Completion Time with Resource Proficiency
                                            Building on the previous function, completionTimeWithResourceProficiency adds an extra layer of complexity by considering resource proficiency
                                            levels. This ensures that tasks are assigned to resources with the required skills and proficiency levels.

->Display Functions
                    Several functions, such as displaySchedule, displayCompletionTimeWithResources, and displayCompletionTimeWithResourceProficiency, offer 
                    users visibility into different aspects of the project. They provide detailed schedules, critical task information, and completion time
                    with resource details.