#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <ctime> 

using namespace std;

struct ticket
{
	unsigned int numbers[6];
	ticket* next;
};

class SuperDraw
{
public:
	SuperDraw()
	{
		ticketListTail = NULL;
		ticketListHead = NULL;
	};
	SuperDraw(int num)
	{
		
		ticketListTail = NULL;
		ticketListHead = NULL;

		cout << num << " new tickets were succesfully generated." << endl;
		cout << "The numbers are: ";
		
		for(int i = 0; i<num; i++)
		{
			newTicket(0);
		}
		ticket* curr = ticketListHead;
		int listlength = 0;

		for(int i=0; i<num; i++)
		{
			if(curr != NULL)
			{
				for(int j = 0; j<6; j++)
				{
				if(j == 5 && curr == ticketListTail) cout<< curr-> numbers[j] << "." << endl;
				else if(j == 5) cout<< curr-> numbers[j] << " and ";
				else cout << curr->numbers[j] << ", ";
				}
			}
			
			curr = curr->next;
		
		}
	
	};
	SuperDraw(const SuperDraw& sd)			//deep copy of another SuperDraw object
	{
		ticketListHead = new ticket;

		for(int i= 0; i<6; i++)					//copying head
		{
			ticketListHead->numbers[i] = sd.ticketListHead->numbers[i]; 
		}
		ticket* curr = sd.ticketListHead;
		ticket* currcopy = ticketListHead;
		ticket* nextcopy;

		while(curr->next != NULL)				//copying everything in between head and tail
		{
			nextcopy = new ticket;
			for(int i= 0; i<6; i++)
			{
				nextcopy->numbers[i] = curr->next->numbers[i]; 
			}
			currcopy->next = nextcopy;
			currcopy = currcopy->next;
			curr = curr->next;
		}
		
		currcopy->next = NULL;
		ticketListTail = currcopy;			//copying tail
	};

	~SuperDraw()							//destructor
	{
		ticket* curr = ticketListHead;
		ticket* temp = ticketListHead;
		while(curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			delete temp;
		}

	};
	void newTicket()					//default newTicket()
	{
		newTicket(0);
	};
	void newTicket(int pr)
	{
		ticket* tic = new ticket;
		tic -> next = NULL;
		bool h = false;
		bool stop = false;

		int nums[6];
		int num = 0;
		for(int i = 0; i<6; i++)		//generating random numbers
		{
			h = false;
			nums[i] = rand()%49 + 1;
			while(!h)					//making sure lottos numbers aren't repeated in the array
			{
				h = true;
				for(int j = 0; j<i; j++)
				{
					if(nums[i] == nums[j])
					{
						nums[i] = rand()%49 + 1;
						h = false;
					}

				}
			}

			
			
		}

		bool sorted = false;
		while(!sorted)				//sort algorithm
		{
			sorted = true;
			for(int i = 0; i<5; i++)
			{
				if(nums[i] > nums[i+1])
				{
					int temp = nums[i];
					nums[i] = nums[i+1];
					nums[i+1] = temp;
					sorted = false;

				}
			}
		}

		memcpy(tic -> numbers, nums, sizeof(nums));				//copying sorted lotto numbers into the tic->numbers

		if(ticketListHead == NULL)
		{
			ticketListHead = tic;
			ticketListTail = tic;
		}

		else{
			ticketListTail->next = tic;
			ticketListTail = ticketListTail -> next;
		}

		if(pr == 1)												//print if 1 is passed as an argument
		{
			cout << "A new ticket was successfully generated. The numbers are: ";
			for(int i=0; i<6; i++)
			{
				if(i == 5) cout << nums[i] << '\n';
				else cout << nums[i] << ", ";
			}

		}

		
	};
	void printAllTicketNumbers()
	{
		ticket* curr = ticketListHead; 
		int numtix = 0;
		while(curr != NULL)							//calculating the lenght of our linked list
		{
			numtix++;
			curr = curr->next;
		}
		cout << "We found " << numtix << " generated tickets:" << endl;
		curr = ticketListHead;
		while(curr != NULL)
		{
			for(int i= 0; i<6; i++)						//print the lists of lotto numbers
			{
				if(i == 5) cout << curr->numbers[i] << endl;				
				else cout << curr->numbers[i] << ", ";
			}
			
			curr = curr->next;
		}
	};
	void verifySequence(int myNumbers[])		
	{

		ticket* curr = ticketListHead; 
		
		while(curr != NULL)
		{

			unsigned int temp[6];
			memcpy(temp, curr->numbers, sizeof(temp));

			for(int i = 0; i<6; i++)					
			{
				int a = temp[i];
				int b = myNumbers[i];
				if(a==b && i==5){			
					cout << "The provided sequence of numbers was already generated.";
					return;
				}
				else if(a !=b) break;
		
			}
			curr = curr->next;
		}

	cout << "The provided sequence of numbers was never generated before.";
	};

	void deleteSequence(int myNumbers[])
	{
		ticket *curr = ticketListHead;
		ticket *prev = ticketListHead;

		while(curr != NULL)
		{

			unsigned int temp[6];
			memcpy(temp, curr->numbers, sizeof(temp));

			for(int i = 0; i<6; i++)			//checking if myNumbers is the same as a lotto sequence in our object
			{
				int a = temp[i];
				int b = myNumbers[i];
				if(a==b && i==5){
					prev->next = curr->next;
					delete curr;
					cout << "The provided sequence of numbers was succesfully deleted." << endl;
					return;
				}
				else if(a !=b) break;
		
			}
			prev = curr;
			curr = curr->next;
		}
		cout << "The provided sequence of numbers was never generated before." << endl;
	};

private:
	ticket* ticketListHead;
	ticket* ticketListTail;

};


int main()
{
	//tester for copy constructor and constructor
	/*SuperDraw sd(4);
	sd.newTicket(1);
	sd.newTicket(0);
	SuperDraw sd2(sd);
	sd2.newTicket(1);
	sd.printAllTicketNumbers();
	sd2.printAllTicketNumbers();*/
	
	
	//tester for printallticketnumbers
	
	/*sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.printAllTicketNumbers();*/

	//tester for verifysequence
	
	/*sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.printAllTicketNumbers();
	int myNumbers[] = {4, 6, 22, 24, 31, 38};
	sd.verifySequence(myNumbers); 
	*/

	//tester for deletesequence
	//SuperDraw sd;
	/*sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.newTicket(0);
	sd.printAllTicketNumbers();
	int myNumbers2[] = {9, 10, 18, 24, 25, 48};
	sd.deleteSequence(myNumbers2);
	sd.printAllTicketNumbers();*/

	return 0;

	
}


