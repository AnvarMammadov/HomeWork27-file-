#include<iostream>
#include<fstream>
using namespace std;
//Job
//No, name, salary, company
//ShowAllJobs
//Add New Job
//Delete job by no
//
//1, Developer, 4000, ShawAgent

struct Job
{
	char* name;
	char* company;
	int salary;
	int no;
};
void CreateFile(const char* filename) {
	FILE* file;
	fopen_s(&file, filename, "wb");
	fclose(file);
}
void WriteFile(const char* filename, Job**& jobs, int& count) {
	FILE* file;
	fopen_s(&file, filename, "wb");
	fwrite(&count, sizeof(int), 1, file);
	for (size_t i = 0; i < count; i++)
	{
		int lName = strlen(jobs[i]->name);
		fwrite(&lName, sizeof(int), 1, file);
		fwrite(jobs[i]->name, sizeof(char), lName, file);
		int lCompany = strlen(jobs[i]->company);
		fwrite(&lCompany, sizeof(int), 1, file);
		fwrite(jobs[i]->company, sizeof(char), lCompany, file);
		fwrite(&jobs[i]->salary, sizeof(int), 1, file);
		fwrite(&jobs[i]->no, sizeof(int), 1, file);
	}
	fclose(file);
}
void ReadFile(const char* filename, Job** jobs, int& count) {
	FILE* file;
	fopen_s(&file, filename, "rb");
	Job** temp = new Job * [count];
	fread_s(&count, sizeof(int), sizeof(int), 1, file);
	for (size_t i = 0; i < count; i++)
	{
		int lName = 0;
		fread_s(&lName, sizeof(int), sizeof(int), 1, file);

		char* name = new char[lName + 1];
		fread_s(name, lName, sizeof(char), lName, file);
		name[lName] = '\0';
		int lCompany = 0;
		fread_s(&lCompany, sizeof(int), sizeof(int), 1, file);
		char* company = new char[lCompany + 1];
		fread_s(company, lCompany, sizeof(char), lCompany, file);
		company[lCompany] = '\0';

		int salary = 0;
		fread_s(&salary, sizeof(int), sizeof(int), 1, file);
		int no = 0;
		fread_s(&no, sizeof(int), sizeof(int), 1, file);
		temp[i] = new Job{ name,company,salary,no };
	}
	jobs = temp;
	temp = nullptr;
	fclose(file);

}
void ShowJobs(Job* job) {
	cout << "=====JOB INFO=====" << endl;
	cout << "ID : " << job->no << endl;
	cout << "Job name : " << job->name << endl;
	cout << "Company : " << job->company << endl;
	cout << "Salary : " << job->salary << endl;
}
void ShowAllJobs(Job** jobs, int count) {
	for (size_t i = 0; i < count; i++)
	{
		ShowJobs(jobs[i]);
	}
}
void AddNewJob(Job**& jobs, int& count) {
	cin.ignore();
	cin.clear();
	cout << "Enter job name : ";
	char* name = new char[30];
	cin.getline(name, 30);
	cout << "Enter company : ";
	char* company = new char[30];
	cin.getline(company, 30);
	cout << "Enter salary : ";
	int	salary = 0;
	cin >> salary;
	int no = jobs[count - 1]->no + 1;
	Job* newjob = new Job{ name,company,salary,no };
	auto temp = new Job * [count + 1];
	for (size_t i = 0; i < count; i++)
	{
		temp[i] = jobs[i];
	}
	temp[count] = newjob;
	jobs = temp;
	temp = nullptr;
	count++;
}
void DeleteJob(Job**& jobs, int& count, int id) {
	auto temp = new Job * [count - 1];
	for (size_t i = 0, k = 0; i < count; i++)
	{
		if (jobs[i]->no != id) {
			temp[k++] = jobs[i];
		}
		else {
			delete jobs[i];
		}
	}
	jobs = temp;
	temp = nullptr;
	count--;
}
void ShowMenu() {
	cout << "Show All Jobs    [1]" << endl;
	cout << "Add New Job      [2]" << endl;
	cout << "Delete Job By No [3]" << endl;
}


bool is_file_exist(const char* fileName)
{
	ifstream infile(fileName);
	return infile.good();
}

void main() {
	system("color f0");
	int countJob = 3;
	Job** jobs = new Job * [countJob] {new Job{ new char[30] {" .Net Developer"},new char[30] {"Google MMC"},40000,1 },
		new Job{ new char[30] {"UI/UX Designer"},new char[30] {"Meta MMC"},25000,2 },
		new Job{ new char[30] {"Node.js Developer"},new char[30] {"Meta MMC"},35000,3 }};


	char* filename = new char[30] {"Jobs.bin"};
	auto exist = is_file_exist(filename);
	if (!exist) {
		CreateFile(filename);
		WriteFile(filename, jobs, countJob);
	}
	enum Operations { show = '1', add = '2', delet = '3' };
	while (true)
	{
		ShowMenu();
		char select = NULL;
		cin >> select;
		if (select == show) {
			ReadFile(filename, jobs, countJob);
			ShowAllJobs(jobs,countJob);
		}
		else if (select == add) {
			AddNewJob(jobs, countJob);
			WriteFile(filename, jobs, countJob);
			cout << "Job added successfully.." << endl;
		}
		else if (select == delet) {
			cin.ignore();
			cin.clear();
			ReadFile(filename, jobs, countJob);
			ShowAllJobs(jobs, countJob);
			cout << "\n\nEnter Job ID : ";
			int id = 0;
			cin >> id;
			DeleteJob(jobs, countJob, id);
			WriteFile(filename,jobs,countJob);
			cout << "Job Deleted successfully.." << endl;
		}
		else {
			cout << "InCorrect Input" << endl;
		}
		system("pause");
		system("cls");
	}
	cout << endl << endl << endl; cin.get();
}