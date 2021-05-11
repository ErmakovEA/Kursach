#pragma once
#include "StudentClass.h"
#include <iostream>
#include "FileManagerClass.h"
using namespace std;
class StudentDBClass : public FileManagerClass
{
private:
	StudentNode* head;
	StudentNode* getNextNode;
	int count;
public:
	StudentDBClass() {
		head = NULL;
		getNextNode = NULL;
		count = 0;
	}
	~StudentDBClass() {
		Erase();
	}
	bool Erase() {
		head = NULL;
		return true;
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	void loadDataFromFile() {
		string line;
		int count = 0;
		std::ifstream inFile(FileName); // �������� ���� ��� ������
		if (inFile.is_open())
		{
			bool isRecord = false;
			StudentNode* sn = new StudentNode();
			int studentId = 0;
			while (getline(inFile, line))
			{
				if (strcmp(startRecordString.c_str(), line.c_str()) == 0) {
					isRecord = true;
					continue;
				}
				if (strcmp(endRecordString.c_str(), line.c_str()) == 0) {
					isRecord = false;
					studentId++;
					Add(sn);
					/// add

					continue;
				}
				if (isRecord) {
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 10; j++)
							sn->examsRecordsData[i][j].isEmpty = true;
					string valueName = getName(line);
					if (strcmp(getType(line).c_str(), "str") == 0)
					{
						string value = getValueStr(line);
						//cout << value << endl;
						if (strcmp("surName", valueName.c_str()) == 0)
							sn->surName = value;
						if (strcmp("name", valueName.c_str()) == 0)
							sn->name = value;
						if (strcmp("middleName", valueName.c_str()) == 0)
						    sn->middleName = value;
						if (strcmp("faculty", valueName.c_str()) == 0)
							sn->faculty = value;
						if (strcmp("department", valueName.c_str()) == 0)
							sn->department = value;						
						if (strcmp("group", valueName.c_str()) == 0)
							sn->group = value;						
						if (strcmp("record�ardNumber", valueName.c_str()) == 0)
							sn->record�ardNumber = value;
						if (strcmp("birthDateString", valueName.c_str()) == 0)
							sn->birthDateString = value;
						// ExamsRecords
						for(int i=0;i<9;i++)
							for (int j = 0; j < 10; j++) {
								//examsResults_0_2_n
											// i j
								string testNameString = "";
								testNameString = testNameString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_n";
								string testMarkString = "";
								testMarkString = testMarkString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_m";
								if (strcmp(testNameString.c_str(), valueName.c_str()) == 0){
									sn->examsRecordsData[i][j].name = value;
									sn->examsRecordsData[i][j].isEmpty = false;
								}
								if (strcmp(testMarkString.c_str(), valueName.c_str()) == 0){
									sn->examsRecordsData[i][j].mark = atoi(value.c_str());
									sn->examsRecordsData[i][j].isEmpty = false;
								}
							}
					}
					else // ����� ���� int �� ���� ���������
					{
						int value = getValueInt(line);
						if (strcmp("id", valueName.c_str()) == 0)
							sn->id = studentId;  // ������ ����� ���������� ����� ������ � �����
						//������ ���� value ������ ��, �� �����;) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						if (strcmp("startYear", valueName.c_str()) == 0)
							sn->id = value;
						if (strcmp("sex", valueName.c_str()) == 0)
							if (value == 0)
								sn->sex = false;
							else
								sn->sex = true;
					}
				}
			}
			inFile.close();     // ��������� ����
		}
	}
	void saveDataToFile() {
		std::ofstream outFile;          // ����� ��� ������
       
		string tmpFileName = "d:\\db1.txt";
		ifstream iff(tmpFileName); //���� ���� ���� �������
		if (iff.bad() == false) 
		{
			remove(tmpFileName.c_str());
		}
        outFile.open(tmpFileName, std::ios::app); // �������� ���� ��� ������
		// outFile.open(FileName, std::ios::app); // �������� ���� ��� ������
        if (outFile.is_open())
        {
            
            StudentClass st = StudentClass();
			int recordsCount = GetRecordCount();
			StudentNode* sn;
			for (int i = 0; i < recordsCount;i++) {
            //st.addRusakov();
				outFile << startRecordString << std::endl;
				sn = getStudentNode(i);
				st.UpdateMasString(sn);
				st.getInitStringRecord();
				string resultString = st.getStringRecord();
				while (resultString.length() > 0) {
					outFile << resultString << std::endl;
					resultString = st.getStringRecord();
				}
				outFile << endRecordString << std::endl;
			}
            
        }
        outFile.close();
	}
	void setData(StudentNode* tNode, StudentNode* st) {
		tNode->surName = st->surName;
		tNode->name = st->name;
		tNode->middleName = st->middleName;
		tNode->faculty = st->faculty;
		tNode->department = st->department;
		tNode->group = st->group;
		tNode->record�ardNumber = st->record�ardNumber;
		tNode->sex = st->sex;
		tNode->startYear = st->startYear;
		tNode->birthDateString = st->birthDateString;
		// //�� ��������
		//ExamsRecords data[9][10];
		for(int i=0;i<9;i++)
			for (int j = 0; j < 10; j++) {
				tNode->examsRecordsData[i][j] = st->examsRecordsData[i][j];
			}
		//tNode->isNULL = false;
	}
	bool Add(StudentNode *st) {
		if (!head)
		{
			head = new StudentNode();
			//head->surName = st->surName;
			setData(head, st);
			//head->data = st;
			head->next = NULL;
			count++;
			return true;
		}
		else
		{
			StudentNode* tmp = new StudentNode();
			setData(tmp, st);
			//tmp->data = st;
			tmp->next = head;
			head = tmp;
			count++;
			return true;
		}
		return false;
	}
	StudentNode* getInit() {
		return getNextNode = head;
	}
	int getCount() {
		return count;
	}
	void printAllSurName() {
		StudentNode* curr = NULL;
		curr = head;
		while (curr) {
			cout << curr->surName << endl;
			curr = curr->next;
		}
	}

	StudentNode* getStudentNode(int num) {
		StudentNode* curr = NULL;
		curr = head;
		int ind = 0;
		while (curr) {
			//cout << curr->surName << endl;
			if (ind == num) {
				return curr;
				break;
			}
			else {
				curr = curr->next;
				ind++;
			}
		}
		return NULL;
	}
	
};


