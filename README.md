# DSTR
Data Structures and Algorithms assignment
Group 32

## Contents
- [Team Members](#team-members)
- [Task Division](#task-division)
- [Assignment Question](#assignment-question)
- [Requirements](#requirements)
- [Guidelines for Team Members](#guidelines-for-team-members)
- [Q&A](#q--a)

## Team Members
- #### TP084561
> Colin Subira Kwilabya  
- #### TP081705
> Kurapatkin Aliaksandr  
- #### TP082557  
> Leon Frank Aminiel
- #### TP082459
> Mohamed Abdifatah Ali
- #### TP069434  
> Omar AlaaEldin Elsayed Farrag

## Task Division

### Explanation
This assignment would be completed in subgroups.
1 (ONE) person completes the *general (common) part*, including:
- making type aliases (sptr, i8, u32, etc.),
- creating string literals/constants,
- implementing basic and helper classes (e.g. `Resident`) and other project-wide types (classes, enums, structs, etc.), including the ones used for time, date, maths,
- CLI (Command-Line Interface) basics

2 (TWO) people implement the *array* part, that includes all of the following:
- data structure implementation (with templates and `std::vector<>`-like inner storage; refer to
[this](https://medium.com/@simonyihunie/arrays-vs-vectors-in-modern-c-a-detailed-comparison-with-examples-b797fefff7f7) 
or [this](https://stackoverflow.com/questions/6462985/c-stdvector-vs-array-in-the-real-world) 
webpage to learn the difference between basic array, `std::array` and `std::vector`),
- sort algorithms: bubble sort, insertion sort. More might be added later,
- search algorithms: linear (brute-force), binary, jump. More might be added later,
- access API (application programming interface), including square brackets (`[]`) operator,
- insert/delete API,
- analysis API

2 (TWO) people implement the *list* part, that includes all of the following:
- data structure implementation (with templates and *single*-linked nodes;
refer to [this](https://www.geeksforgeeks.org/dsa/types-of-linked-list/)
webpage to learn about the different types of linked lists),
- sort algorithms: bubble sort, quick sort. More might be added later,
- search algorithms: linear (brute-force), binary, exponential. More might be added later,
- access API (application programming interface), including square brackets (`[]`) operator,
- insert/delete API,
- analysis API

### Assignees
*General* functionality - [Alex](#tp081705)  
*Array* Implementation - [Leo](#tp082557) and [Moha](#TP082459)  
*List* Implementation - [Colin](#TP084561) and [Omar](#TP069434)  


## Assignment Question
All the parts of this project are created following the initial assignment question. The exact PDF-document may be opened with [this link](./doc/AssignmentT1.pdf) 

## Requirements

## Guidelines for Team Members
> [!TIP]
> If it appears that after reading all the `.md` guidelines and [Q&A Section](#q--a) you
still have any questions, please follow this order to make
a research on the topic:
> 1. ChatGPT/DeepSeek/Grok/Claude
(Be aware of coding mistakes if not context-pretrained)
> 2. Perplexity + Google 
> 3. YouTube
> 4. Reddit
> 5. StackOverflow
(Actually the best one if u know how to find what you need.
So you can try it even before any GPT.
Or set GPT to "search"/"web" and ask it
to give the references from this website.)
> 6. Group Leader

### Toolchain/Framework
- For this assignment Group 32 is using C++ 17 standard.  
- Target platform: Windows 10/11.  
- Any IDE would be okay, yet Microsoft Visual Studio (Not Visual Studio Code) is recommended.
You don't have to use Enterprise (or any paid) edition.
Community Edition is enough for this assignment.  
- CMake is used as a building system.  
- Git + GitHub basic toolchain (without CI pipeline) would be used
for version control and Kanban workflow.   
- Unit tests may be implemented with Google Test.  
- No building speed requirements.  
- Execution speed / time might be measured with standard `std::chrono` tools. No profiling toolchain required for now (might be changed according to the lecturer requirements).  
- Memory usage might be measured with ?
- Multithreading implementation is not required.

### Style and Naming Conventions
We are using the C++ Google coding style with some minor changes.
The exact guidelines and coding style requirements can be found [here](./doc/code-style.md).

### Documentation
Documentation might be implemented in 2 ways:
1. Create your own `.md` file in `docs` directory. No formatting required.
2. Write comments on each entity: classes, methods, fields, constants.

You can pick one or do both.  
Check [this file](./doc/code-doc.md) to understand what exactly do you need to mention in documentation.

## Q & A
Here would be stated all the unclear requirements and all other questions related to this assignment. Together with supervisor's answers.

### Q1
What C++ standard should we use? C++ 17?

#### Answer
--

### Q2
Is it allowed to use JSON files?

#### Answer
Yes, but only for this lecture (L3-ABA).

### Q3
What about the unit tests? Is it allowed or redundant? Does it count as creativity?

#### Answer
--

### Q4
How do we measure the memory usage for the data structures?
Do we use profiling tools or just `sizeof()` operator?
If someone is coding with Visual Studio Code, what profiling tools should they use?

#### Answer
--

### Q5
"Carpool" and "Car" are the same Mode Of Transport or different?
"School Bus" and "Bus"?

#### Answer
--

### Q6
What is meant by "analysis operations" in assignment question?

#### Answer
--
