#include <iostream>
#include <string>

class String
{
public:
	String() = default;
	String(const char* string)
	{
		std::cout << "Created" << std::endl;
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}
	String(const String& other)
	{
		std::cout << "Coppied" << std::endl;
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}
	
	String(String&& other) noexcept
	{
		std::cout << "Moved" << std::endl;
		m_Size = other.m_Size;
		m_Data = other.m_Data;
		
		other.m_Size = 0;		//we are setting other as hollow object 
		other.m_Data = nullptr; //so that when it gets deleted it doesent delete our array
	}

	String& operator=(String&& other) noexcept
	{
		std::cout << "Moved" << std::endl;

		if (this != &other) //moving only makes sense if objects are different
		{
			delete[] m_Data; //object that we are moving to might have some data alocated previously

			m_Size = other.m_Size;
			m_Data = other.m_Data;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}

		return *this;
	}

	~String()
	{
		std::cout << "Destroyed" << std::endl;
		delete m_Data;
	}

	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++)
		{
			std::cout << m_Data[i];
		}
		std::cout << std::endl;
	}
private:
	char* m_Data;
	uint32_t m_Size;

};

class Entity
{
public:
	Entity(const String& name)
		:m_Name(name)
	{

	}

	Entity(String&& name)
		:m_Name(std::move(name))
	{

	}
	void PrintName()
	{
		m_Name.Print();
	}

private:
	String m_Name;
};

int main()
{
	String name = "Copying Name"; //First constructed a String object that then will be passed and copying will be performed
	Entity e(name);//construction of entity with a copy constructor
	e.PrintName();
	std::cout << "\n\n----------------------------------------\n\n";

	Entity entity(String("Moving Name")); //First "Name" String will be constructed then it will be moved without constructing any other String object and copying things
	entity.PrintName();
	std::cout << "\n\n----------------------------------------\n\n";



	String SRC = "Hello";
	String DST; 
	SRC.Print();//Printing Hello
	DST.Print();//Dst is now empty so printing nothing
	DST = std::move(SRC);//move basicly does the same thing as casting to (String&&), Movingdata from SRC do DST and clearing SRC
	SRC.Print();//Nothing in SRC
	DST.Print();//Hello in DST without any copying
	std::cout << "\n\n----------------------------------------\n\n";
}