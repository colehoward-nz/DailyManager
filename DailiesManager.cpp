#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

// task structure
struct task
{
	std::string title;
	bool status = false;
};

void refresh()
{
	// Will run cls in the window
	// This works for windows devices,
	// but not for linux/mac I believe.
	std::system("cls");
}



// operation functions
void load(std::vector<task> &tasks)
{
	std::ifstream file("tasks.txt");
	if (file.is_open())
	{
		task task;
		while (getline(file, task.title))
		{
			file >> task.status;
			tasks.push_back(task);

			// Ignores newline character
			file.ignore();
		}
		file.close();
	}
}

void save(const std::vector<task>& tasks)
{
	std::ofstream file("tasks.txt");
	if (file.is_open())
	{
		// Loop through all tasks in the tasks vector
		for (const task& task : tasks)
		{
			file << task.title << "\n";
			file << task.status << "\n";
		}
		file.close();
	}
}

void view(const std::vector<task>& tasks)
{
	if (tasks.size() == 0)
	{
		std::cout << "There are no tasks!\n\n";
		return;
	}

	std::cout << "---------------------\n";
	std::cout << "      Daily Tasks\n";
	std::cout << "---------------------\n";

	for (size_t i = 0; i < tasks.size(); i++) {
		std::cout << std::setw(2) << "(" << i + 1 << ") ";
		if (tasks[i].status) {
			std::cout << "[X] ";
		}
		else {
			std::cout << "[ ] ";
		}
		std::cout << tasks[i].title << "\n";
	}
	std::cout << "---------------------\n\n";
}

void add(std::vector<task>& tasks)
{
	task newTask;
	std::cout << "Enter title of task: ";

	// This will clear input buffer and will wait for users input.
	std::cin.ignore(); 

	// We use getline to retrieve the entire line, incase the title includes spaces.
	std::getline(std::cin, newTask.title);

	newTask.status = false;
	tasks.push_back(newTask);
	std::cout << "Added new task '" << newTask.title << "'\n\n";
}

void remove(std::vector<task>& tasks)
{
	// Show all available tasks
	view(tasks);

	int id;
	std::cout << "Enter ID of task you wish to remove: ";
	std::cin >> id;

	// Check if ID is within tasks vector
	if (id > 0 && id <= tasks.size())
	{
		tasks.erase(tasks.begin() + (id - 1));

		// Show updated task list
		refresh();
		view(tasks);

		std::cout << "Removed task with ID " << id << ".\n\n";
	}
	else
	{
		std::cout << "Unknown task ID.\n\n";
	}
}

void toggle(std::vector<task>& tasks)
{
	// Show all available tasks
	view(tasks);

	int id;
	std::cout << "Enter ID of task you wish to toggle: ";
	std::cin >> id;

	// Check if ID is within tasks vector
	if (id > 0 && id <= tasks.size())
	{
		task& target = tasks[id-1];
		target.status = !target.status;

		refresh();
		view(tasks);
		std::cout << "Set status of ID " << id << " to " 
		<< (target.status ? "Completed" : "Uncompleted") << "\n\n";
	}
	else
	{
		std::cout << "Unknown task ID.\n\n";
	}
}



int main()
{
	// Load tasks from file.
	std::vector<task> tasks;
	load(tasks);
	view(tasks);

	int option = 5;
	do 
	{
		std::cout << "(1) View daily tasks\n";
		std::cout << "(2) Add task\n";
		std::cout << "(3) Remove task\n";
		std::cout << "(4) Toggle status\n";
		std::cout << "(5) Quit program\n";
		std::cin >> option;

		// Clear console window
		refresh();

		switch (option)
		{
			// View tasks
			case 1:
				view(tasks);
				break;

			// Add task
			case 2:
				add(tasks);
				break;

			// Remove task
			case 3:
				remove(tasks);
				break;

			// Toggle task
			case 4:
				toggle(tasks);
				break;

			default:
				break;
		}
	} while (option != 5);

	// Save and farewell message
	save(tasks);
	std::cout << "Thanks for using the program!\n";
}